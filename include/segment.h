#ifndef _SEGMENT_H
#define _SEGMENT_H

#include "spot.h"
#include <string>
#include <vector>

class segment{

public:

  segment(std::vector<spot>&&);
  void Caculate_features();
  void Print_me();
  void Normolized(double);
  double Modify_weight(double,int);
  const double Get_feature(std::string) const;
  

public:
  int Is_feet;   // 1 : is feet    ,     -1 : not feet

private:


  int _spots_number;
  double _standard_deviation;
  double _width;
  double _circularity;
  double _radius;
  double _weight;
  std::vector<spot> _spots;

private:
  void caculate_standard_deviation();
  void caculate_width();
  void caculate_circularity_and_radius();
};

#endif
