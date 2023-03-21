#include"spot.h"
#include<vector>

class segment{
  

public:

  segment(std::vector<spot>&& spots);
  void Caculate_features(){};
  void Print_me();

private:

  std::vector<spot> _spots;

  int _spots_number;
  float _standard_deviation;
  float _width;
  float _circularity;
  float _radius;

private:
  void caculate_standard_deviation();
  void caculate_width();
  void caculate_circularity();
  void caculate_radius();
};
