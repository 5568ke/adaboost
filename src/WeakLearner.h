#include <string>
#include <iostream>
#include <utility>
#include <cmath>
#include "../include/segment.h"
#include "../include/stump.h"


class WeakLearner{

public:

  // _moudle_accurate is for sorting the order of weak learners , 
  // the different with _error_rate is it's unrelated with the weight of training data
  double Moudle_accurate;
  double Amount_of_say;
  double R;

public:

  WeakLearner(std::vector<segment>& Segments,std::string Feature_type)
  :_model(Feature_type)
  {
    train(Segments,Feature_type);
  }
  
  void train(std::vector<segment>& Segments,std::string Feature){
    //res.first : prediect error rate
    //res.second : vector of predict result , vector[i]=1 means Segments[i] been predict as feet, vector[i]=-1 means not feet;
    auto res= _model.Train(Segments);               
    R = res.first; 
    _alpha = 0.5 * std::log( ((double)1+R) / ((double)1-R));
    Amount_of_say=_alpha;
    _prediect_result=std::move(res.second);
  }
  
  int Predict_if_is_feet(const segment& Seg){
    // predict is feet  : return 1
    // preidct not feet : return -1
    return _model.Predict(Seg);     
  }

  void been_chosen(std::vector<segment>& Segments){
    update_data_weight(Segments,std::move(_prediect_result));
  }

  std::string Get_Feature(){
    return _model.Get_Feature();
  }



private:
  double _alpha;
  stump _model;

  std::vector<int> _prediect_result;

private:
  void update_data_weight(std::vector<segment>& Segments,std::vector<int>&& Predict_result){
    // update data weight
    double weight_sum=0;
    for(int index{};index<Segments.size();index++)
      weight_sum+=Segments[index].Modify_weight(_alpha,Predict_result[index]);

    for(int index{};index<Segments.size();index++)
      Segments[index].Normolized(weight_sum);

  }
};
