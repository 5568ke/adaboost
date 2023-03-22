#include<vector>
#include<string>
#include<utility>

class model{
public:
  std::pair<double,std::vector<int>> Caculate_error_rate(std::vector<std::vector<segment>>& Segments);
};
