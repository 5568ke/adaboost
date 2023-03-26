#ifndef _UTILITY_H
#define _UTILITY_H
#include<vector>
#include<unordered_map>
#include"../include/segment.h"


std::pair<std::vector<segment>,std::vector<std::vector<segment>>> load_data();
void Normolized_data_weight(std::vector<segment>&);
void Show_Predict_Animation(const std::vector<double>& ,const std::vector<double>&,const std::vector<double>&,const std::vector<double>&);
void Show_Predict_Result(double,double,double,double);void Get_Predict_Result(const segment& seg,std::unordered_map<std::string,int>& dict, std::vector<double>& Is_feet_vec_x,
                        std::vector<double>& Is_feet_vec_y,std::vector<double>& Not_feet_vec_x,std::vector<double>& Not_feet_vec_y);
#endif
