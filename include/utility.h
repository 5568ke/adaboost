#ifndef _UTILITY_H
#define _UTILITY_H
#include<vector>
#include<unordered_map>
#include"../include/segment.h"
#include"../src/WeakLearner.h"


std::pair<std::vector<segment>,std::vector<std::vector<segment>>> load_data();
void Normolized_data_weight(std::vector<segment>&);
void Show_Predict_Animation(const std::vector<double>& ,const std::vector<double>&,const std::vector<double>&,const std::vector<double>&);
void Show_Predict_Result(std::unordered_map<std::string,int>&,std::string);
void Get_Predict_Result(const segment&,std::unordered_map<std::string,int>&,std::vector<double>&,
                        std::vector<double>&,std::vector<double>&,std::vector<double>&,std::vector<WeakLearner>&);
#endif
