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
        CPPUNIT_ASSERT(j == 200);}
		
	void test_read_3 () {
        std::istringstream r("201 210\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 201);
        CPPUNIT_ASSERT(j == 210);}
		
	void test_read_4 () {
        std::istringstream r("900 1000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==  900);
        CPPUNIT_ASSERT(j == 1000);}

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
        std::istringstream r("42069 42069\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "42069 42069 58\n");}	

    void test_solve_3 () {
        std::istringstream r("999167 999167\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "999167 999167 321\n");}

    void test_solve_4 () {
        std::istringstream r("1000 900\n210 200\n200 100\n10 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1000 900 174\n210 200 89\n200 100 125\n10 1 20\n");}
		
	// -----
	// cycle_length
	// -----
	void test_cycle_length_1 () {
	    const int v = collatz_cycle_length(1);
		CPPUNIT_ASSERT(v == 1);}
		
	void test_cycle_length_2 () {
	    const int v = collatz_cycle_length(2);
		CPPUNIT_ASSERT(v == 2);}
		
	void test_cycle_length_3 () {
	    const int v = collatz_cycle_length(3);
		CPPUNIT_ASSERT(v == 8);}
	
	void test_cycle_length_4 () {
	    const int v = collatz_cycle_length(4);
		CPPUNIT_ASSERT(v == 3);}
	
	void test_cycle_length_5 () {
	    const int v = collatz_cycle_length(5);
		CPPUNIT_ASSERT(v == 6);}
	
	void test_cycle_length_6 () {
	    const int v = collatz_cycle_length(6);
		CPPUNIT_ASSERT(v == 9);}
	
	void test_cycle_length_7 () {
	    const int v = collatz_cycle_length(7);
		CPPUNIT_ASSERT(v == 17);}
	
	void test_cycle_length_8 () {
	    const int v = collatz_cycle_length(8);
		CPPUNIT_ASSERT(v == 4);}
		
    void test_cycle_length_9 () {
	    const int v = collatz_cycle_length(9);
		CPPUNIT_ASSERT(v == 20);}
		
	void test_cycle_length_10 () {
	    const int v = collatz_cycle_length(10);
		CPPUNIT_ASSERT(v == 7);}
	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
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
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
	CPPUNIT_TEST(test_cycle_length_1);
	CPPUNIT_TEST(test_cycle_length_2);
	CPPUNIT_TEST(test_cycle_length_3);
	CPPUNIT_TEST(test_cycle_length_4);
	CPPUNIT_TEST(test_cycle_length_5);
	CPPUNIT_TEST(test_cycle_length_6);
	CPPUNIT_TEST(test_cycle_length_7);
	CPPUNIT_TEST(test_cycle_length_8);
	CPPUNIT_TEST(test_cycle_length_9);
	CPPUNIT_TEST(test_cycle_length_10);
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
