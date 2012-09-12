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

    void test_read_2 (){
	std::istringstream r("23 150\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 23);
	CPPUNIT_ASSERT(j == 150);}

    void test_read_3 () {
	std::istringstream r("230 180\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i = 230);
	CPPUNIT_ASSERT(j = 180);}

    void test_read_4 () {
	std::istringstream r("720 900\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 720);
	CPPUNIT_ASSERT(j == 900);}


    // ----
    // cycle_length
    // ----
    
    void test_cycle_length_1 (){
	const int x = cycle_length(345);
	CPPUNIT_ASSERT(x == 126);
    }

    void test_cycle_length_2 (){
	const int x = cycle_length(3000);
	CPPUNIT_ASSERT(x == 49);
    }

    void test_cycle_length_3 (){
	const int x = cycle_length(99999);
	CPPUNIT_ASSERT(x == 227);
    }
    void test_cycle_length_4 (){
	const int x = cycle_length(1);
	CPPUNIT_ASSERT(x == 1);
    }
  
    void test_cycle_length_5 (){
	const int x = cycle_length(15);
	CPPUNIT_ASSERT(x == 18);
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

    void test_print_2 () {
	std::ostringstream w;
	collatz_print(w, 17, 87, 207);
	CPPUNIT_ASSERT(w.str() == "17 87 207\n");}

    void test_print_3() {
	std::ostringstream w;
	collatz_print(w, 30, 90, 120);
	CPPUNIT_ASSERT(w.str() == "30 90 120\n");}

    void test_print_4() {
	std::ostringstream w;
	collatz_print(w, 100, 200, 550);
	CPPUNIT_ASSERT(w.str() == "100 200 550\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2 () {
	std::istringstream r("495625 705494\n229705 378425\n608223 564520\n326615 702673\n");
	std::ostringstream w;
	collatz_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "495625 705494 470\n229705 378425 443\n608223 564520 434\n326615 702673 470\n");}

    void test_solve_3 () {
	std::istringstream r("4 4\n8 8\n16 16\n1024 1024\n");
	std::ostringstream w;
	collatz_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "4 4 3\n 8 8 4\n16 16 5\n 1024 1024 11\n");}

    void test_solve_4 () {
	std::istringstream r("9 9\n1 9\n9 17\n9 1\n17 9\n");
	std::ostringstream w;
	collatz_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "9 9 20\n1 9 20\n9 17 20\n9 1 20\n17 9 20\n");}

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
