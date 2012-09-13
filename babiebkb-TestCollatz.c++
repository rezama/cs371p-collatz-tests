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
        
    void test_read1 () {
        std::istringstream r("10 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    10);
        CPPUNIT_ASSERT(j ==   1);}
        
    void test_read2 () {
        std::istringstream r("100 1000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    100);
        CPPUNIT_ASSERT(j ==   1000);}
        
    void test_read3 () {
        std::istringstream r("999999 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    999999);
        CPPUNIT_ASSERT(j ==   1000000);}
        
    // ----
    // eval
    // ----

    void test_eval () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval1 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval2 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval3 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}
        
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    
    void test_print1 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");}
    
    void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");}
    
    void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");}
        
    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve1 () {
        std::istringstream r("495625 705494\n229705 378426\n608223 564520\n326615 702673\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "495625 705494 470\n229705 378426 443\n608223 564520 434\n326615 702673 470\n");}

    void test_solve2 () {
        std::istringstream r("700138 983739\n61597 324117\n468919 436897\n519574 66398\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "700138 983739 476\n61597 324117 443\n468919 436897 444\n519574 66398 470\n");}  
        
    void test_solve3 () {
        std::istringstream r("700138 983739\n61597 324117\n468919 436897\n519574 66398\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "700138 983739 476\n61597 324117 443\n468919 436897 444\n519574 66398 470\n");}  
        
        
    // -----
    // cycle length
    // -----  
    void test_length1 () {
        const int v = cycle_length(1);
        CPPUNIT_ASSERT(v == 0);}

    void test_length2 () {
        const int v = cycle_length(100);
        CPPUNIT_ASSERT(v == 25);}

    void test_length3 () {
        const int v = cycle_length(10000);
        CPPUNIT_ASSERT(v == 29);}

        
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval);
    CPPUNIT_TEST(test_eval1);
    CPPUNIT_TEST(test_eval2);
    CPPUNIT_TEST(test_eval3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);    
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    CPPUNIT_TEST(test_length1);
    CPPUNIT_TEST(test_length2);  
    CPPUNIT_TEST(test_length3);      
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
