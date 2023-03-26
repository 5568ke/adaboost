#include <fstream>
#include <mutex>
#include <thread>
#include <cmath>
#include <vector>
#include <iostream>
#include "../include/segment.h"
#include "../include/spot.h"
#include "../include/Label.h"
#include "../include/stump.h"
#include "WeakLearner.h"

void Normolized_data_weight(std::vector<segment>& segments){
  int is_feet_count{},not_feet_count{}; 
  for(auto& seg : segments){
    if(seg.Is_feet==1)
      is_feet_count++;
    else
      not_feet_count++;
  }
  for(auto& seg : segments){
    if(seg.Is_feet==1)
      seg.Initialize_weight(0.5/is_feet_count);
    else 
      seg.Initialize_weight(0.5/not_feet_count);
  }
}
std::vector<segment> load_data(){
  std::ifstream xy_data;
  xy_data.open("../data/xy_data.txt");
  if(xy_data.fail()){
    std::cout<<"input file open failed !! ";
    exit(1);
  }

  const double threshold=0.1;   //to be revised
  std::vector<segment> segments;
  std::vector<std::vector<segment>> temp_segments;    // this vector contains all segment in this round of datamain
  temp_segments.resize(60);
  for(int round{};round<60;round++){
    std::vector<spot> single_segment;
    std::vector<spot> valid_spots;
    double x,y;
    //get valid input x,y position 
    // 720 * 2   x , y
    for(int i=0;i<720;i++){
      xy_data>>x>>y;
      if(( x != 0 || y!=0) && (std::isfinite(x) && std::isfinite(y)))     
        valid_spots.emplace_back(x,y);
    }
    single_segment.emplace_back(valid_spots[0].x,valid_spots[0].y);
    const size_t valid_size=valid_spots.size();
    for(int i=1;i<valid_size;i++){
      if(std::sqrt(std::pow(valid_spots[i].x-valid_spots[i-1].x,2) + std::pow(valid_spots[i].y-valid_spots[i-1].y,2)) > threshold ){
        // this spot belong to a new segment 
        temp_segments[round].emplace_back(std::move(single_segment));
        single_segment.clear();
      }
      // push spots in to segment buffer
      single_segment.push_back(valid_spots[i]);
    }
    temp_segments[round].emplace_back(std::move(single_segment));
    single_segment.clear();
    valid_spots.clear();
  }

  xy_data.close();

  //mark if segment is feet
  for(int round{};round<60;round++){
    std::vector<int> label_data=Label(round+1,temp_segments[round]); 
    for(int index{};index<label_data.size();index++)
      temp_segments[round][index].Is_feet=label_data[index];
  }

  //store all segments in to a one-dimension vector
  for(int round{};round<60;round++)
    for(int index{};index<temp_segments[round].size();index++)
      segments.push_back(std::move(temp_segments[round][index]));

  return segments;
}


int main(){

  // load all segment's data in to vector
  std::vector<segment> segments = load_data(); 
  const int segments_number=segments.size();
  int is_feet_count{},not_feet_count{};
  Normolized_data_weight(segments); 

  std::vector<WeakLearner> Chosen_WeakLearners;
  std::vector<std::string> Features{"spots_number","stand_deviation","width","circularity","radius"};
  // std::vector<std::string> Features{"circularity"};


  int iterate_num,iterate_count{};
  std::cout<<"iterate times : "<<std::endl;
  std::cin>>iterate_num;
  // for(auto& seg : segments){
  //   std::cout<<"weight : "<<seg.Get_weight()<<std::endl;
  // }

  for(int i=0;i<iterate_num;i++){
   
    std::cout<<"iterate times : "<<++iterate_count<<std::endl;
    std::vector<std::thread> training_workers;
    std::vector<WeakLearner> WeakLearners;
    for(int index{};index<Features.size();index++){
      std::mutex _m;
      std::string feature{Features[index]};
      // WeakLearners.emplace_back(segments,feature);   
      training_workers.push_back(std::thread([&,index,feature](){
        // WeakLearners.emplace_back(segments,feature);   
        // std::cout<<"training feature : "<<feature<<std::endl;
        WeakLearner t_WeakLearner(segments,feature);
        std::lock_guard<std::mutex> lg(_m);
        WeakLearners.push_back(t_WeakLearner);
      }));
    }
    for(auto & worker : training_workers)
      worker.join();

    int max_r_index=0;
    double max_r=0;
    for(int index{};index<5;index++){
      if(WeakLearners[index].R > max_r){
        max_r=WeakLearners[index].R;
        max_r_index=index; 
      }
    }
    // std::cout<<"final_max_r : "<<max_r<<std::endl;
    WeakLearners[max_r_index].been_chosen(segments);
    std::cout<<"Feature : "<<WeakLearners[max_r_index].Get_Feature()<<std::endl;
    std::cout<<"greater or less : "<<WeakLearners[max_r_index].Get_Choose()<<std::endl;
    Chosen_WeakLearners.push_back(WeakLearners[max_r_index]);
    // for(auto& seg : segments){
    //   std::cout<<"weight : "<<seg.Get_weight()<<std::endl;
    // }
  }
  std::cout<<"finish iterate"<<std::endl;

  std::cout<<"size :"<<Chosen_WeakLearners.size()<<std::endl;
  for(int i{};i<Chosen_WeakLearners.size();i++){
    std::cout<<"Amount_of_say : "<<Chosen_WeakLearners[i].Amount_of_say<<std::endl;
  }
  
  
  

  int True_Positive{},True_Negative{},Faulse_Positive{},Faulse_Negative{};
  for(auto & seg : segments){
    double result{};
    for(auto & classifier : Chosen_WeakLearners){
      result+= classifier.Predict_if_is_feet(seg)*classifier.Amount_of_say;
      // std::cout<< "result : "<<result<<std::endl;
      // std::cout<< "point : "<<classifier.Get_point();
      // std::cout<< "   Amount_of_say : "<<classifier.Amount_of_say<<std::endl;
    }
    if(seg.Is_feet==1){
      if(result>0)
        True_Positive++;
      else
        True_Negative++;
    }else{
      if(result>0)
        Faulse_Positive++;
      else
        Faulse_Negative++;
    }
  }

  std::cout<<"True_Positive : "<<True_Positive<<std::endl;
  std::cout<<"True_Negative : "<<True_Negative<<std::endl;
  std::cout<<"Faulse_Positive : "<<Faulse_Positive<<std::endl;
  std::cout<<"Faulse_Negative : "<<Faulse_Negative<<std::endl;
  
}
