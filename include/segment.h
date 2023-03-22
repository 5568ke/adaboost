#ifndef _SEGMENT_H
#define _SEGMENT_H

#include "spot.h"
#include <vector>

class segment{

public:

  segment(std::vector<spot>&&);
  void Caculate_features();
  void Print_me();
  void Modify_weight(double,int);

public:
  int Is_feet;   // 1 : is feet    ,     -1 : not feet

private:

  std::vector<spot> _spots;

  int _spots_number;
  double _standard_deviation;
  double _width;
  double _circularity;
  double _radius;
  double _weight;
  

private:
  void caculate_standard_deviation();
  void caculate_width();
  void caculate_circularity();
  void caculate_radius();
};

#endif
