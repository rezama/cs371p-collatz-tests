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

    void test_read () {
	std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_largest_int(){
	std::istringstream r("1 2147483647\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	CPPUNIT_ASSERT(b ==       true);
	CPPUNIT_ASSERT(i ==          1);
	CPPUNIT_ASSERT(j == 2147483647);
    }
    
    void test_extra_white_space(){
	std::istringstream r("1 \t2147483647\n");
	int i; 
	int j;
	const bool b = collatz_read(r, i ,j);
	CPPUNIT_ASSERT(b ==       true);
	CPPUNIT_ASSERT(i ==          1);
	CPPUNIT_ASSERT(j == 2147483647);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}
	
	void test_eval_5(){
        const int v = collatz_eval(159487, 159487);
        CPPUNIT_ASSERT(v == 184);
    }
    
    void test_eval_6(){
        const int v = collatz_eval(3, 3);
        CPPUNIT_ASSERT(v == 8);
    }
    
    void test_eval_7(){
        const int v = collatz_eval(232545, 681701);
        CPPUNIT_ASSERT(v == 509);
    }
    
    void test_eval_8(){
        const int v = collatz_eval(773104, 675975);
        CPPUNIT_ASSERT(v == 504);
    }
    
    void test_eval_backward_input(){
        const int v = collatz_eval(10, 1);
        CPPUNIT_ASSERT(v == 20);
    }
    
    void test_eval_generic_double_input(){
        const int v = collatz_eval(888, 888);
        CPPUNIT_ASSERT(v == 73);
    }

    // -----
    // print
    // -----

    void test_print () {
	std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    
    void test_print_base_case(){
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");
    }
    
    void test_print_max_values(){
        std::ostringstream w;
        collatz_print(w, 1000000, 1000000, 153);
        CPPUNIT_ASSERT(w.str() == "1000000 1000000 153\n");
    }
    
    void test_print_max_range(){
        std::ostringstream w;
        collatz_print(w, 1, 1000000, 525);
        CPPUNIT_ASSERT(w.str() == "1 1000000 525\n");
    }

    // -----
    // solve
    // -----

    void test_solve () {
	std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
	std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

	void test_solve_edge_cases(){
		std::istringstream r("1 2\n999999 1000000\n");
	    std::ostringstream w;
		collatz_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "1 2 2\n999999 1000000 259\n");
	}



    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_largest_int);
	CPPUNIT_TEST(test_extra_white_space);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_backward_input);
	CPPUNIT_TEST(test_eval_generic_double_input);
    CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_base_case);
	CPPUNIT_TEST(test_print_max_values);
	CPPUNIT_TEST(test_print_max_range);
    CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve_edge_cases);
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
