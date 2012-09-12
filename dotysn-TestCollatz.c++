// --------------------------------

// 371/Projects/Collatz/TestCollatz.c++
// Simon Doty (uteid: dotysn)
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
     
    void test_read1 () {
        //test 1
		std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
	}
    void test_read2() {
 		//test 2
		std::istringstream s("15 10\n");
		int i;
		int j;
		const bool c = collatz_read(s, i, j);
		CPPUNIT_ASSERT(c == true);
		CPPUNIT_ASSERT(i ==   15);
		CPPUNIT_ASSERT(j == 10);
	}
	void test_read3() {
		//test 3
		std::istringstream t("1 1000000000\n");
		int i;
		int j;
		const bool d = collatz_read(t, i, j);
		CPPUNIT_ASSERT(d == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 1000000000);
	}
	void test_read4() {
		//test 4
		std::istringstream u("\n");
		int i;
		int j;
		const bool e = collatz_read(u, i, j);
		CPPUNIT_ASSERT(e == false);
		
	}
 
    
    //-----
	// count
	//-----
	void test_count1() {
		int n = 5;
		int v = count(n);
		CPPUNIT_ASSERT(v == 6);
	} 

    void test_count2() {
		int n = 300500;
		int v = count(n);
		std::cout << "answer for 837799: " << v << std::endl;
		CPPUNIT_ASSERT(v == 115);
	}	
	void test_count3() {
		int n = 9;
		int v = count(n);
		CPPUNIT_ASSERT(v== 20);
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
	void test_eval_5 () {
		const int v = collatz_eval(3, 907);
		CPPUNIT_ASSERT(v == 179);
	}

    // -----
    // print
    // -----

    void test_print1() {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
	}
	void test_print2() {
		std::ostringstream w;
		collatz_print(w, 156904, 341910, 200);
		CPPUNIT_ASSERT(w.str() == "156904 341910 200\n");
	}
    void test_print3() {
	    std::ostringstream w;
	    collatz_print(w, 1, 999999, 476);
	 	CPPUNIT_ASSERT(w.str() == "1 999999 476\n");
	}

    // -----
    // solve
    // -----

    void test_solve1() {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
	    CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}
	void test_solve2() {
	    std::istringstream r("1 1\n2 2\n999 999\n");
	    std::ostringstream w;
	    collatz_solve(r, w); 
	    CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n999 999 50\n");
	}
	void test_solve3 () {
		std::istringstream r("1 1000000\n2 1000000\n3 1000000\n");
		std::ostringstream w;
	    collatz_solve(r, w);
	    CPPUNIT_ASSERT(w.str() == "1 1000000 525\n2 1000000 525\n3 1000000 525\n");
	}
    
	
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestCollatz);
    
	CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
	CPPUNIT_TEST(test_read3);
	CPPUNIT_TEST(test_read4);	
	CPPUNIT_TEST(test_count1);
	CPPUNIT_TEST(test_count2);
	CPPUNIT_TEST(test_count3);
	CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_eval_5);    
	CPPUNIT_TEST(test_print1);
	CPPUNIT_TEST(test_print2);
	CPPUNIT_TEST(test_print3);    
	CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    
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

