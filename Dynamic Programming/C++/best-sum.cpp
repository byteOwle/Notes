#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

// Brute-Force Solution
// std::vector<int> bestSum(int targetSum,std::vector<int> numbers)
// {
//   if(targetSum == 0) return {};
//   if(targetSum < 0) return {NULL};

//  std::vector<int> shortestCombination = {NULL};

//   for(auto num: numbers){
//     int remainder = targetSum - num;
//     auto remainderCombination = bestSum(remainder, numbers);
//     auto nullfind = find(remainderCombination.begin(),remainderCombination.end(), NULL);
//     if(nullfind == remainderCombination.end())
//     {
//      std::vector<int> combination;
//       for(auto elements: remainderCombination)
//         combination.push_back(elements);
//       combination.push_back(num);

//       nullfind = find(shortestCombination.begin(),shortestCombination.end(), NULL);
//       auto end = shortestCombination.end();
//       if(nullfind != end || combination.size() < shortestCombination.size()){
//         shortestCombination = combination;
//       }
//     }
//   }

//   return shortestCombination;
// }


// Memoized Solution
std::vector<int> bestSum(int targetSum, std::vector<int> numbers)
{
  static std::map<int, std::vector<int>> memo = {};

  if(memo.find(targetSum) != end(memo)) return memo[targetSum];
  if(targetSum == 0) return {};
  if(targetSum < 0) return {NULL};

  std::vector<int> shortestCombination = {NULL};

  for(auto num: numbers){
    int remainder = targetSum - num;
    auto remainderCombination = bestSum(remainder, numbers);
    auto nullfind = find(remainderCombination.begin(),remainderCombination.end(), NULL);
    if(nullfind == remainderCombination.end())
    {
      std::vector<int> combination;
      for(auto elements: remainderCombination)
        combination.push_back(elements);
      combination.push_back(num);

      nullfind = find(shortestCombination.begin(),shortestCombination.end(), NULL);
      auto end = shortestCombination.end();
      if(nullfind != end || combination.size() < shortestCombination.size()){
        shortestCombination = combination;
      }
    }
  }

  memo[targetSum] = shortestCombination;
  return shortestCombination;
}

int main(){

  std::vector<int> path = bestSum(100, {1, 2, 5, 25});
  std::cout << "[ ";
  for(int elements: path)
    std::cout << elements << " ";

	std::cout << "]\n";

	return 0;
}
