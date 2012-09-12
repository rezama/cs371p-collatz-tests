// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------
 
// --------
// includes
// --------
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <map> // for lazy-cache system
 
// ------------
// collatz_read
// ------------
/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}
 
// ------------
// collatz_eval_cache_helper
// ------------
/**
 * @param n, an integer >
 * @param j the end of the range, inclusive
 * @return the cycle length of n
 */
 
int collatz_eval_rec_helper(long long n, std::map<int,int> &cache) {
    //assert n>0, also will determine if long overflow
    assert(n>0);
    // Check cache previously calculated cycle length
    //cache size is 100000
    	if(n<100000 && cache.find((int)n) != cache.end())
    	{
				return cache[(int)n];
    	}
    
    // Calculate the cycle length
    int cycleLength = 0;
    if (n == 1)
       cycleLength = 1;
    else if (n%2==0)
       cycleLength = collatz_eval_rec_helper(n >> 1,cache)+1;
    else
       cycleLength = collatz_eval_rec_helper(n+(n>>1)+1,cache)+2;
    //save to cache
	if(n<100000 && cache.find((int)n) == cache.end())
       cache[(int) n] = cycleLength;
    //get out of here!
    assert(cycleLength>0);
    return cycleLength;
}
// ------------
// collatz_eval
// ------------
/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    
    //insure that i>j, else swap operators
    if(j<i){
   		i = i^j;
   		j = i^j;
   		i = i^j;
    }
    if(i<(j>>1))
    	i=((j>>1));
    //max stores highest cycle length, temp store current cycle length
	int max = 0;
	int temp = -1;
	
	////////initialize cache////
	std::map<int,int> cache;
    
    //loop from i to j, comparing the cycle lengths and capturing the max
	for (int curNum=i; curNum<=j; curNum++) {
		//helper method, contains collatz algorithm
		temp = collatz_eval_rec_helper(curNum,cache);
		//capture the largest cycle length
		if(temp>max)
			max=temp;
	}
	//return the max
    assert(max > 0);
    return max;
}
// -------------
// collatz_print
// -------------
 
/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}
 
// -------------
// collatz_solve
// -------------
/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
 
 