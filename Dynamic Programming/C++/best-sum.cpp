#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

void print(std::vector<int> input){
  std::cout << "[";
  for(int i = 0; i < input.size(); i++){
      std::cout << input[i];
      if(i != input.size()-1)
        std::cout << ", ";
  }

  std::cout << "]\n";
}

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
struct BestSum{
  std::vector<int> bestSum(int targetSum, std::vector<int> numbers){
    std::map<int, std::vector<int>> memo = {};
    return bestSum(targetSum, numbers, memo);
  }

  private:
    std::vector<int> bestSum(int targetSum, std::vector<int> numbers, std::map<int, std::vector<int>>& memo)
    {
      if(memo.find(targetSum) != end(memo)) return memo[targetSum]; 
      if(targetSum == 0) return {};
      if(targetSum < 0) return {NULL};

      std::vector<int> shortestCombination = {NULL};

      for(auto num: numbers){
        int remainder = targetSum - num;
        auto remainderCombination = bestSum(remainder, numbers, memo);
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
};



int main(){

  std::vector<int> path;
  BestSum Test;
  // Test cases
  path = Test.bestSum(7, {5, 3, 4, 7}); // [7]
  print(path);
  path = Test.bestSum(8, {2, 3, 5}); // [3, 5]
  print(path);
	path = Test.bestSum(8, {1, 4, 5}); // [4, 4]
  print(path);
  path = Test.bestSum(100, {1, 2, 5, 25}); // [25, 25, 25, 25]
  print(path);
  return 0;
}
