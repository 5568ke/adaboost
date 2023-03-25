#include"../include/stump.h"
#include<float.h>
#include<algorithm>



std::pair<double,std::vector<int>> stump::Train(const std::vector<segment>& segments){
  int max_index{},min_index{};
  const size_t segments_number{segments.size()};
  std::vector<double> feature_vec;
  for(const auto& seg : segments)
    feature_vec.emplace_back(seg.Get_feature(_feature_type));

  auto  it_pair=std::minmax_element(feature_vec.begin(),feature_vec.end());
  const double min=*(it_pair.first),max=*(it_pair.second);
  const double distance{};
  const int step_num=segments_number*100;
  const int step_size=distance/(step_num+1);

  for(double t_critical_point{min}; t_critical_point<max; t_critical_point+=step_size)
    try_point(t_critical_point,segments);
    
  
  

}
int stump::Predict(const segment& seg){
  double t_feature{seg.Get_feature(_feature_type)};
  if(t_feature >= _critical_point) return 1;
  return -1;
};

void stump::try_point(double Critical_point , const std::vector<segment>& segments){
  double t_error_rate{},weight_sum{},correct_sum{};
  const size_t segments_number=segments.size();
  _critical_point=Critical_point;
  for(size_t index{};index<segments_number;index++){
    double t_weight=segments[index].Get_weight();
    weight_sum+= t_weight;
    correct_sum+= Predict(segments[index]) * segments[index].Is_feet * t_weight;
  }
  t_error_rate = correct_sum / weight_sum;
  if(t_error_rate < _min_error_rate){
    _min_error_rate=t_error_rate;
    _critical_point=Critical_point;
  }
};
