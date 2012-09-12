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
        std::istringstream r("1 201\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   201);}

    void test_read2 () {
        std::istringstream r("12345 23456\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true); 
        CPPUNIT_ASSERT(i ==     12345);
        CPPUNIT_ASSERT(j ==    23456);}

    void test_read3 () {
        std::istringstream r("1 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   1000000);}

        /* decreasing range */
    void test_read4 () {
        std::istringstream r("100 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    100);
        CPPUNIT_ASSERT(j ==   1);}

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

    // i > j
    void test_eval_5 () {
        const int v = collatz_eval(1, 1000000);
        CPPUNIT_ASSERT(v == 525);}

    void test_eval_6 () {
        const int v = collatz_eval(12345, 23456);
        CPPUNIT_ASSERT(v == 279);}

    void test_eval_7 () {
        const int v = collatz_eval(500000, 401);
        CPPUNIT_ASSERT(v == 449);}

    void test_eval_8 () {
        const int v = collatz_eval(888, 888);
        CPPUNIT_ASSERT(v == 73);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print1 () {
        std::ostringstream w;
        collatz_print(w, 1000000, 1, 525);
        CPPUNIT_ASSERT(w.str() == "1000000 1 525\n");}

    void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 12345, 23456, 279);
        CPPUNIT_ASSERT(w.str() == "12345 23456 279\n");}

    void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 5000, 6000, 236);
        CPPUNIT_ASSERT(w.str() == "5000 6000 236\n");}
    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve1 () {
        std::istringstream r("12345 23456\n12276 91074\n11785 33150\n12609 31682\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "12345 23456 279\n12276 91074 351\n11785 33150 308\n12609 31682 308\n");}

    void test_solve2 () {
        std::istringstream r("867 5309\n223 3911\n226 3232\n512 210\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "867 5309 238\n223 3911 238\n226 3232 217\n512 210 144\n");}

    void test_solve_corner1 () {
        std::istringstream r("1 1\n1000000 1000000\n1000000 1\n1 1000000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n1000000 1000000 153\n1000000 1 525\n1 1000000 525\n");}

    // ----------
    // runCollatz
    // ----------
    void test_runCollatz_1 () {
        int i = 12345;
        int j = 23456;
        const int v = runCollatz(i, j);
        CPPUNIT_ASSERT(v == 279);
    }

    void test_runCollatz_2 () {
        int i = 1;
        int j = 1;
        const int v = runCollatz(i, j);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_runCollatz_3 () {
        int i = 1;
        int j = 1000000;
        const int v = runCollatz(i, j);
        CPPUNIT_ASSERT(v == 525);
    }

    void test_runCollatz_4 () {
        int i = 8888;
        int j = 9999;
        const int v = runCollatz(i, j);
        CPPUNIT_ASSERT(v == 260);
    }

    // -----------------
    // iterativeCollatsz
    // -----------------
    void test_iterativeCollatz_1 () {
        int i = 54321;
        const int v = iterativeCollatz(i);
        CPPUNIT_ASSERT(v == 40);
    }

    void test_iterativeCollatz_2 () {
        int i = 1000;
        const int v = iterativeCollatz(i);
        CPPUNIT_ASSERT(v == 112);
    }

    void test_iterativeCollatz_3 () {
        int i = 1;
        const int v = iterativeCollatz(i);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_iterativeCollatz_4 () {
        int i = 39393;
        const int v = iterativeCollatz(i);
        CPPUNIT_ASSERT(v == 50);
    }

    // ----------------
    // recursiveCollatz
    // ----------------
    void test_recursiveCollatz_1 () {
        int i = 12345;
        int length = 1;
        const int v = recursiveCollatz(i, length);
        CPPUNIT_ASSERT(v == 51);
    }

    void test_recursiveCollatz_2 () {
        int i = 765432;
        int length = 1;
        const int v = recursiveCollatz(i, length);
        CPPUNIT_ASSERT(v == 163);
    }

    void test_recursiveCollatz_3 () {
        int i = 8888;
        int length = 1;
        const int v = recursiveCollatz(i, length);
        CPPUNIT_ASSERT(v == 35);
    }

    void test_recursiveCollatz_4 () {
        int i = 987654;
        int length = 1;
        const int v = recursiveCollatz(i, length);
        CPPUNIT_ASSERT(v == 184);
    }

    // ----------
    // cacheCheck
    // ----------
    void test_cacheCheck_1 () {
        int i = 2000;
        int j = 3000;
        const int v = cacheCheck(i, j);
        CPPUNIT_ASSERT(v == 217);
    }

    void test_cacheCheck_2 () {
        int i = 200;
        int j = 200000;
        const int v = cacheCheck(i, j);
        CPPUNIT_ASSERT(v == 383);
    }

    void test_cacheCheck_3 () {
        int i = 500000;
        int j = 1000000;
        const int v = cacheCheck(i, j);
        CPPUNIT_ASSERT(v == 525);
    }

    void test_cacheCheck_4 () {
        int i = 256;
        int j = 4096;
        const int v = cacheCheck(i, j);
        CPPUNIT_ASSERT(v == 238);
    }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_read4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve_corner1);
    CPPUNIT_TEST(test_runCollatz_1);
    CPPUNIT_TEST(test_runCollatz_2);
    CPPUNIT_TEST(test_runCollatz_3);
    CPPUNIT_TEST(test_runCollatz_4);
    CPPUNIT_TEST(test_iterativeCollatz_1);
    CPPUNIT_TEST(test_iterativeCollatz_2);
    CPPUNIT_TEST(test_iterativeCollatz_3);
    CPPUNIT_TEST(test_iterativeCollatz_4);
    CPPUNIT_TEST(test_recursiveCollatz_1);
    CPPUNIT_TEST(test_recursiveCollatz_2);
    CPPUNIT_TEST(test_recursiveCollatz_3);
    CPPUNIT_TEST(test_recursiveCollatz_4);
    CPPUNIT_TEST(test_cacheCheck_1);
    CPPUNIT_TEST(test_cacheCheck_2);
    CPPUNIT_TEST(test_runCollatz_3);
    CPPUNIT_TEST(test_cacheCheck_4);
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
