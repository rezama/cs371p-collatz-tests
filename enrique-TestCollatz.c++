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
#include <map> 

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

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
        std::istringstream r("100 100\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    100);
        CPPUNIT_ASSERT(j ==   100);}

    void test_read_3 () {
        std::istringstream r("1234 56\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1234);
        CPPUNIT_ASSERT(j ==   56);}



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

    // ----
    // get_cycle_length
    // ----

    typedef std::map<int, int> IntMap; 
    void test_get_cycle_length_1 () {
        IntMap map;
        const int v = collatz_get_cycle_length(1, map);
        CPPUNIT_ASSERT(v == 1);}

    void test_get_cycle_length_2 () {
        IntMap map;
        const int v = collatz_get_cycle_length(22, map);
        CPPUNIT_ASSERT(v == 16);}

    void test_get_cycle_length_3 () {
        IntMap map;
        const int v = collatz_get_cycle_length(2, map);
        CPPUNIT_ASSERT(v == 2);}

    void test_get_cycle_length_4 () {
        IntMap map;
        const int v = collatz_get_cycle_length(4, map);
        CPPUNIT_ASSERT(v == 3);}

    void test_get_cycle_length_5 () {
        IntMap map;
        const int v = collatz_get_cycle_length(5, map);
        CPPUNIT_ASSERT(v == 6);}

    void test_get_cycle_length_6 () {
        IntMap map;
        const int v = collatz_get_cycle_length(300, map);
        CPPUNIT_ASSERT(v == 17);}

    void test_get_cycle_length_7 () {
        IntMap map;
        const int v = collatz_get_cycle_length(250, map);
        CPPUNIT_ASSERT(v == 110);}

    void test_get_cycle_length_8 () {
        IntMap map;
        const int v = collatz_get_cycle_length(100, map);
        CPPUNIT_ASSERT(v == 26);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 100, 100, 200);
        CPPUNIT_ASSERT(w.str() == "100 100 200\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 123, 456, 789);
        CPPUNIT_ASSERT(w.str() == "123 456 789\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
 
    void test_solve_2 () {
        std::istringstream r("1 2000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2000 182\n");}

    void test_solve_3 () {
        std::istringstream r("1 1\n100 100\n6001 8000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n100 100 26\n6001 8000 262\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_get_cycle_length_1);
    CPPUNIT_TEST(test_get_cycle_length_2);
    CPPUNIT_TEST(test_get_cycle_length_3);
    CPPUNIT_TEST(test_get_cycle_length_4);
    CPPUNIT_TEST(test_get_cycle_length_5);
    CPPUNIT_TEST(test_get_cycle_length_6);
    CPPUNIT_TEST(test_get_cycle_length_7);
    CPPUNIT_TEST(test_get_cycle_length_8);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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
