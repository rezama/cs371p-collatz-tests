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

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
        std::istringstream r("10 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    10);
        CPPUNIT_ASSERT(j ==   1);}

    void test_read_3 () {
        std::istringstream r("1000000 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1000000);
        CPPUNIT_ASSERT(j ==   1000000);}

    void test_read_4 () {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    void test_read_5 () {
        std::istringstream r("one two\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

     void test_read_6 () {
        std::istringstream r("batman\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    void test_read_7 () {
        std::istringstream r("\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    void test_read_8 () {
        std::istringstream r("43567 123124\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    43567);
        CPPUNIT_ASSERT(j ==   123124);}


        
    // ----
    // length
    // ----

    void test_length_1 () {
        std::tr1::unordered_map<int,int> d;
        //seed values: my algo is designed like this
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_length(1, d);
        CPPUNIT_ASSERT(v == 1);}

    
    void test_length_2 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_length(1000000, d);
        CPPUNIT_ASSERT(v == 153);}

    void test_length_3 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_length(2456, d);
        CPPUNIT_ASSERT(v == 41);}

    void test_length_4 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_length(98743, d);
        CPPUNIT_ASSERT(v == 160);}

    void test_length_5 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_length(98744, d);
        CPPUNIT_ASSERT(v == 266);}

    void test_length_6 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_length(876545, d);
        CPPUNIT_ASSERT(v == 220);}
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
        const int v = collatz_eval(1, 1000000);
        CPPUNIT_ASSERT(v == 525);}

    void test_eval_6 () {
        const int v = collatz_eval(1000000, 1);
        CPPUNIT_ASSERT(v == 525);}

    void test_eval_7 () {
        const int v = collatz_eval(999998, 999998);
        CPPUNIT_ASSERT(v == 259);}

    void test_eval_8 () {
        const int v = collatz_eval(999997, 999997);
        CPPUNIT_ASSERT(v == 114);}

    void test_eval_9 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}

    void test_eval_10 () {
        const int v = collatz_eval(2, 2);
        CPPUNIT_ASSERT(v == 2);}

    void test_eval_11 () {
        const int v = collatz_eval(3, 3);
        CPPUNIT_ASSERT(v == 8);}

    void test_eval_12 () {
        const int v = collatz_eval(43567, 123124);
        CPPUNIT_ASSERT(v == 354);}

    // ----
    // eval
    // ----

    void test_overloaded_eval_1 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(1, 10, d);
        CPPUNIT_ASSERT(v == 20);}

    void test_overloaded_eval_2 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(100, 200, d);
        CPPUNIT_ASSERT(v == 125);}

    void test_overloaded_eval_3 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(201, 210, d);
        CPPUNIT_ASSERT(v == 89);}

    void test_overloaded_eval_4 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(900, 1000, d);
        CPPUNIT_ASSERT(v == 174);}

    void test_overloaded_eval_5 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(1, 1000000, d);
        CPPUNIT_ASSERT(v == 525);}

    void test_overloaded_eval_6 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(1000000, 1, d);
        CPPUNIT_ASSERT(v == 525);}

    void test_overloaded_eval_7 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(999998, 999998, d);
        CPPUNIT_ASSERT(v == 259);}

    void test_overloaded_eval_8 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(999997, 999997, d);
        CPPUNIT_ASSERT(v == 114);}

    void test_overloaded_eval_9 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(100, 87652, d);
        CPPUNIT_ASSERT(v == 351);}

    void test_overloaded_eval_10 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(87652, 87652, d);
        CPPUNIT_ASSERT(v == 165);}

    void test_overloaded_eval_11 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(3, 3, d);
        CPPUNIT_ASSERT(v == 8);}

    void test_overloaded_eval_12 () {
        std::tr1::unordered_map<int,int> d;
        d[1] = 1;
        d[2] = 2;
        const int v = collatz_eval(43567, 123124, d);
        CPPUNIT_ASSERT(v == 354);}


    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 10, 1, 20);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 1, 1000000, 525);
        CPPUNIT_ASSERT(w.str() == "1 1000000 525\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_print_5 () {
        std::ostringstream w;
        collatz_print(w, 2, 2, 2);
        CPPUNIT_ASSERT(w.str() == "2 2 2\n");}    

     void test_print_6 () {
        std::ostringstream w;
        collatz_print(w, 1000000, 1000000, 153);
        CPPUNIT_ASSERT(w.str() == "1000000 1000000 153\n");}       

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2 () {
        std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}

    void test_solve_3 () {
        std::istringstream r("1000000 1000000\n999999 999999\n999998 999998\n999997 999997\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1000000 1000000 153\n999999 999999 259\n999998 999998 259\n999997 999997 114\n");}

    void test_solve_4 () {
        std::istringstream r("1 1\n2 2\n3 3\n3 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n3 3 8\n3 1 8\n");}

    void test_solve_5 () {
        std::istringstream r("235235 745645\n9742 234\n1095 6756\n23415 23567\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "235235 745645 509\n9742 234 262\n1095 6756 262\n23415 23567 282\n");}

    void test_solve_6 () {
        std::istringstream r("1 100\n 101 200\n 201 300\n301 400\n401 500\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 100 119\n101 200 125\n201 300 128\n301 400 144\n401 500 142\n");}                             

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
    CPPUNIT_TEST(test_read_7);
    CPPUNIT_TEST(test_read_8);
    CPPUNIT_TEST(test_length_1);
    CPPUNIT_TEST(test_length_2);
    CPPUNIT_TEST(test_length_3);
    CPPUNIT_TEST(test_length_4);
    CPPUNIT_TEST(test_length_5);
    CPPUNIT_TEST(test_length_6);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_9);
    CPPUNIT_TEST(test_eval_10);
    CPPUNIT_TEST(test_eval_11);
    CPPUNIT_TEST(test_eval_12);
    CPPUNIT_TEST(test_overloaded_eval_1);
    CPPUNIT_TEST(test_overloaded_eval_2);
    CPPUNIT_TEST(test_overloaded_eval_3);
    CPPUNIT_TEST(test_overloaded_eval_4);
    CPPUNIT_TEST(test_overloaded_eval_5);
    CPPUNIT_TEST(test_overloaded_eval_6);
    CPPUNIT_TEST(test_overloaded_eval_7);
    CPPUNIT_TEST(test_overloaded_eval_8);
    CPPUNIT_TEST(test_overloaded_eval_9);
    CPPUNIT_TEST(test_overloaded_eval_10);
    CPPUNIT_TEST(test_overloaded_eval_11);
    CPPUNIT_TEST(test_overloaded_eval_12);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_print_5);
    CPPUNIT_TEST(test_print_6);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
    CPPUNIT_TEST(test_solve_6);
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
