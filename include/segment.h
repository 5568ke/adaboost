#ifndef _SEGMENT_H
#define _SEGMENT_H

#include <string>
#include <vector>
#include "spot.h"
#include "../ThirdParty/Eigen/Dense"

class segment{

public:

  segment(std::vector<spot>&&);
  void Initialize_weight(double);
  void Caculate_features();
  void Caculate_features(spot,spot);
  void Print_me();
  void Normolized(double);
  double Modify_weight(double,int);
  const double Get_weight() const;
  const double Get_feature(std::string) const;
  const std::vector<spot> Get_Spots() const ;
  const spot Get_mid_point()const ;
  const spot Get_first_point()const ;
  const spot Get_last_point()const  ;
  

public:
  int Is_feet;   // 1 : is feet    ,     -1 : not feet

private:


  int _spots_number;
  double _standard_deviation;
  double _width;
  double _circularity;
  double _radius;
  double _weight;
  double _distance;
  double _jump_distance_prev;
  double _jump_distance_next;
  double _linearity;
  std::vector<spot> _spots;

private:
  void caculate_standard_deviation();
  void caculate_width();
  void caculate_circularity_and_radius();
  void caculate_linearity();
  void caculate_jump_distance(spot,spot);
};

#endif
