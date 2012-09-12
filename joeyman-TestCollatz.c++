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

    void test_read_pair () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_whitespace () {
        std::istringstream r("  1    10 \n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_newline () {
        std::istringstream r("\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    void test_read_empty () {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

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

    void test_eval_one () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}

    void test_eval_two () {
        const int v = collatz_eval(2, 2);
        CPPUNIT_ASSERT(v == 2);}

    void test_eval_backwards () {
        const int v = collatz_eval(10, 1);
        CPPUNIT_ASSERT(v == 20);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");}

    void test_print_backwards () {
        std::ostringstream w;
        collatz_print(w, 10, 1, 20);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_nothing () {
        std::istringstream r("");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_solve_one () {
        std::istringstream r("1 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_solve_backwards () {
        std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_pair);
    CPPUNIT_TEST(test_read_whitespace);
    CPPUNIT_TEST(test_read_newline);
    CPPUNIT_TEST(test_read_empty);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_one);
    CPPUNIT_TEST(test_eval_two);
    CPPUNIT_TEST(test_eval_backwards);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_print_backwards);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_nothing);
    CPPUNIT_TEST(test_solve_one);
    CPPUNIT_TEST(test_solve_backwards);
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
