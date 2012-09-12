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

    void test_read_2() {
        std::istringstream r("1 \n 10 \n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
    }

    void test_read_3() {
        std::istringstream r("10000 \n \n \n 999999 \n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 10000);
        CPPUNIT_ASSERT(j == 999999);
    }

    void test_read_4() {
        std::istringstream r("10 1 \n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 10);
        CPPUNIT_ASSERT(j == 1);
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

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2() {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
    }

    void test_print_3() {
        std::ostringstream w;
        collatz_print(w, 10, 1, 20);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");}

    void test_print_4() {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");
    }

    void test_print_5() {
        std::ostringstream w;
        collatz_print(w, 100, 1000, 179);
        CPPUNIT_ASSERT(w.str() == "100 1000 179\n");
    }

    void test_print_6() {
        std::ostringstream w;
        collatz_print(w, 123, 456, 144);
        CPPUNIT_ASSERT(w.str() == "123 456 144\n");
    }

    void test_print_7() {
        std::ostringstream w;
        collatz_print(w, 330, 120, 144);
        CPPUNIT_ASSERT(w.str() == "330 120 144\n");
    }

    // -----
    // solve
    // -----

    void test_solve () {
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
        std::istringstream r("90000 100000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "90000 100000 333\n");
    }

    void test_solve_4 () {
        std::istringstream r("1000000 1000000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1000000 1000000 153\n");
    }


    // ------
    // length
    // ------
    
    void test_length_1 () {
      CPPUNIT_ASSERT(collatz_length(10) == 7);
    }

    void test_length_2() {
      CPPUNIT_ASSERT(collatz_length(1000000) == 153);
    }

    void test_length_3 () {
      CPPUNIT_ASSERT(collatz_length(1) == 1);
    }

    // --------------
    // can_meta_cache
    // --------------
    
    void test_can_meta_1 () {
      CPPUNIT_ASSERT(can_meta_cache(1, 10) == false );
    }

    void test_can_meta_2 () {
      CPPUNIT_ASSERT(can_meta_cache(1000, 5000) == true);
    }

    void test_can_meta_3 () {
      CPPUNIT_ASSERT(can_meta_cache(1, 500000) == true);
    }

    // ----------
    // meta_cache
    // ----------
  
    void test_meta_cache_1 () {
      CPPUNIT_ASSERT(collatz_meta_cache(1, 5) == 238);
    }

    void test_meta_cache_2 () {
      CPPUNIT_ASSERT(collatz_meta_cache(10, 15) == 276);
    }

    void test_meta_cache_3 () {
      CPPUNIT_ASSERT(collatz_meta_cache(10, 20) == 279);
    }
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
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_print_5);
    CPPUNIT_TEST(test_print_6);
    CPPUNIT_TEST(test_print_7);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_length_1);
    CPPUNIT_TEST(test_length_2);
    CPPUNIT_TEST(test_length_3);
    CPPUNIT_TEST(test_can_meta_1);
    CPPUNIT_TEST(test_can_meta_2);
    CPPUNIT_TEST(test_can_meta_3);
    CPPUNIT_TEST(test_meta_cache_1);
    CPPUNIT_TEST(test_meta_cache_2);
    CPPUNIT_TEST(test_meta_cache_3);
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
