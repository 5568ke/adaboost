#include <fstream>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <cmath>
#include <utility>
#include <vector>
#include <future>
#include <iostream>
#include "../include/segment.h"
#include "../include/spot.h"
#include "../include/stump.h"
#include "../include/utility.h"
#include "../include/matplotlibcpp.h"
#include "../include/ThreadPool.h"



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
  

  //this vector will store all weaklearners been chosen,and become the stronglearner
  std::vector<WeakLearner> Chosen_WeakLearners;
  const std::vector<std::string> Features{"distance","spots_number","stand_deviation","width","circularity","radius","jump_distance_next","jump_distance_prev","linearity"};
  const size_t Features_num=Features.size();

  const int max_thread_num=std::thread::hardware_concurrency();
  const int iterate_times=1000;
  int thread_num;
  std::cout<<" support "<<max_thread_num<<" concurrent threads "<<std::endl;
  std::cout<<" use thread numbers : ";
  std::cin>>thread_num;
  ThreadPool pool(thread_num);



  std::cout<<" start training" <<std::endl;
  auto begin = std::chrono::high_resolution_clock::now();
  for(int i=0;i<iterate_times;i++){
    //iterate n times
    std::vector<std::thread> training_workers;
    std::vector<WeakLearner> WeakLearners;
    std::mutex _m;

    std::vector<std::future<void>> signals(Features_num);
    for(int index{};index<Features_num;index++){
    //for every feature train a weaklearner
      std::string feature{Features[index]};
      signals[index]=pool.enqueue([&,index,feature](){
        WeakLearner t_WeakLearner(train_segments,feature);
        std::lock_guard<std::mutex> lg(_m);    // STL isn't thread safe --> Lock  ,  push back isn't slow , so just spin
        WeakLearners.push_back(t_WeakLearner);
      }); 
    }
    // wait all weaklearners' training been finished
    for(std::future<void>& signal : signals)
      signal.wait();

    // choose best weaklearner
    int max_r_index{};
    double max_r{};
    for(int index{};index<Features.size();index++){
      // std::cout<<"feature : "<<WeakLearners[index].Get_Feature()<<" r : "<<WeakLearners[index].R<<std::endl;
      if(WeakLearners[index].R > max_r){
        max_r=WeakLearners[index].R;
        max_r_index=index; 
      }
    }
    WeakLearners[max_r_index].been_chosen(train_segments);   // data's weight will be update in this function (using this weaklearner's alpha)
    Chosen_WeakLearners.push_back(WeakLearners[max_r_index]);
  }
  pool.stop();
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);


  std::cout<<" training use times : "<<elapsed.count() * 1e-9 <<std::endl<<std::endl<<std::endl;

 
  // showing predict result : animation and confusion table
  int t_True_Positive{},t_True_Negative{},t_Faulse_Positive{},t_Faulse_Negative{};
  // this hash table store the predict result : true positive , true negative , faulse positive , faulse negative
  std::unordered_map<std::string,int> t_Predict_Result;
  std::vector<double> t_Is_feet_vec_x,t_Is_feet_vec_y,t_Not_feet_vec_x,t_Not_feet_vec_y;
  for(auto & seg : train_segments)
    Get_Predict_Result(seg,t_Predict_Result,t_Is_feet_vec_x,t_Is_feet_vec_y,t_Not_feet_vec_x,t_Not_feet_vec_y,Chosen_WeakLearners);
  //this function show the animation of prediction red means been predicted as feet blue mens not feet


  // showing predict result : animation and confusion table
  int True_Positive{},True_Negative{},Faulse_Positive{},Faulse_Negative{};
  // this hash table store the predict result : true positive , true negative , faulse positive , faulse negative
  std::unordered_map<std::string,int> Predict_Result;
  for(auto & seg_vec : test_segments){
    // this scope execute predict of one one round(second) data
    // these vector if for animation
    std::vector<double> Is_feet_vec_x,Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y;
    for(auto & seg : seg_vec)
      Get_Predict_Result(seg,Predict_Result,Is_feet_vec_x,Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y,Chosen_WeakLearners);
    //this function show the animation of prediction red means been predicted as feet blue mens not feet
    Show_Predict_Animation(Is_feet_vec_x, Is_feet_vec_y,Not_feet_vec_x,Not_feet_vec_y);
  }
  Show_Predict_Result(t_Predict_Result,"training");
  Show_Predict_Result(Predict_Result,"test");
  
}
