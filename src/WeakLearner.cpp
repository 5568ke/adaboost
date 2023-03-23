#include <string>
#include <utility>
#include <cmath>
#include "../include/segment.h"


template<typename Model>
class WeakLearner{

public:

  // _moudle_accurate is for sorting the order of weak learners , 
  // the different with _error_rate is it's unrelated with the weight of training data
  double Moudle_accurate;
  double Amount_of_say;

public:
  
  void train(std::vector<segment>& Segments,std::string Feature){
    //res.first : prediect error rate
    //res.second : vector of predict result , vector[i]=1 means Segments[i] been predict as feet, vector[i]=-1 means not feet;
    auto res= _model.Caculate_error_rate(Segments,Feature);               
    _error_rate = res.first; 
    _alpha = 0.5 * log( (1-_error_rate) / _error_rate );
    Amount_of_say=_alpha;
    modify_data_weight(Segments,std::move(res.second),_alpha);
  }
  
  int Predict_if_is_feet(const segment& Seg){
    // predict is feet  : return 1
    // preidct not feet : return -1
    return _model.Predict(Seg);     
  }


private:
  double _error_rate;
  double _alpha;
  Model _model;

private:
  void modify_data_weight(std::vector<segment>& Segments,std::vector<int>&& Predict_result){
    for(int index{};index<Segments.size();index++)
      Segments[index].Modify_weight(_alpha,Predict_result[index]);
  }
};
