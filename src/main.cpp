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
#include "WeakLearner.h"
#include "../include/matplotlibcpp.h"



int main(){

  // load train data and test data
  auto res = load_data();
  std::vector<segment> train_segments{res.first};
  std::vector<std::vector<segment>> test_segments{res.second}; 
  Normolized_data_weight(train_segments); 
  
  std::vector<WeakLearner> Chosen_WeakLearners;
  std::vector<std::string> Features{"spots_number","stand_deviation","width","circularity","radius"};


  int iterate_num,iterate_count{};
  std::cout<<"iterate times : "<<std::endl;
  std::cin>>iterate_num;
  for(int i=0;i<iterate_num;i++){
   
    //for every feature , train a weaklearner
    std::cout<<"iterate times : "<<++iterate_count<<std::endl;
    std::vector<std::thread> training_workers;
    std::vector<WeakLearner> WeakLearners;
    std::mutex _m;
    for(int index{};index<Features.size();index++){
      std::string feature{Features[index]};
      training_workers.push_back(std::thread([&,index,feature](){
        WeakLearner t_WeakLearner(train_segments,feature);
        std::lock_guard<std::mutex> lg(_m);
        WeakLearners.push_back(t_WeakLearner);
      }));
    }
    for(auto & worker : training_workers)
      worker.join();

    //choose best weaklearner
    int max_r_index=0;
    double max_r=0;
    for(int index{};index<Features.size();index++){
      if(WeakLearners[index].R > max_r){
        max_r=WeakLearners[index].R;
        max_r_index=index; 
      }
    }
    WeakLearners[max_r_index].been_chosen(train_segments);   // data's weight will be update in this function
    std::cout<<"Feature : "<<WeakLearners[max_r_index].Get_Feature()<<std::endl;
    // std::cout<<"greater or less : "<<WeakLearners[max_r_index].Get_Choose()<<std::endl;
    Chosen_WeakLearners.push_back(WeakLearners[max_r_index]);
  }
  std::cout<<"finish iterate"<<std::endl;

  std::cout<<"size :"<<Chosen_WeakLearners.size()<<std::endl;
  for(int i{};i<Chosen_WeakLearners.size();i++){
    std::cout<<"Amount_of_say : "<<Chosen_WeakLearners[i].Amount_of_say<<std::endl;
  }
  
  
  
  // showing predict result : animation and confusion table
  int True_Positive{},True_Negative{},Faulse_Positive{},Faulse_Negative{};
  std::unordered_map<std::string,int> Predict_Result;
  for(auto & seg_vec : test_segments){
    // this scope execute predict of one round(second) data
    std::vector<double> Is_feet_vec_x,Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y;
    for(auto & seg : seg_vec)
      Get_Predict_Result(seg,Predict_Result,Is_feet_vec_x,Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y);
    Show_Predict_Animation(Is_feet_vec_x, Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y);
  }
  Show_Predict_Result(True_Positive,True_Negative,Faulse_Positive,Faulse_Negative);
}
