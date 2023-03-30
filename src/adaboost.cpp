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

  // Load train data and test data
  auto res = load_data();
  std::vector<segment> train_segments{res.first};
  for(size_t index{1};index<train_segments.size()-1;index++)
    train_segments[index].Caculate_features(train_segments[index-1].Get_last_point(),train_segments[index+1].Get_first_point());
  std::vector<std::vector<segment>> test_segments{res.second}; 
  for(auto & test_segs: test_segments)
    for(size_t index{1};index<test_segs.size()-1;index++)
      test_segs[index].Caculate_features(test_segs[index-1].Get_last_point(),test_segs[index+1].Get_first_point());
  Normolized_data_weight(train_segments); 

  // This vector will store all weaklearners been chosen and become the stronglearner.
  std::vector<WeakLearner> Chosen_WeakLearners;

  // Get features
  const std::vector<std::string> Features{Get_features()};
  const size_t Features_num = Features.size();

  // Set up the thread pool with the chosen number of threads.
  ThreadPool pool(UserIO());

  const int iterate_times{Get_iterate_times()};
  std::cout<<" Training process start currently ......" <<std::endl<<" Please wait for a few seconds "<<std::endl;
  auto begin = std::chrono::high_resolution_clock::now();
  for(int i=0;i<iterate_times;i++){
    // Iterate n times
    std::vector<std::thread> training_workers;
    std::vector<WeakLearner> WeakLearners;
    std::mutex _m;

    // This vector used to wait for every features' weaklearner training finished , so the iterations will be sequential
    std::vector<std::future<void>> signals(Features_num);

    // For every feature train a weaklearner
    for(int index{};index<Features_num;index++){
      std::string feature{Features[index]};
      signals[index]=pool.enqueue([&,index,feature](){
        WeakLearner t_WeakLearner(train_segments,feature);
        std::lock_guard<std::mutex> lg(_m);    // STL isn't thread safe --> Lock  ,  push back isn't slow , so just spin
        WeakLearners.push_back(t_WeakLearner);
      }); 
    }

    // Wait all weaklearners' training been finished
    for(std::future<void>& signal : signals)
      signal.wait();

    // Choose best weaklearner
    int max_r_index{};
    double max_r{};
    for(int index{};index<Features.size();index++){
      if(WeakLearners[index].R > max_r){
        max_r=WeakLearners[index].R;
        max_r_index=index; 
      }
    }

    // Data's weight will be update in this function (using the chosen weaklearner's alpha)
    WeakLearners[max_r_index].been_chosen(train_segments);       

    // Put the chosen weaklearner (best accurency) in to the stronglearner 
    Chosen_WeakLearners.push_back(WeakLearners[max_r_index]);

    // Go next iteration
  }
  std::cout<<" Training process finished "<<std::endl;

  // Finished training stop threadpool
  pool.stop();
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  // Show all message
  Show_Result_Message(train_segments,test_segments,Chosen_WeakLearners,elapsed.count());
}
