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

	void test_readCornerOnes () {
		std::istringstream r("1 1\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i ==    1);
		CPPUNIT_ASSERT(j ==    1);}
	
	void test_readFail () {
		std::istringstream r("\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == false);}
	
	void test_readMax () {
		std::istringstream r("1000000 1000000\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 1000000);
		CPPUNIT_ASSERT(j == 1000000);}
	
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
	
	void test_eval_max () {
		const int v = collatz_eval(1, 1000000);
		CPPUNIT_ASSERT(v == 525);}
		
	void test_eval_backwards () {
		const int v = collatz_eval(100, 1);
		CPPUNIT_ASSERT(v == 119);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
		
	void test_print_ones () {
		std::ostringstream w;
		collatz_print(w, 1, 1, 1);
		CPPUNIT_ASSERT(w.str() == "1 1 1\n");}
	
	void test_print_max () {
		std::ostringstream w;
		collatz_print(w, 1, 1000000, 525);
		CPPUNIT_ASSERT(w.str() == "1 1000000 525\n");}
	
	void test_print_random () {
		std::ostringstream w;
		collatz_print(w, 13451, 63110, 234240);
		CPPUNIT_ASSERT(w.str() == "13451 63110 234240\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
		
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
		
	void test_solve_random () {
        std::istringstream r("18436 2896\n90414 89434\n226495 274475\n158910 67300\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "18436 2896 279\n90414 89434 315\n226495 274475 443\n158910 67300 383\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_readCornerOnes);
	CPPUNIT_TEST(test_readFail);
	CPPUNIT_TEST(test_readMax);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_eval_one);
	CPPUNIT_TEST(test_eval_max);
	CPPUNIT_TEST(test_eval_backwards);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_ones);
	CPPUNIT_TEST(test_print_max);
	CPPUNIT_TEST(test_print_random);
	CPPUNIT_TEST(test_print_ones);
    CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve_one);
	CPPUNIT_TEST(test_solve_backwards);
	CPPUNIT_TEST(test_solve_random);
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
