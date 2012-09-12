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
    
    void test_read_2 () {
    	std::istringstream r("100 200\n");
    	int i;
    	int j;
    	const bool b = collatz_read(r, i, j);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 100);
    	CPPUNIT_ASSERT(j == 200);
    }
    
    void test_read_3 () {
    	std::istringstream r("1000 1234\n");
    	int i;
    	int j;
    	const bool b = collatz_read(r, i, j);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 1000);
    	CPPUNIT_ASSERT(j == 1234);
    }
    
    void test_read_4 () {
    	std::istringstream r("94869 11442\n");
    	int i;
    	int j;
    	const bool b = collatz_read(r, i, j);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 94869);
    	CPPUNIT_ASSERT(j == 11442);
    }
    
    void test_read_5 () {
    	std::istringstream r("10000 125069\n");
    	int i;
    	int j;
    	const bool b = collatz_read(r, i, j);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 10000);
    	CPPUNIT_ASSERT(j == 125069);
    }
    
    // ----------
    // cache_init
    // ----------
    
    void test_init_1 () {
    	int *cache = cache_init();
    	CPPUNIT_ASSERT(cache[2] = 2);
    }
    
    void test_init_2 () {
    	int *cache = cache_init();
    	CPPUNIT_ASSERT(cache[3276] = 16);
    }
    
    void test_init_3 () {
    	int *cache = cache_init();
    	CPPUNIT_ASSERT(cache[8192] = 14);
    }
    
    void test_init_4 () {
    	int *cache = cache_init();
    	CPPUNIT_ASSERT(cache[524288] = 20);
    }
    
    // -----
    // cycle
    // -----
    
    void test_cycle_1 () {
    	const int v = collatz_cycle(5);
    	CPPUNIT_ASSERT(v == 6);}
    
    void test_cycle_2 () {
    	const int v = collatz_cycle(2);
    	CPPUNIT_ASSERT(v == 2);}
    
    void test_cycle_3 () {
    	const int v = collatz_cycle(3);
    	CPPUNIT_ASSERT(v == 8);}

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
        const int v = collatz_eval(5212, 595369);
        CPPUNIT_ASSERT(v == 470);}
        
    void test_eval_6 () {
        const int v = collatz_eval(103349, 32173);
        CPPUNIT_ASSERT(v == 351);}
        
    void test_eval_7 () {
        const int v = collatz_eval(103349, 32173);
        CPPUNIT_ASSERT(v == 351);}

    // -----
    // print
    // -----

    void test_print () {
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

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
        
    void test_solve_2 () {
        std::istringstream r("5212 595369\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "5212 595369 470\n");}
        
    void test_solve_3 () {
        std::istringstream r("5212 595369\n344044 313751");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "5212 595369 470\n344044 313751 384\n");}
        
    void test_solve_4 () {
        std::istringstream r("5212 595369\n344044 313751\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "5212 595369 470\n344044 313751 384\n900 1000 174\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_init_1);
    CPPUNIT_TEST(test_init_2);
    CPPUNIT_TEST(test_init_3);
    CPPUNIT_TEST(test_init_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_solve);
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
