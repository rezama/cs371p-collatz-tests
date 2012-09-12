// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------------

/*
To test the program:
	% ls /usr/include/cppunit/
	...
	HelperMacros.h
	...
	% locate libcppunit.a
	/usr/lib/libcppunit.a
	% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall\
		TestCollatz.c++ -o TestCollatz.c++.app
	% valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"			// TestFixture
#include "cppunit/TextTestRunner.h"			// TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
struct TestCollatz : CppUnit::TestFixture {
	// ----
	// read
	void test_read_0 () {
		istringstream r("1 10\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i ==	1);
		CPPUNIT_ASSERT(j == 10);
	}
	
	void test_read_1 () {
		istringstream r("4 1 2 34\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i ==	4);
		CPPUNIT_ASSERT(j == 1);
	}
	
	void test_read_2 () {
		istringstream r("1 20\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i ==	1);
		CPPUNIT_ASSERT(j == 20);
	}
	
	// -----------
	// cycleLength
	void test_cycleLength_0(){
		int n = 1;
		int c = cycleLength(n);
		
		CPPUNIT_ASSERT(c == 1);
	}
	
	void test_cycleLength_1(){
		int n = 2;
		int c = cycleLength(n);
		
		CPPUNIT_ASSERT(c == 2);
	}
	
	void test_cycleLength_2(){
		int n = 3;
		int c = cycleLength(n);
		
		CPPUNIT_ASSERT(c == 8);
	}
	
	void test_cycleLength_3(){
		int n = 20;
		int c = cycleLength(n);
		
		CPPUNIT_ASSERT(c == 8);
	}

	// ----
	// eval
	void test_eval_1 () {
		const int v = collatz_eval(1, 10);
		if(DEBUG) cerr << "v = " << v << endl;
		CPPUNIT_ASSERT(v == 20);}

	void test_eval_2 () {
		const int v = collatz_eval(100, 200);
		if(DEBUG) cerr << "v = " << v << endl;
		CPPUNIT_ASSERT(v == 125);}

	void test_eval_3 () {
		const int v = collatz_eval(201, 210);
		if(DEBUG) cerr << "v = " << v << endl;
		CPPUNIT_ASSERT(v == 89);}

	void test_eval_4 () {
		const int v = collatz_eval(900, 1000);
		if(DEBUG) cerr << "v = " << v << endl;
		CPPUNIT_ASSERT(v == 174);}

	// -----
	// print
	void test_print_0 () {
		ostringstream w;
		collatz_print(w, 1, 10, 20);
		CPPUNIT_ASSERT(w.str() == "1 10 20\n");
	}
	
	void test_print_1 () {
		ostringstream w;
		collatz_print(w, 3, 2, 4);
		CPPUNIT_ASSERT(w.str() == "3 2 4\n");
	}
	
	void test_print_2 () {
		ostringstream w;
		collatz_print(w, 132, 123, 42);
		CPPUNIT_ASSERT(w.str() == "132 123 42\n");
	}

	// -----
	// solve
	void test_solve_0 () {
		istringstream r("1 10");
		ostringstream w;
		collatz_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 10 20\n");
	}
	
	void test_solve_1 () {
		istringstream r("1 10\n100 200\n201 210\n");
		ostringstream w;
		collatz_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n");
	}
	
	void test_solve_2 () {
		istringstream r("1 10\n100 200\n201 210\n900 1000\n");
		ostringstream w;
		collatz_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}
	
	void test_solve_3 () {
		istringstream r("1 10000\n");
		ostringstream w;
		collatz_solve(r, w);
		if(DEBUG) cerr << "w.str(): " << w.str() << endl;
		CPPUNIT_ASSERT(w.str() == "1 10000 262\n");
	}
	
	void test_solve_4 () {
		int t0 = clock();
		istringstream r("1 999999\n");
		ostringstream w;
		collatz_solve(r, w);
		if(DEBUG) cerr << "w.str(): " << w.str() << endl;
		CPPUNIT_ASSERT(w.str() == "1 999999 525\n");
		int t1 = clock();
		int i = 0; i++;
		if(DEBUG) cerr << "time: " << (t1 - t0) << endl;
		if(DEBUG) cerr << "clock per sec: " << CLOCKS_PER_SEC	 << endl;
		
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestCollatz);
	
	CPPUNIT_TEST(test_read_0);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_cycleLength_0);
	CPPUNIT_TEST(test_cycleLength_1);
	CPPUNIT_TEST(test_cycleLength_2);
	CPPUNIT_TEST(test_cycleLength_3);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_print_0);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_solve_0);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_solve_4);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestCollatz.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestCollatz::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
