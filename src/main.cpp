#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
#include "segment.h"
#include "spot.h"

std::vector<std::vector<segment>> load_data(){
  std::ifstream xy_data;
  xy_data.open("../data/xy_data.txt");
  if(xy_data.fail()){
    std::cout<<"input file open failed !! ";
    exit(1);
  }

  const double threshold=0.1;   //to be revised
  std::vector<std::vector<segment>> segments;    // this vector contains all segment in this round of datamain
  segments.resize(120);
  for(int round{};round<120;round++){

    std::vector<spot> single_segment;
    std::vector<spot> valid_spots;
    double x,y;
    //get valid input x,y position 
    // 720 * 2   x , y
    for(int i=0;i<720;i++){
      xy_data>>x>>y;
      if(( x != 0 || y!=0) && (std::isnormal(x) && std::isnormal(y)))     
        valid_spots.emplace_back(x,y);
    }
    single_segment.emplace_back(valid_spots[0].x,valid_spots[0].y);
    const size_t valid_size=valid_spots.size();
    for(int i=1;i<valid_size;i++){
      if(std::sqrt(std::pow(valid_spots[i].x-valid_spots[i-1].x,2) + std::pow(valid_spots[i].y-valid_spots[i-1].y,2)) > threshold ){
        // this spot belong to a new segment 
        segments[round].emplace_back(std::move(single_segment));
        single_segment.clear();
      }
      // this spot belongs to the same segment which last spot belongs to
      single_segment.push_back(valid_spots[i]);
    }
    segments[round].emplace_back(std::move(single_segment));
    single_segment.clear();
    valid_spots.clear();
  }

  xy_data.close();
  return segments;
}


int main(){

  // load data
  // one time of looping means read 360 (one round) of data
  std::vector<std::vector<segment>> segments = load_data(); 
  for(int round{};round<segments.size();round++){
    std::cout<<"round :"<<round+1<<"   segment_numbers : "<<segments[round].size()<<std::endl;
    for(int seg_index{};seg_index<segments[round].size();seg_index++){
      // std::cout<<"round : "<<round<<", segemnt index : "<<seg_index<<std::endl;
      // segments[round][seg_index].Print_me();
      // std::cout<<std::endl;
    }
  }
}
