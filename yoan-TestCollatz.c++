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
        std::istringstream r("345 3425\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    345);
        CPPUNIT_ASSERT(j ==   3425);}
        
    void test_read_3 () {
        std::istringstream r("34534 2345\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    34534);
        CPPUNIT_ASSERT(j ==   2345);}
        
        
     void test_read_4 () {
        std::istringstream r("23453 4342\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    23453);
        CPPUNIT_ASSERT(j ==   4342);}

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
	
    // // -----
    // // cycle
    // // -----
	
    // void test_cycle_1 () {
    //     const int v = collatz_cycle(7366);
    //     CPPUNIT_ASSERT(v == 133);}
	
    // void test_cycle_2 () {
    //     const int v = collatz_cycle(38098);
    //     CPPUNIT_ASSERT(v == 200);}
	
    // void test_cycle_3 () {
    //     const int v = collatz_cycle(37099);
    //     CPPUNIT_ASSERT(v == 156);}
	
    // void test_cycle_4 () {
    //     const int v = collatz_cycle(27511);
    //     CPPUNIT_ASSERT(v == 184);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
        
    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 2345, 52, 134525);
        CPPUNIT_ASSERT(w.str() == "2345 52 134525\n");}
        
    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 445, 654, 7374);
        CPPUNIT_ASSERT(w.str() == "445 654 7374\n");}
        
    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 34, 57443, 5743);
        CPPUNIT_ASSERT(w.str() == "34 57443 5743\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
        
    void test_solve_2 () {
        std::istringstream r("18855 26474\n18892 37498\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "18855 26474 282\n18892 37498 324\n");}
        
    void test_solve_3 () {
        std::istringstream r("4488 8645\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "4488 8645 262\n");}
        
    void test_solve_4 () {
        std::istringstream r("2374 31714\n19543 23325\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "2374 31714 308\n19543 23325 274\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    // CPPUNIT_TEST(test_cycle_1);
    // CPPUNIT_TEST(test_cycle_2);
    // CPPUNIT_TEST(test_cycle_3);
    // CPPUNIT_TEST(test_cycle_4);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST_SUITE_END();
};

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
