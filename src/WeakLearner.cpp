#include"segment.h"
#include<cmath>


template<typename Model>
class WeakLearner{

public:

  // _moudle_accurate is for sorting the order of weak learners , 
  // the different with _error_rate is it's unrelated with the weight of training data
  double Moudle_accurate;

public:
  
  void train(vector<segment>& Segments,std::string Feature){
    _error_rate = _model.caculate_error_rate(Segments,Feature); 
    _amount_of_say = 0.5d * log( (1-_error_rate) / _error_rate );
  }


private:
  double _amount_of_say;
  double _error_rate;
  Moudle _model;

};
