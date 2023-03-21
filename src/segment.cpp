#include<vector>
#include<iostream>
#include<math.h>
#include"spot.h"

class segment{

public:

  segment(std::vector<spot>&& spots) 
  : _spots(std::move(spots)),_spots_number(spots.size())
  {
    Caculate_features();

  };

  void Caculate_features(){
    caculate_standard_deviation();
    caculate_width();
    caculate_circularity();
    caculate_radius();
  };

public:
  void Print_me(){
    for(auto& spot : _spots)
      spot.Print_me();
  }




private:

  std::vector<spot> _spots;

  int _spots_number;
  float _standard_deviation;
  float _width;
  float _circularity;
  float _radius;
  float _weigt;
  bool _is_

private:
  void caculate_standard_deviation(){
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
  };

  void caculate_width(){

  };
  void caculate_circularity(){

  };
  void caculate_radius(){

  };
  
};
