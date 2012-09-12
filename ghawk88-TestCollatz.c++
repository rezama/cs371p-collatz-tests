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
#include <map> // for lazy-cache system

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

void test_read_1 () {
        std::istringstream r("1 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   1);}
    
    void test_read_2 () {
        std::istringstream r("1000000 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1000000);
        CPPUNIT_ASSERT(j ==   1000000);}
    
    void test_read_3 () {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}
    
    void test_read_4 () {
        std::istringstream r("coolio dude");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    // ----
    // eval_helper
    // ----


    void test_eval_helper_guy_1 () {
	std::map<int,int> cache;
        const int v = collatz_eval_rec_helper(1,cache);
        CPPUNIT_ASSERT(v == 1);}

    void test_eval_helper_guy_2 () {
	std::map<int,int> cache;
         const int v = collatz_eval_rec_helper(999999,cache);
        CPPUNIT_ASSERT(v == 259);}

    void test_eval_helper_guy_3 () {
	std::map<int,int> cache;
        const int v = collatz_eval_rec_helper(500000,cache);
        CPPUNIT_ASSERT(v == 152);}

    void test_eval_helper_guy_4 () {
	std::map<int,int> cache;
        const int v = collatz_eval_rec_helper(10,cache);
        CPPUNIT_ASSERT(v == 7);}
   
    void test_eval_helper_guy_5 () {
	std::map<int,int> cache;
        const int v = collatz_eval_rec_helper(999999,cache);
        CPPUNIT_ASSERT(v == 259);}



    // ----
    // eval
    // ----
////////////////////////////////////////////////
//  THESE TESTS TEND TO TAKE THE MOST TIME, SORRY. THANKS :)
///////////////////////////////////////////////
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
        const int v = collatz_eval(999999, 999999);
        CPPUNIT_ASSERT(v == 259);}

    void test_eval_7 () {
        const int v = collatz_eval(250000, 500000);
        CPPUNIT_ASSERT(v == 449);}

    void test_eval_8 () {
        const int v = collatz_eval(785, 541);
        CPPUNIT_ASSERT(v == 171);}

////////////////////////////////////////////////


    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 11, 101, 201);
        CPPUNIT_ASSERT(w.str() == "11 101 201\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 0, 0, 0);
        CPPUNIT_ASSERT(w.str() == "0 0 0\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 999, 999, 999);
        CPPUNIT_ASSERT(w.str() == "999 999 999\n");}

    // -----
    // solve
    // -----

    void test_solve() {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
   
    void test_solve_1() {
        std::istringstream r("10 20\n2 202\n3 303\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 20 21\n2 202 125\n3 303 128\n");}

    void test_solve_2() {
        std::istringstream r("10 100\n1 2\n99 100\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 100 119\n1 2 2\n99 100 26\n");}

    void test_solve_3() {
        std::istringstream r("1 1\n2 2\n999 999\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n999 999 50\n");}
    
    // -----
    // suite
    // -----   
    CPPUNIT_TEST_SUITE(TestCollatz);
//////////////////////////////////
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
///////////////////////////////////
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
////////////////////////////////////////
    CPPUNIT_TEST(test_eval_helper_guy_1);
    CPPUNIT_TEST(test_eval_helper_guy_2);
    CPPUNIT_TEST(test_eval_helper_guy_3);
    CPPUNIT_TEST(test_eval_helper_guy_4);
    CPPUNIT_TEST(test_eval_helper_guy_5);
///////////////////////////////////////// 
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
/////////////////////////////////////////
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
//////////////////////////////////
    CPPUNIT_TEST_SUITE_END();};
///////////// END ////////////////
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
