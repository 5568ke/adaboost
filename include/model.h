#ifndef _MODEL_H
#define _MODEL_H
#include<vector>
#include<string>
#include<utility>
#include"segment.h"
class model{
public:
  
  virtual std::pair<double,std::vector<int>> Train(const std::vector<segment>&);
  virtual int Predict(const segment&);

protected:
  std::string _feature_type;
};
#endif // !_MODEL_H
