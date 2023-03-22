#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
#include "segment.h"
#include "spot.h"

std::vector<segment> load_data(){
  // 720 * 2   x , y
  std::ifstream xy_data;
  xy_data.open("../data/xy_data.txt");
  if(xy_data.fail()){
    std::cout<<"input file open failed !! ";
    exit(1);
  }
  std::vector<spot> valid_spots;
  double x,y;
  const double threshold=0.1d;   //to be revised

  //get valid input x,y position 
  for(int i=0;i<720;i++){
    xy_data>>x>>y;
    if(( x != 0 || y!=0) && (std::isnormal(x) && std::isnormal(y)))     
      valid_spots.emplace_back(x,y);
  }

  std::vector<segment> segments;    // this vector contains all segment in this round of datamain
  std::vector<spot> single_segment;
  single_segment.emplace_back(valid_spots[0].x,valid_spots[0].y);


  const size_t valid_size=valid_spots.size();
  for(int i=1;i<valid_size;i++){
    if(std::sqrt(std::pow(valid_spots[i].x-valid_spots[i-1].x,2) + std::pow(valid_spots[i].y-valid_spots[i-1].y,2)) > threshold ){
      // this spot belong to a new segment 
      std::cout<<"new segment "<<single_segment.size()<<std::endl;
      segments.emplace_back(std::move(single_segment));
      single_segment.clear();
    }
    // this spot belongs to the same segment which last spot belongs to
    single_segment.push_back(valid_spots[i]);
  }
  segments.emplace_back(std::move(single_segment));
  return segments;
}


int main(){



  // load data
  // one time of looping means read 360 (one round) of data
  std::cout<<"test";
  std::vector<segment> segments = load_data(); 
  for(int i{};i<segments.size();i++){
    std::cout<<"segemnt index : "<<i<<std::endl;
    segments[i].Print_me();
    std::cout<<std::endl;
  }


}
