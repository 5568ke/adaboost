#include <iostream>
#include "../include/spot.h"

spot::spot(double X,double Y) : x(X),y(Y) {}

void spot::Print_me(){
  std::cout<<" x : "<<x<<" y : "<<y<<std::endl;
}
