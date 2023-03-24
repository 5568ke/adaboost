#ifndef _STUMP_H
#define _STUMP_H
#include"model.h"
#include<vector>

class stump : model {
public:
  std::pair<double,std::vector<int>> Train(const std::vector<segment>&) override;
  int Predict(const segment&) override;


private:
  double _critical_point;
  double _min_error_rate;
  std::vector<int> _predict_result;

private:
  void try_point(double  , const std::vector<segment>& );

 
};


#endif
