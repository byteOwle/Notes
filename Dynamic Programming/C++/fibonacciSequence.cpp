#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

// Brute force
// int fibonacci(int num){
//   if(num <= 2) return 1;

//   return fibonacci(n - 1) + fibonacci(n = 2);
// }


//memoized solution
int fibonacci(int num)
{
  static map<int, int> cache{{0, 0}, {1, 1}};

  auto found = cache.find(num);
  if (found != end(cache)) {
    // For debugging purposes, to check that the cache is doing something
    // cout << "Found in cache: " << num << " -> " << found->second << '\n';
    return found->second;
  }

  cache[num]  = fibonacci(num - 1) + fibonacci(num - 2);
  
  return cache[num];
}

int main(){
	// cout << "Fib: " << fibonacci(20) << endl;

  int input = 0, sum = 0;


  while(input <= .25){
    cout << ": ";
    cin >> input;
    if(input >= .25){
      //sum = (sum > input)? sum : input;
      cout << "true\n"; 
    } 
    else {
      sum += input;
      cout << sum << ": \n";
    }  
    cout << sum;  
    break;
  }

  cout << "out\n";




	return 0;
}