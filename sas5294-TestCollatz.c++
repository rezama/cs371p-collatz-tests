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

struct TestCollatz : CppUnit::TestFixture 
{

    // ----
    // read
    // ----
    
    void test_read_0() 
    {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
    }
    
    void test_read_1() 
    {
        std::istringstream r("201 210\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==   201);
        CPPUNIT_ASSERT(j ==   210);
    }
    
    void test_read_2()
    {
        std::istringstream r("900 1000\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==    900);
        CPPUNIT_ASSERT(j ==   1000);
    }
    
    void test_read_3() 
    {
        std::istringstream r("100 1000000\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==    100);
        CPPUNIT_ASSERT(j ==   1000000);
    }
    
    void test_read_4() 
    {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }
    
    void test_read_5() 
    {
        std::istringstream r("this is fun\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }
    
    // ----
    // eval
    // ----
    
    void test_eval_0() 
    {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
    }
    
    void test_eval_1() 
    {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
    }
    
    void test_eval_2() 
    {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
    }
    
    void test_eval_3() 
    {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
    }
    
    void test_eval_4()
    {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);
    }
    
    void test_eval_5() 
    {
        const int v = collatz_eval(2000, 3000);
        CPPUNIT_ASSERT(v == 217);
    }
    
    // -----
    // print
    // -----
    
    void test_print_0() 
    {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
    }
    
    void test_print_1() 
    {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");
    }
    
    void test_print_2()
    {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");
    }
    
    void test_print_3() 
    {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
    }
    
    // -----
    // solve
    // -----
    
    void test_solve_0() 
    {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    }
    
    void test_solve_1() 
    {
        std::istringstream r("10 100\n1 2\n99 100\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 100 119\n1 2 2\n99 100 26\n");
    }
    
    void test_solve_2() 
    {
        std::istringstream r("1 1\n2 2\n999 999\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n999 999 50\n");
    }
    
    void test_solve_3() 
    {
        std::istringstream r("1 1000000\n2 1000000\n3 1000000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1000000 525\n2 1000000 525\n3 1000000 525\n");
    }
    
    void test_collatz_recurse_0()
    {
        const int v = collatz_recurse(1);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_collatz_recurse_1()
    {
        const int v = collatz_recurse(999);
        CPPUNIT_ASSERT(v == 50);
    }

    void test_collatz_recurse_2()
    {
        const int v = collatz_recurse(3);
        CPPUNIT_ASSERT(v == 8);
    }

    void test_collatz_recurse_3()
    {
        const int v = collatz_recurse(1337);
        CPPUNIT_ASSERT(v == 45);
    }

    void test_collatz_recurse_4()
    {
        const int v = collatz_recurse(1000000);
        CPPUNIT_ASSERT(v == 153);
    }

    void test_collatz_recurse_5()
    {
        const int v = collatz_recurse(999999);
        CPPUNIT_ASSERT(v == 259);
    }

    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_0);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_eval_0);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_print_0);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_0);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_collatz_recurse_0);
    CPPUNIT_TEST(test_collatz_recurse_1);
    CPPUNIT_TEST(test_collatz_recurse_2);
    CPPUNIT_TEST(test_collatz_recurse_3);
    CPPUNIT_TEST(test_collatz_recurse_4);
    CPPUNIT_TEST(test_collatz_recurse_5);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;
}

