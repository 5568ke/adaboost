#include <vector>
#include <iostream>
#include <math.h>
#include "spot.h"
#include "segment.h"

segment::segment(std::vector<spot>&& spots) 
: _spots(std::move(spots)),_spots_number(spots.size())
{
  Caculate_features();
}

void segment::Caculate_features(){
  caculate_standard_deviation();
  caculate_width();
  caculate_circularity();
  caculate_radius();
}

void segment::Print_me(){
  for(auto& spot : _spots)
    spot.Print_me();
}

void segment::caculate_standard_deviation(){
  float mean_x,mean_y,square_diff_sum=0;
  for(auto& spot : _spots){
    mean_x+=spot.x;
    mean_y+=spot.y;
  }
  mean_x/=_spots_number;
  mean_y/=_spots_number;
  for(auto& spot : _spots){
    square_diff_sum += (spot.x - mean_x) * (spot.x - mean_x) + (spot.y - mean_y) * (spot.y - mean_y);
  }
  square_diff_sum /= _spots_number;
  _standard_deviation=sqrt(square_diff_sum);
}

void segment::caculate_width(){}
void segment::caculate_circularity(){}
void segment::caculate_radius(){}