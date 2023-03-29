#include <unordered_map>
#include<vector>
#include<fstream>
#include<iostream>
#include<cmath>
#include"../include/utility.h"
#include"../include/segment.h"
#include"../include/Label.h"
#include"../include/matplotlibcpp.h"

//only use in main

std::pair<std::vector<segment>,std::vector<std::vector<segment>>> load_data(){
  std::ifstream xy_data;
  xy_data.open("../data/xy_data.txt");
  if(xy_data.fail()){
    std::cout<<"input file open failed !! ";
    exit(1);
  }

  const double threshold=0.1;   //to be revised
  std::vector<segment> train_segments;
  std::vector<std::vector<segment>> test_segments;
  std::vector<std::vector<segment>> temp_segments;    // this vector contains all segment in this round of data
  temp_segments.resize(120);
  for(int round{};round<120;round++){
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
  for(int round{};round<120;round++){
    std::vector<int> label_data=Label(round+1,temp_segments[round]); 
    for(int index{};index<label_data.size();index++)
      temp_segments[round][index].Is_feet=label_data[index];
  }

  //store all segments in to a one-dimension vector
  for(int round{};round<60;round++)
    for(int index{};index<temp_segments[round].size();index++)
      train_segments.push_back(std::move(temp_segments[round][index]));


  for(int round{60};round<120;round++)
    test_segments.push_back(std::move(temp_segments[round]));
  return std::make_pair(train_segments, test_segments);
}
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

void Show_Predict_Animation(const std::vector<double>& Is_feet_vec_x,
                            const std::vector<double>& Is_feet_vec_y,
                            const std::vector<double>& Not_feet_vec_x,
                            const std::vector<double>& Not_feet_vec_y
                            ){
    matplotlibcpp::xlim(-5, 5);
    matplotlibcpp::ylim(-5, 5);
    matplotlibcpp::plot(Is_feet_vec_x, Is_feet_vec_y, "r.");  
    matplotlibcpp::plot(Not_feet_vec_x, Not_feet_vec_y, "b.");  
    matplotlibcpp::pause(0.05);
    matplotlibcpp::clf();
    matplotlibcpp::draw();
}

void Show_Predict_Result(std::unordered_map<std::string,int>& Predict_Reuslt,std::string type){
  std::cout<<"===================================================="<<std::endl;
  std::cout<<type<<" data's result : "<<std::endl;
  int True_Positive{Predict_Reuslt["True_Positive"]},
      True_Negative{Predict_Reuslt["True_Negative"]},
      Faulse_Positive{Predict_Reuslt["Faulse_Positive"]},
      Faulse_Negative{Predict_Reuslt["Faulse_Negative"]};
  std::cout<<"True_Positive : "<<True_Positive<<std::endl;
  std::cout<<"True_Negative : "<<True_Negative<<std::endl;
  std::cout<<"Faulse_Positive : "<<Faulse_Positive<<std::endl;
  std::cout<<"Faulse_Negative : "<<Faulse_Negative<<std::endl;
  std::cout<<"accuracy : "<<(double)(True_Positive+True_Negative)/(True_Positive+True_Negative+Faulse_Positive+Faulse_Negative)<<std::endl;
  std::cout<<"precision : "<<(double)True_Positive/(True_Positive+Faulse_Positive)<<std::endl;
  std::cout<<"recall : "<<(double)True_Positive/(True_Positive+Faulse_Negative)<<std::endl;
  std::cout<<"===================================================="<<std::endl;
}

void Get_Predict_Result(const segment& seg,
                        std::unordered_map<std::string,int>& dict,
                        std::vector<double>& Is_feet_vec_x,
                        std::vector<double>& Is_feet_vec_y,
                        std::vector<double>& Not_feet_vec_x,
                        std::vector<double>& Not_feet_vec_y,
                        std::vector<WeakLearner>& Chosen_WeakLearners
                        ){
  double result{};
  for(auto & classifier : Chosen_WeakLearners)
    result+= classifier.Predict_if_is_feet(seg)*classifier.Amount_of_say;
  if(seg.Is_feet==1){
    if(result>0){
      dict["True_Positive"]++;
      for(spot s :seg.Get_Spots()){
        Is_feet_vec_x.push_back(s.x);
        Is_feet_vec_y.push_back(s.y);
      }
    }else{
      dict["Faulse_Negative"]++;
      for(spot s :seg.Get_Spots()){
        Not_feet_vec_x.push_back(s.x);
        Not_feet_vec_y.push_back(s.y);
      }
    } 
  }
  else{
    if(result>0){
      dict["Faulse_Positive"]++;
      for(spot s :seg.Get_Spots()){
        Is_feet_vec_x.push_back(s.x);
        Is_feet_vec_y.push_back(s.y);
      }
    }else{
      dict["True_Negative"]++;
      for(spot s :seg.Get_Spots()){
        Not_feet_vec_x.push_back(s.x);
        Not_feet_vec_y.push_back(s.y);
      }
    }
  }
}
