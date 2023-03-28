#include <cmath>
#include <vector>
#include <iostream>
#include <math.h>
#include "../ThirdParty/Eigen/Dense"
#include "../include/spot.h"
#include "../include/segment.h"

segment::segment(std::vector<spot>&& Spots) 
: _spots_number(Spots.size()) , _spots(std::move(Spots)) ,_circularity(0),_jump_distance_next(0),_jump_distance_prev(0)
{
}

void segment::Caculate_features(spot _prev_last_point,spot _next_first_point ){
  caculate_standard_deviation();
  caculate_width();
  caculate_circularity_and_radius();
  caculate_jump_distance(_prev_last_point, _next_first_point);
  caculate_linearity();
}

void segment::Caculate_features(){
  caculate_standard_deviation();
  caculate_width();
  caculate_circularity_and_radius();
  caculate_linearity();
}

void segment::Initialize_weight(double Weight){
  _weight=Weight;
}

const std::vector<spot> segment::Get_Spots()const{
  return _spots;
}

const double segment::Get_weight() const{
  return _weight;
}

const spot segment::Get_first_point() const{
  return _spots[0];
}

const spot segment::Get_last_point() const{
  return _spots[_spots_number-1];
}

const double segment::Get_feature(std::string Feature_type) const{
  if(Feature_type=="spots_number") return _spots_number;
  if(Feature_type=="stand_deviation") return _standard_deviation;
  if(Feature_type=="width") return _width;
  if(Feature_type=="circularity") return _circularity;
  if(Feature_type=="radius") return _radius;
  if(Feature_type=="distance") return _distance;
  if(Feature_type=="jump_distance_next") return _jump_distance_next;
  if(Feature_type=="jump_distance_prev") return _jump_distance_prev;
  if(Feature_type=="linearity") return _linearity;
}



double segment::Modify_weight(double Alpha , int Predict_result){
  double ratio = exp(-Alpha * (double)Predict_result * (double)Is_feet) ; 
  _weight *= ratio; 
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
  if(_spots_number==1 && Is_feet==1){
    _circularity=1;
    _radius=0;
    _distance=std::sqrt(pow(_spots[0].x,2)+pow(_spots[0].y,2));
    return;
  }
  // Eigen::MatrixXd a(_spots_number,3);
  // Eigen::VectorXd b(_spots_number);
  // for(int index{};index<_spots_number;index++){
  //   a(index,0)=-2*_spots[index].x;
  //   a(index,1)=-2*_spots[index].y;
  //   a(index,2)=1;
  //   b(index) = -pow(_spots[index].x,2)-pow(_spots[index].y,2);
  // }
  // Eigen::MatrixXd result((a.transpose()*a).inverse()*(a.transpose())*b);
  // double center_x_pos{result(0,0)},center_y_pos{result(1,0)};
  // _radius= std::sqrt(-(result(2,0)-pow(center_x_pos,2)-pow(center_y_pos,2)));
  // for(int index{};index<_spots_number;index++)
  //   _circularity+=pow(_radius-std::sqrt(pow(center_x_pos-_spots[index].x,2)+pow(center_y_pos-_spots[index].y,2)),2);
   
  Eigen::MatrixXd t_spots_matrix(_spots_number,2);
  for(int index{};index<_spots_number;index++){
    t_spots_matrix(index,0)=_spots[index].x;
    t_spots_matrix(index,1)=_spots[index].y;
  }

  Eigen::MatrixXd Seg=t_spots_matrix;

  const auto &x = Seg.col(0);
  const auto &y = Seg.col(1);

    Eigen::MatrixXd A(Seg.rows(), 3);
    Eigen::MatrixXd b(Seg.rows(), 1);

    A << -2 * x, -2 * y, Eigen::MatrixXd::Ones(Seg.rows(), 1);
    b << (-1 * x.array().square() - y.array().square());

    Eigen::MatrixXd x_p = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);
    auto xc = x_p(0);
    auto yc = x_p(1);

    _radius = std::sqrt(std::pow(xc, 2) + std::pow(yc, 2) - x_p(2));
    _circularity = ((_radius - ((xc - x.array()).square() + (yc - y.array()).square()).sqrt()).square()).sum();
    _distance = std::sqrt(std::pow(xc, 2) + std::pow(yc, 2));
}

void segment::caculate_jump_distance(spot _prev_last_point,spot _next_first_point){
  _jump_distance_next=std::sqrt( pow(_spots[_spots_number-1].x - _next_first_point.x,2)
                               + pow(_spots[_spots_number-1].y - _next_first_point.y,2));
  _jump_distance_prev=std::sqrt( pow(_spots[0].x - _prev_last_point.x,2)
                               + pow(_spots[0].y - _prev_last_point.y,2));
}

  
void segment::caculate_linearity() {

    Eigen::MatrixXd t_spots_matrix(_spots_number,2);
    for(int index{};index<_spots_number;index++){
      t_spots_matrix(index,0)=_spots[index].x;
      t_spots_matrix(index,1)=_spots[index].y;
    }

    Eigen::MatrixXd segment=t_spots_matrix;

    int n = segment.rows(); // number of points in the segment
    double sum_x = segment.col(0).sum(); // sum of x-coordinates
    double sum_y = segment.col(1).sum(); // sum of y-coordinates
    double sum_x_squared = (segment.col(0).array() * segment.col(0).array()).sum(); // sum of squares of x-coordinates
    double sum_xy = (segment.col(0).array() * segment.col(1).array()).sum(); // sum of products of x- and y-coordinates
    
    double det = n * sum_x_squared - sum_x * sum_x;
    double a = (n * sum_xy - sum_x * sum_y) / det; // slope
    double b = (sum_x_squared * sum_y - sum_x * sum_xy) / det; // y-intercept
    
    double rss = 0.0; // residual sum of squares
    for (int i = 0; i < n; i++) {
        double x = segment(i, 0);
        double y = segment(i, 1);
        double dist = std::abs(y - a * x - b) / std::sqrt(1.0 + a * a);
        rss += dist * dist;
    }
    _linearity=rss;    
}
