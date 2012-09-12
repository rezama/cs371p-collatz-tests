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

    /** XXX-MDM Begin Code **/
    void test_read1() {
        std::istringstream r("4 5\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   4);
        CPPUNIT_ASSERT(j ==   5);}

    void test_read2() {
        std::istringstream r("\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    void test_read3() {
        std::istringstream r("1 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   1000000);}
    /** XXX-MDM End Code **/
    
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

    /** XXX-MDM Begin Code **/
    void test_eval_5() {
        const int v = collatz_eval(16807, 16807);
        CPPUNIT_ASSERT(v == 67);}
    
    void test_eval_6() {
        const int v = collatz_eval(475249, 475249);
        CPPUNIT_ASSERT(v == 139);}
    
    void test_eval_7() {
        const int v = collatz_eval(650073, 650073);
        CPPUNIT_ASSERT(v == 67);}
    
    void test_singleeval_1() {
        const int v = collatz_eval(943658);
        CPPUNIT_ASSERT(v == 52);}
    
    void test_singleeval_2() {
        const int v = collatz_eval(108930);
        CPPUNIT_ASSERT(v == 186);}
    
    void test_singleeval_3() {
        const int v = collatz_eval(211272);
        CPPUNIT_ASSERT(v == 81);}
    /** XXX-MDM End Code **/

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    /** XXX-MDM Begin Code **/
    void test_print1() {
        std::ostringstream w;
        collatz_print(w, 199, 200, 20);
        CPPUNIT_ASSERT(w.str() == "199 200 20\n");}

    void test_print2() {
        std::ostringstream w;
        collatz_print(w, 1073741824, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1073741824 10 20\n");}

    void test_print3() {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}
    /** XXX-MDM End Code **/
    
    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    /** XXX-MDM Begin Code **/
    void test_solve1() {
        std::istringstream r("\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_solve2() {
        std::istringstream r("108930 108930\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "108930 108930 186\n");}

    void test_solve3() {
        std::istringstream r("211272 211272\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "211272 211272 81\n");}
    /** XXX-MDM End Code **/
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve);
    
    /** XXX-MDM Begin Code **/
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);    
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_singleeval_1);
    CPPUNIT_TEST(test_singleeval_2);
    CPPUNIT_TEST(test_singleeval_3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    /** XXX-MDM End Code **/
    
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
