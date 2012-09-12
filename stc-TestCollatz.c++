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
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

	/**
	* Tests that ints 1 and 10 are entered, read, and stored correctly
	*/
    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
	}
    
	/**
	* Tests that ints 2 and 20 are entered, read, and stored correctly
	*/
	void test_read_2 () {
        std::istringstream r("2 20\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    2);
        CPPUNIT_ASSERT(j ==   20);
	}

	
	/**
	* Tests that ints 3 and 999999 are entered, read, and stored correctly
	*/
	void test_read_3 () {
        std::istringstream r("3 999999\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    3);
        CPPUNIT_ASSERT(j ==   999999);
	}

    // ----
    // eval
    // ----


	/**
	* Tests that the collatz_eval function works by finding the largest cycle length of range 1 through 10
	*/
    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

	
	/**
	* Tests that the collatz_eval function works by finding the largest cycle length of range 100 through 200
	*/
    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}
	
	/**
	* Tests that the collatz_eval function works by finding the largest cycle length of range 201 through 210
	*/
    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}


    // -----
    // print
    // -----
	
	/**
	* Tests that the three numbers 1 10 20 are correctly printed to the outstream.
	*/
    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

	/**
	* Tests that the three numbers 10 1000 2000000 are correctly printed to the outstream.
	*/
    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 100, 1000, 200000);
        CPPUNIT_ASSERT(w.str() == "100 1000 200000\n");}

	/**
	* Tests that the three numbers 999998 1 999999 are correctly printed to the outstream.
	*/
    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 999998, 1, 999999);
        CPPUNIT_ASSERT(w.str() == "999998 1 999999\n");}

    // -----
    // solve
    // -----

	/**
	* Tests multiple problems of evaluation of the largest cycle length in a range;
	*/
    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}

	/**
	* Tests multiple problems of evaluation of the largest cycle length in a range;
	*/
    void test_solve_2 () {
        std::istringstream r("229705 378426\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "229705 378426 443\n");
	}

	/**
	* Tests multiple problems of evaluation of the largest cycle length in a range;
	*/
    void test_solve_3 () {
        std::istringstream r("1 1\n999999 999999\n131149 322412\n35991 968566\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n999999 999999 259\n131149 322412 443\n35991 968566 525\n");
	}

	/**
	* Tests multiple problems of evaluation of the largest cycle length in a range;
	*/
    void test_solve_4 () {
        std::istringstream r("114172 105722\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "114172 105722 354\n");
	}


	// -----
	// compute_cycle_length
	// -----

	/**
	* Tests helper program that computes the cycle length of number 1
	*/
	void test_compute_cycle_length_1 () {
		const int len = compute_cycle_length(1);
		CPPUNIT_ASSERT(len == 1);
	}

	/**
	* Tests helper program that computes the cycle length of number 2
	*/
	void test_compute_cycle_length_2 () {
		const int len = compute_cycle_length(2);
		CPPUNIT_ASSERT(len == 2);
	}

	/**
	* Tests helper program that computes the cycle length of number 3
	*/
	void test_compute_cycle_length_3 () {
		const int len = compute_cycle_length(3);
		CPPUNIT_ASSERT(len == 8);
	}

	/**
	* Tests helper program that computes the cycle length of number 5
	*/
	void test_compute_cycle_length_4 () {
		const int len = compute_cycle_length(5);
		CPPUNIT_ASSERT(len == 6);
	}

	/**
	* Tests helper program that computes the cycle length of number 999999
	*/
	void test_compute_cycle_length_5 () {
		const int len = compute_cycle_length(999999);
		CPPUNIT_ASSERT(len == 259);
	}

	/**
	* Tests helper program that computes the cycle length of number 434343
	*/
	void test_compute_cycle_length_6 () {
		const int len = compute_cycle_length(434343);
		CPPUNIT_ASSERT(len == 250);
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
	CPPUNIT_TEST(test_compute_cycle_length_1);
	CPPUNIT_TEST(test_compute_cycle_length_2);
	CPPUNIT_TEST(test_compute_cycle_length_3);
	CPPUNIT_TEST(test_compute_cycle_length_4);
	CPPUNIT_TEST(test_compute_cycle_length_5); 
	CPPUNIT_TEST(test_compute_cycle_length_6); 
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
	CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
