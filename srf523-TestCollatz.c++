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
% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestCollatz.c++ -o TestCollatz.c++.app
% valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    
	// ----
    	// read
    	// ----

	void test_read_1 () {
		std::istringstream r("1 10\n");
        	int i;
        	int j;
        	const bool b = collatz_read(r, i, j);
        	CPPUNIT_ASSERT(b == true);
        	CPPUNIT_ASSERT(i == 1);
        	CPPUNIT_ASSERT(j == 10);
	}

	void test_read_2() {
		std::istringstream r("1 2\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 2);
	}

	void test_read_3() {
		std::istringstream r("1 1\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 1);
	}

	void test_read_4() {
		std::istringstream r("20 5\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 20);
		CPPUNIT_ASSERT(j == 5);
	}

	void test_read_5() {
		std::istringstream r("words");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT( b == false);
	}
	
	void test_read_6() {
		std::istringstream r("");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT( b == false);
	}

    	// ----
    	// eval
    	// ----

    	void test_eval_1 () {
        	const int maxCycleLen = collatz_eval(1, 10);
        	CPPUNIT_ASSERT(maxCycleLen == 20);
	}

    	void test_eval_2 () {
        	const int maxCycleLen = collatz_eval(100, 200);
        	CPPUNIT_ASSERT(maxCycleLen == 125);
	}

    	void test_eval_3 () {
        	const int maxCycleLen = collatz_eval(201, 210);
        	CPPUNIT_ASSERT(maxCycleLen == 89);
	}

    	void test_eval_4 () {
        	const int maxCycleLen = collatz_eval(900, 1000);
        	CPPUNIT_ASSERT(maxCycleLen == 174);
	}

	void test_eval_5() {
		const int maxCycleLen = collatz_eval(10, 1);
		CPPUNIT_ASSERT(maxCycleLen == 20);
	}

	void test_eval_6() {
		const int maxCycleLen = collatz_eval(1, 2);
		CPPUNIT_ASSERT(maxCycleLen == 2);
	}

	void test_eval_7() {
		const int maxCycleLen = collatz_eval(999999, 1000000);
		CPPUNIT_ASSERT(maxCycleLen == 259);
	}

	void test_eval_8() {
		const int maxCycleLen = collatz_eval(1, 1000000);
		CPPUNIT_ASSERT(maxCycleLen == 525);
	}


    	// -----
    	// print
    	// -----

    	void test_print_1 () {
        	std::ostringstream w;
        	collatz_print(w, 1, 10, 20);
        	CPPUNIT_ASSERT(w.str() == "1 10 20\n");
	}

	void test_print_2() {
		std::ostringstream w;
		collatz_print(w, 10, 1, 20);
		CPPUNIT_ASSERT(w.str() == "10 1 20\n");
	}

	void test_print_3() {
		std::ostringstream w;
		collatz_print(w, 900, 1000, 174);
		CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
	}

	void test_print_4() {
		std::ostringstream w;
		collatz_print(w, 1, 1000000, 525);
		CPPUNIT_ASSERT(w.str() == "1 1000000 525\n");
	}


    	// -----
    	// solve
    	// -----

    	void test_solve_1 () {
        	std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        	std::ostringstream w;
        	collatz_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}

	void test_solve_2 () {
        	std::istringstream r("1 10\n10 1\n201 210\n1 1000000\n");
        	std::ostringstream w;
        	collatz_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "1 10 20\n10 1 20\n201 210 89\n1 1000000 525\n");
	}

	void test_solve_3 () {
        	std::istringstream r("900 1000\n1000000 1000000\n1 1\n1 2\n");
        	std::ostringstream w;
        	collatz_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "900 1000 174\n1000000 1000000 153\n1 1 1\n1 2 2\n");
	}


	void test_solve_4 () {
        	std::istringstream r("12345 23456");
        	std::ostringstream w;
        	collatz_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "12345 23456 279\n");
	}

 
	// --------------
	// getCycleLength
	// --------------

	void test_getCycleLength_1() {
		const int len = getCycleLength(1);
		CPPUNIT_ASSERT (len == 1);
	}

	void test_getCycleLength_2() {
		const int len = getCycleLength(100);
		CPPUNIT_ASSERT (len == 26);
	}

	void test_getCycleLength_3() {
		const int len = getCycleLength(1000);
		CPPUNIT_ASSERT (len == 112);
	}

	void test_getCycleLength_4() {
		const int len = getCycleLength(1000000);
		CPPUNIT_ASSERT (len == 153);
	}

	void test_getCycleLength_5() {
		const int len = getCycleLength(2);
		CPPUNIT_ASSERT (len == 1);
	}

	void test_getCycleLength_6() {
		const int len = getCycleLength(3);
		CPPUNIT_ASSERT (len == 8);
	}

	void test_getCycleLength_7() {
		const int len = getCycleLength(4);
		CPPUNIT_ASSERT (len == 3);
	}

	void test_getCycleLength_8() {
		const int len = getCycleLength(5);
		CPPUNIT_ASSERT (len == 6);
	}

	void test_getCycleLength_9() {
		const int len = getCycleLength(6);
		CPPUNIT_ASSERT (len == 9);
	}

	void test_getCycleLength_10() {
		const int len = getCycleLength(7);
		CPPUNIT_ASSERT (len == 17);
	}

	void test_getCycleLength_11() {
		const int len = getCycleLength(8);
		CPPUNIT_ASSERT (len == 4);
	}

	void test_getCycleLength_12() {
		const int len = getCycleLength(9);
		CPPUNIT_ASSERT (len == 20);
	}

	void test_getCycleLength_13() {
		const int len = getCycleLength(10);
		CPPUNIT_ASSERT (len == 7);
	}
    	// -----
    	// suite
    	// -----

    	CPPUNIT_TEST_SUITE(TestCollatz);

    	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
    	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_read_4);
	CPPUNIT_TEST(test_read_5);
	CPPUNIT_TEST(test_read_6);

    	CPPUNIT_TEST(test_eval_1);
    	CPPUNIT_TEST(test_eval_2);
    	CPPUNIT_TEST(test_eval_3);
    	CPPUNIT_TEST(test_eval_4);
    	CPPUNIT_TEST(test_eval_5);
    	CPPUNIT_TEST(test_eval_6);
    	CPPUNIT_TEST(test_eval_7);
    	CPPUNIT_TEST(test_eval_8);


    	CPPUNIT_TEST(test_print_1);
    	CPPUNIT_TEST(test_print_2);
    	CPPUNIT_TEST(test_print_3);
    	CPPUNIT_TEST(test_print_4);

    	CPPUNIT_TEST(test_solve_1);
    	CPPUNIT_TEST(test_solve_2);
    	CPPUNIT_TEST(test_solve_3);
    	CPPUNIT_TEST(test_solve_4);



	CPPUNIT_TEST(test_getCycleLength_1);
	CPPUNIT_TEST(test_getCycleLength_2);
	CPPUNIT_TEST(test_getCycleLength_3);
	CPPUNIT_TEST(test_getCycleLength_4);

    	CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
	using namespace std;
    	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    	cout << "TestCollatz.c++" << endl;

    	CppUnit::TextTestRunner tr;
    	tr.addTest(TestCollatz::suite());
    	tr.run();

    	cout << "Done." << endl;
    	return 0;
}
