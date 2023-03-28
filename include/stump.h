#ifndef _STUMP_H
#define _STUMP_H
#include<iostream>
#include<string>
#include<vector>
#include "segment.h"
#include "FWL.h"

class stump{
public:

  stump(std::string);
  std::pair<double,std::vector<int>> Train(const std::vector<segment>&);
  int Predict(const segment&);
  std::string Get_Feature();
  std::string Get_Choose();


private:
  std::string _feature_type;
  std::vector<int> _predict_result;
  double _critical_point;
  double _max_r;
  int predict_with_point_less_than(double , const double);
  int predict_with_point_greater_than(double , const double);
  std::string _greater_or_less;
private:
  void try_point(double  , const std::vector<FWL>& ,std::vector<int>&);
  
};


#endif
