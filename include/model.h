#include<vector>
#include<string>
#include<utility>
#include"segment.h"

class model{
public:
  
  model(std::string FeatureType);
  virtual void Train(const std::vector<segment>& Segments);
  int Predict(const segment& Seg);
  std::pair<double,std::vector<int>> Caculate_error_rate(std::vector<std::vector<segment>>& Segments);

private:
  std::string _feature_type;
};
