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

    //Student written

    void test_read_multiline () {
        std::istringstream r("1 10\n2 20\n3 30\n");
        int i;
        int j;
        int i2;
        int j2;
        int i3;
        int j3;

        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);

        const bool b2 = collatz_read(r, i2, j2);
        CPPUNIT_ASSERT(b2 == true);
        CPPUNIT_ASSERT(i2 ==   2);
        CPPUNIT_ASSERT(j2 ==   20);

        const bool b3 = collatz_read(r, i3, j3);
        CPPUNIT_ASSERT(b3 == true);
        CPPUNIT_ASSERT(i3 ==   3);
        CPPUNIT_ASSERT(j3 ==   30);
    }

    void test_read_empty(){
    	std::istringstream r("\n");
    	int i;
    	int j;

    	const bool b = collatz_read(r, i, j);
    	CPPUNIT_ASSERT(b == false);
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
        
    void test_eval_big_number () {
        const int v = collatz_eval(113383, 113383);
        CPPUNIT_ASSERT(v == 248);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    //Student written

    void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 3, 30, 20);
        CPPUNIT_ASSERT(w.str() == "3 30 20\n");}

    void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 10, 300, 165);
        CPPUNIT_ASSERT(w.str() == "10 300 165\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_single_line () {
        std::istringstream r("1 10\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
    }
    
    void test_solve_empty () {
        std::istringstream r("\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");
    }
    
    // -----
    // collatz_helper: UNIT TEST FOR STUDENT WRITTEN 
    // METHOD: DO NOT USE.
    // -----

    void test_helper_small_number () {
        CPPUNIT_ASSERT(collatz_helper(10) == 7);
    }
    
    void test_helper_big_number () {
        CPPUNIT_ASSERT(collatz_helper(113383) == 248);
    }
    
    void test_helper_big_number2 () {
        CPPUNIT_ASSERT(collatz_helper(982037) == 140);
    }
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_multiline);
    CPPUNIT_TEST(test_read_empty);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_big_number);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_single_line);
    CPPUNIT_TEST(test_solve_empty);
    
    CPPUNIT_TEST(test_helper_small_number);
    CPPUNIT_TEST(test_helper_big_number);
    CPPUNIT_TEST(test_helper_big_number2);
    
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
