#include <fstream>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <cmath>
#include <utility>
#include <vector>
#include <iostream>
#include "../include/segment.h"
#include "../include/spot.h"
#include "../include/stump.h"
#include "../include/utility.h"
#include "../include/matplotlibcpp.h"



int main(){

  // load train data and test data
  auto res = load_data();
  std::vector<segment> train_segments{res.first};
  for(size_t index{1};index<train_segments.size()-1;index++)
    train_segments[index].Caculate_features(train_segments[index-1].Get_last_point(),train_segments[index+1].Get_first_point());
  std::vector<std::vector<segment>> test_segments{res.second}; 
  for(auto & test_segs: test_segments)
    for(size_t index{1};index<test_segs.size()-1;index++)
      test_segs[index].Caculate_features(test_segs[index-1].Get_last_point(),test_segs[index+1].Get_first_point());
  Normolized_data_weight(train_segments); 
  
  std::vector<WeakLearner> Chosen_WeakLearners;
  std::vector<std::string> Features{"distance","spots_number","stand_deviation","width","circularity","radius","jump_distance_next","jump_distance_prev","linearity"};
  // for(segment& seg : train_segments)
    // if(seg.Is_feet==-1)
      // seg.Print_me();


  int iterate_num,iterate_count{};
  std::cout<<"iterate times : "<<std::endl;
  std::cin>>iterate_num;
  for(int i=0;i<iterate_num;i++){
    //iterate n times
    std::cout<<"iterate times : "<<++iterate_count<<std::endl;
    std::vector<std::thread> training_workers;
    std::vector<WeakLearner> WeakLearners;
    std::mutex _m;
    for(int index{};index<Features.size();index++){
    //for every feature train a weaklearner
      std::string feature{Features[index]};
      training_workers.push_back(std::thread([&,index,feature](){
        WeakLearner t_WeakLearner(train_segments,feature);
    //stl isn't thread save -> lock
        std::lock_guard<std::mutex> lg(_m);
        WeakLearners.push_back(t_WeakLearner);
      }));
    }
    for(auto & worker : training_workers)
      worker.join();

    //choose best weaklearner
    int max_r_index{};
    double max_r{};
    for(int index{};index<Features.size();index++){
      // std::cout<<"feature : "<<WeakLearners[index].Get_Feature()<<" r : "<<WeakLearners[index].R<<std::endl;
      if(WeakLearners[index].R > max_r){
        max_r=WeakLearners[index].R;
        max_r_index=index; 
      }
    }
    WeakLearners[max_r_index].been_chosen(train_segments);   // data's weight will be update in this function
    std::cout<<"Feature : "<<WeakLearners[max_r_index].Get_Feature()<<std::endl;
    Chosen_WeakLearners.push_back(WeakLearners[max_r_index]);
  }

  // for(int index{};index<Features.size()*1000;index++){
  //   std::cout<<"times : "<<index<<std::endl;
  //   // for(auto& seg : train_segments)
  //   //   std::cout<<"weight : "<<seg.Get_weight()<<std::endl; 
  //     Chosen_WeakLearners.emplace_back(train_segments,Features[index%Features.size()]);
  //     std::cout<<"Feature : "<<Chosen_WeakLearners[index].Get_Feature()<<std::endl;
  //     Chosen_WeakLearners[index].been_chosen(train_segments);
  // }




  // showing predict result : animation and confusion table
  int True_Positive{},True_Negative{},Faulse_Positive{},Faulse_Negative{};
  std::unordered_map<std::string,int> Predict_Result;
  for(auto & seg_vec : test_segments){
    // this scope execute predict of one round(second) data
    std::vector<double> Is_feet_vec_x,Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y;
    for(auto & seg : seg_vec)
      Get_Predict_Result(seg,Predict_Result,Is_feet_vec_x,Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y,Chosen_WeakLearners);
    // matplotlibcpp::figure();
    // matplotlibcpp::figure_size(20,20);
    Show_Predict_Animation(Is_feet_vec_x, Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y);
  }
  Show_Predict_Result(Predict_Result);
}
