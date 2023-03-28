#ifndef _STUMP_H
#define _STUMP_H
#include<iostream>
#include<string>
#include<vector>
#include "segment.h"
#include "FWL.h"

class stump{
public:
  stump(const std::string&);
  std::pair<double,std::vector<int>> Train(const std::vector<segment>&);
  int Predict(const segment&);
private:
  std::string _feature_type;
  std::vector<int> _predict_result;
  double _critical_point;
  double _max_r;
  std::string _greater_or_less;
private:
  void try_point(const double,const std::vector<FWL>& ,std::vector<int>&);
  int predict_with_point_less_than(const double , const double);
  int predict_with_point_greater_than(const double , const double);
};


#endif
