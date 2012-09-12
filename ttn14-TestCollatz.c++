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

#include "Collatz.h" //MAX_RANGE, a

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
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
        std::istringstream r("1 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==    1);}

    void test_read_3 () {
        std::istringstream r("99999 99999\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   99999);
        CPPUNIT_ASSERT(j ==   99999);}

    void test_read_4 () {
        std::istringstream r("99999 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   99999);
        CPPUNIT_ASSERT(j ==   1);}
    // ----
    // eager cache
    // ----
    void test_eager_cache_1(){
    	eager_cache();
    	//MAX_RANGE and a are from Collatz.h
    	for (int i = 1; i<MAX_RANGE; i++)
    		CPPUNIT_ASSERT( a[i]!=0 );
    }
    void test_eager_cache_2(){
    	eager_cache();
    	//MAX_RANGE and a are from Collatz.h
    	for (int i = 1; i<MAX_RANGE; i++)
    		CPPUNIT_ASSERT( a[i]!=0 );
    }
    void test_eager_cache_3(){
    	eager_cache();
    	//MAX_RANGE and a are from Collatz.h
    	for (int i = 1; i<MAX_RANGE; i++)
    		CPPUNIT_ASSERT( a[i]!=0 );
    }
    // ----
    // cycle length
    // ----

    void test_cycle_length_1(){
    	const int c = cycle_length(9999);
    	CPPUNIT_ASSERT( c== 92);
    }

    void test_cycle_length_2(){
    	const int c = cycle_length(100000);
    	CPPUNIT_ASSERT( c== 129);
    }

    void test_cycle_length_3(){
    	const int c = cycle_length(111);
    	CPPUNIT_ASSERT( c== 70);
    }

    void test_cycle_length_4(){
    	const int c = cycle_length(999);
    	CPPUNIT_ASSERT( c== 50);
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

    void test_eval_5 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}

    void test_eval_6 () {
        const int v = collatz_eval(1, 2);
        CPPUNIT_ASSERT(v == 2);}

    void test_eval_7 () {
        const int v = collatz_eval(99999, 1);
        CPPUNIT_ASSERT(v ==  351);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 99999, 99999, 351);
        CPPUNIT_ASSERT(w.str() == "99999 99999 351\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 2, 2, 2);
        CPPUNIT_ASSERT(w.str() == "2 2 2\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2 () {
        std::istringstream r("1 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_solve_3 () {
        std::istringstream r("9999 2\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "9999 2 262\n");}

    void test_solve_4 () {
        std::istringstream r("1 12345\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 12345 268\n");}
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    //Prepare the cache before testing
    CPPUNIT_TEST(test_eager_cache_1);
    CPPUNIT_TEST(test_eager_cache_2);
    CPPUNIT_TEST(test_eager_cache_3);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_cycle_length_1);
    CPPUNIT_TEST(test_cycle_length_2);
    CPPUNIT_TEST(test_cycle_length_3);
    CPPUNIT_TEST(test_cycle_length_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
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
