#include<iostream>
class spot{

public:
  spot(float X,float Y) : x(X),y(Y)
  {}
  void Print_me(){
    std::cout<<" x : "<<x<<" y : "<<y<<std::endl;
  }

public:
  const float x;
  const float y;
};
