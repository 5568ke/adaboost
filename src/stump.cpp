#include"../include/stump.h"
#include<float.h>
#include<algorithm>



stump::stump(const std::string& Feature_type)
:_feature_type(Feature_type) , _max_r(std::numeric_limits<double>::min())
{
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




std::pair<double,std::vector<int>> stump::Train(const std::vector<segment>& Segments){
  const size_t segments_number{Segments.size()};
  std::vector<int> predict_result_vec(segments_number);

  //make Feature,Weight,Label vector
  std::vector<FWL> FWL_vec(segments_number);
  for(int index{};index<segments_number;index++){
    FWL_vec[index].Feature=Segments[index].Get_feature(_feature_type);
    FWL_vec[index].Weight=Segments[index].Get_weight();
    FWL_vec[index].Label=Segments[index].Is_feet;
    FWL_vec[index].Index=index;
  }
  std::sort(begin(FWL_vec),end(FWL_vec),[](FWL a ,FWL b){ return a.Feature < b.Feature;});

  //try all point between two segment's specific feature
  for(int index{};index<segments_number-1;index++)
    try_point( (double)(FWL_vec[index].Feature+FWL_vec[index+1].Feature)/2 , FWL_vec, predict_result_vec);

  return std::make_pair(_max_r,predict_result_vec);
}


void stump::try_point(double Critical_point , const std::vector<FWL>& FWLs, std::vector<int>& Predict_result_vec){  
  double t_r{};
  const size_t segments_number=FWLs.size();
  std::vector<int> t_prediect_result_vec(segments_number);

  for(size_t index{};index<segments_number;index++){
    double t_weight=FWLs[index].Weight;
    int t_predict_result=predict_with_point_less_than(FWLs[index].Feature,Critical_point);
    t_r+= t_weight * t_predict_result * FWLs[index].Label;
    t_prediect_result_vec[FWLs[index].Index]=t_predict_result;
  }
  if(t_r>_max_r){
    _max_r=t_r;
    _critical_point=Critical_point;
    Predict_result_vec=t_prediect_result_vec;
    _greater_or_less="less";
  }

  t_r=0;
  for(size_t index{};index<segments_number;index++){
    double t_weight=FWLs[index].Weight;
    double t_predict_result=predict_with_point_greater_than(FWLs[index].Feature,Critical_point);
    t_r+= t_weight * t_predict_result * FWLs[index].Label;
    t_prediect_result_vec[FWLs[index].Index]=t_predict_result;
  }
  if(t_r>_max_r){
    _max_r=t_r;
    _critical_point=Critical_point;
    Predict_result_vec=t_prediect_result_vec;
    _greater_or_less="greater";
  }
};


int stump::predict_with_point_less_than(double Feature,const double Critical_point){
  if(Feature < Critical_point) return 1;
  return -1;
};


int stump::predict_with_point_greater_than(double Feature,const double Critical_point){
  if(Feature > Critical_point) return 1;
  return -1;
}
