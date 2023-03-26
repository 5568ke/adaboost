
#include"../include/stump.h"
#include<float.h>
#include<algorithm>


stump::stump(std::string Feature_type)
:_feature_type(Feature_type) , _max_r(std::numeric_limits<double>::min())
{
}

std::string stump::Get_Choose(){
  return _greater_or_less;
}

int stump::Predict(const segment& seg){
  double t_feature{seg.Get_feature(_feature_type)};
  if(_greater_or_less=="less"){
    if(t_feature < _critical_point) return 1;
    return -1;
  }else if(_greater_or_less=="greater"){
    if(t_feature > _critical_point) return 1;
    return -1;
  }
}

std::string stump::Get_Feature(){
  return _feature_type;
}

std::pair<double,std::vector<int>> stump::Train(const std::vector<segment>& segments){
  int max_index{},min_index{};
  const size_t segments_number{segments.size()};
  std::vector<double> feature_vec;
  std::vector<int> predict_result_vec(segments_number);
  for(const auto& seg : segments)
    feature_vec.emplace_back(seg.Get_feature(_feature_type));

  auto  it_pair=std::minmax_element(feature_vec.begin(),feature_vec.end());
  const double min=*(it_pair.first)/1.1,max=*(it_pair.second)*1.1;
  const double distance{max-min};
  const int step_num=segments_number*5;
  const double step_size=distance/(step_num+1);

  for(double t_critical_point{min}; t_critical_point<max; t_critical_point+=step_size)
    try_point(t_critical_point,segments,predict_result_vec);


  return std::make_pair(_max_r,predict_result_vec);
}
int stump::predict_with_point_less_than(const segment& seg,const int Critical_point){
  double t_feature{seg.Get_feature(_feature_type)};
  if(t_feature < Critical_point) return 1;
  return -1;
};

int stump::predict_with_point_greater_than(const segment& seg,const int Critical_point){
  double t_feature{seg.Get_feature(_feature_type)};
  if(t_feature > Critical_point) return 1;
  return -1;
}

void stump::try_point(double Critical_point , const std::vector<segment>& Segments, std::vector<int>& Predict_result_vec){  
  double t_max_r{};
  const size_t segments_number=Segments.size();
  std::vector<int> t_prediect_result_vec(segments_number);

  for(size_t index{};index<segments_number;index++){
    double t_weight=Segments[index].Get_weight();
    double t_predict_result=predict_with_point_less_than(Segments[index],Critical_point);
    t_max_r+= t_weight * t_predict_result * Segments[index].Is_feet;
    t_prediect_result_vec[index]=t_predict_result;
  }
  // std::cout<<"t_max_r : "<<t_max_r<<std::endl;
  if(t_max_r>_max_r){
    _max_r=t_max_r;
    _critical_point=Critical_point;
    Predict_result_vec=t_prediect_result_vec;
    _greater_or_less="less";
  }

  t_max_r=0;
  for(size_t index{};index<segments_number;index++){
    double t_weight=Segments[index].Get_weight();
    double t_predict_result=predict_with_point_greater_than(Segments[index],Critical_point);
    t_max_r+= t_weight * t_predict_result * Segments[index].Is_feet;
    t_prediect_result_vec[index]=t_predict_result;
  }
  // std::cout<<"t_max_r : "<<t_max_r<<std::endl;
  if(t_max_r>_max_r){
    _max_r=t_max_r;
    _critical_point=Critical_point;
    Predict_result_vec=t_prediect_result_vec;
    _greater_or_less="greater";
  }
};
