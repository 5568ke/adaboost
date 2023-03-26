#include <vector>
#include <iostream>
#include <math.h>
#include "../ThirdParty/Eigen/Dense"
#include "../include/spot.h"
#include "../include/segment.h"

segment::segment(std::vector<spot>&& Spots) 
: _spots_number(Spots.size()) , _spots(std::move(Spots))
{
  Caculate_features();
}

void segment::Caculate_features(){
  caculate_standard_deviation();
  caculate_width();
  caculate_circularity_and_radius();
}

void segment::Initialize_weight(double Weight){
  _weight=Weight;
}

const double segment::Get_feature(std::string Feature_type) const{
  if(Feature_type=="spots_number") return _spots_number;
  if(Feature_type=="stand_deviation") return _standard_deviation;
  if(Feature_type=="width") return _width;
  if(Feature_type=="circularity") return _circularity;
  if(Feature_type=="radius") return _radius;
}

const double segment::Get_weight() const{
  return _weight;
}

void segment::Print_me(){
  // for(auto& spot : _spots)
    // spot.Print_me();
  std::cout<<"is feet : "<<Is_feet<<std::endl;
  std::cout<<"spots_number : "<<_spots_number<<std::endl;
  std::cout<<"stand_deviation : "<<_standard_deviation<<std::endl;
  std::cout<<"width : "<<_width<<std::endl;
  std::cout<<"circularity : "<<_circularity<<std::endl;
  std::cout<<"radius : "<<_radius<<std::endl;

  std::cout<<std::endl<<std::endl;
}

double segment::Modify_weight(double Alpha , int Predict_result){
  double ratio = exp(-Alpha * (double)Predict_result * (double)Is_feet) ; 
  _weight *= ratio; 
  // std::cout<<"weight : "<<_weight<<" correct or not : "<<Predict_result * Is_feet<<std::endl;
  return _weight;
}

void segment::Normolized(double Weight_sum){
  _weight/=Weight_sum;
}

void segment::caculate_standard_deviation(){
  if(_spots_number==1){
    _standard_deviation=0;
    return;
  }
  float mean_x{},mean_y{},square_diff_sum{};
  for(const auto& spot : _spots){
    mean_x+=spot.x;
    mean_y+=spot.y;
  }
  mean_x/=_spots_number;
  mean_y/=_spots_number;
  for(const auto& spot : _spots){
    square_diff_sum += (spot.x - mean_x) * (spot.x - mean_x) + (spot.y - mean_y) * (spot.y - mean_y);
  }
  square_diff_sum /= _spots_number;
  _standard_deviation=std::sqrt(square_diff_sum);
}

void segment::caculate_width(){
  _width=std::sqrt(
    std::pow(_spots[_spots_number-1].x-_spots[0].x,2) + 
    std::pow(_spots[_spots_number-1].y-_spots[0].y,2)  
  ); 
}
void segment::caculate_circularity_and_radius(){
  Eigen::MatrixXd a(_spots_number,3);
  Eigen::VectorXd b(_spots_number);
  for(int index{};index<_spots_number;index++){
    a(index,0)=-2*_spots[index].x;
    a(index,1)=-2*_spots[index].y;
    a(index,2)=1;
    b(index) = -pow(_spots[index].x,2)-pow(_spots[index].y,2);
  }
  Eigen::MatrixXd result((a.transpose()*a).inverse()*(a.transpose())*b);
  double center_x_pos{result(0,0)},center_y_pos{result(1,0)};
  _radius= std::sqrt(-(result(2,0)-pow(center_x_pos,2)-pow(center_y_pos,2)));
  for(int index{};index<_spots_number;index++)
    _circularity+=pow(_radius-std::sqrt(pow(center_x_pos-_spots[index].x,2)+pow(center_y_pos-_spots[index].y,2)),2);
}
