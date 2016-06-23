// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------
// --------
// includes
// --------
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
using namespace std;
#define CACHE_SIZE 250000 // Comment out this section to use the simple solution (uncached)
#ifdef CACHE_SIZE
int values[CACHE_SIZE] = {0};
#endif
// ------------
// collatz_read
// ------------
bool collatz_read(istream &r, int &i, int &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}
// ------------
// collatz_eval
// ------------
int collatz_eval(int start, int end) {
  assert(
      (start > 0 && start < 1000000) &&
      (end > 0 && end < 1000000)); // pre-condition: must be within test range
  int max_cycle_length = 1;
  if (start > end) {
    // using swap trick from class
    start ^= end;
    end ^= start;
    start ^= end;
  }
  int orig_start = start;
  int orig_end = end;
#ifndef CACHE_SIZE
  for (int diff = start; diff <= end; diff++) {
    int curr_length = 1;
    int num = diff;
    while (num > 1) {
      if ((num % 2) == 1)
        num = (3 * num) + 1;
      else
        num = num / 2;
      curr_length++;
    }
    if (curr_length > max_cycle_length)
      max_cycle_length = curr_length;
  }
#endif
// We know that any given number n has mcl of mcl(n/2) + 1, so we will exploit
// this fact
// Optimized implementation
// This was so much easier in Python, lol.
#ifdef CACHE_SIZE
  int begin = start;
  if (start < (end / 2))
    begin = end / 2;
  for (int diff = begin; diff <= end; ++diff) 
  {
    int curr_length = 1;
    int num = diff;
    while (num > 1) {
      // Check for existing variable in cache FIRST to save time
      if (num < CACHE_SIZE) {
      	if(values[num]!=0){
          curr_length += values[num] - 1; // Subtract 1 because of curr_length
         break;
      	}
      } 
      if ((num % 2) == 1){
        num = num + (num >> 1) + 1;  //Changed to be (3n+1)/2 from class
        curr_length += 2;
      }
      else{
        num = num / 2;
        ++curr_length;
      }
      //curr_length+=2;
    }
    if (diff < CACHE_SIZE)
      values[diff] = curr_length;
    if (curr_length > max_cycle_length)
      max_cycle_length = curr_length;
  }
#endif
  assert(start = orig_start); // post-condition: start/end values not changed by
                              // method execution
  assert(end = orig_end);
  assert(max_cycle_length > 0); // post-condition: max_cycle_length started as 1
                                // and cannot be less than
  return max_cycle_length;
}
// -------------
// collatz_print
// -------------
void collatz_print(ostream &w, int i, int j, int v) {
  w << i << " " << j << " " << v << endl;
}
// -------------
// collatz_solve
// -------------
void collatz_solve(istream &r, ostream &w) {
  int i;
  int j;
  for (int q = 0; q < CACHE_SIZE; q++){
  	values[q] = 0;
  }
  while (collatz_read(r, i, j)) {
    const int v = collatz_eval(i, j);
    collatz_print(w, i, j, v);
  }
}
// ----
// main
// ----
int main() {
  using namespace std;
  collatz_solve(cin, cout);
  return 0;
}
