// --------------------------------
// Graham Benevelli
// EID: grambo
// CSID: grahambo
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
  // init
  // ----

  void test_init_1 () {
    collatz_init();
    CPPUNIT_ASSERT(b[1] == 1);
    CPPUNIT_ASSERT(b[2] == 0);
  }

  void test_init_2 () {
    collatz_init();
    collatz_eval(1, 10);
    collatz_init();
    CPPUNIT_ASSERT(b[1] == 1);
    CPPUNIT_ASSERT(b[2] == 0);
  }

  void test_init_3 () {
    collatz_init();
    collatz_eval(1, 1000000);
    collatz_init();
    CPPUNIT_ASSERT(b[1] == 1);
    CPPUNIT_ASSERT(b[2] == 0);
  }

    // ----
    // read
    // ----
    
    void test_read () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
    }
    
    void test_read_1 () {
        std::istringstream r("201 210\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==   201);
        CPPUNIT_ASSERT(j ==   210);
    }
    
    void test_read_2 () {
        std::istringstream r("900 1000\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==    900);
        CPPUNIT_ASSERT(j ==   1000);
    }
    
    void test_read_3 () {
        std::istringstream r("100 1000000\n");
        int i;
        int j;
        const bool bo = collatz_read(r, i, j);
        CPPUNIT_ASSERT(bo == true);
        CPPUNIT_ASSERT(i ==    100);
        CPPUNIT_ASSERT(j ==   1000000);
    }
    
    void test_read_4 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}
    
    void test_read_5 () {
        std::istringstream r("10 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    10);
        CPPUNIT_ASSERT(j ==   1);}
    
    void test_read_6 () {
        std::istringstream r("1000000 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1000000);
        CPPUNIT_ASSERT(j ==   1000000);}
    
    void test_read_7 () {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}
    
    void test_read_8 () {
        std::istringstream r("lets makes some works\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}
    
    void test_read_9 () {
        std::istringstream r("words\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}
    
    void test_read_10 () {
        std::istringstream r("\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}
    
    // ----
    // eval
    // ----
    
    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
    }
    
    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
    }
    
    void test_eval_3 () {
        const int v = collatz_eval(200, 100);
        CPPUNIT_ASSERT(v == 125);
    }
    
    void test_eval_4 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
    }
    
    void test_eval_5 () {
        const int v = collatz_eval(210, 201);
        CPPUNIT_ASSERT(v == 89);
    }
    
    void test_eval_6 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
    }
    
    void test_eval_7 () {
        const int v = collatz_eval(1000, 900);
        CPPUNIT_ASSERT(v == 174);
    }
    
    void test_eval_8 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);
    }
    
    void test_eval_9 () {
        const int v = collatz_eval(2000, 3000);
        CPPUNIT_ASSERT(v == 217);
    }
    
    void test_eval_10 () {
        const int v = collatz_eval(3000, 2000);
        CPPUNIT_ASSERT(v == 217);
    }
    
    void test_eval_11 () {
        const int v = collatz_eval(999999, 1000000);
        CPPUNIT_ASSERT(v == 259);
    }
    
    void test_eval_12 () {
        const int v = collatz_eval(1000000, 999999);
        CPPUNIT_ASSERT(v == 259);
    }
    
    void test_eval_13 () {
        const int v = collatz_eval(1, 1000000);
        CPPUNIT_ASSERT(v == 525);}
    
    void test_eval_14 () {
        const int v = collatz_eval(1000000, 1);
        CPPUNIT_ASSERT(v == 525);}
    
    //-----------------
    // eval single value
    // -----------------
    
    void test_eval_single_1 () {
        const int v = collatz_eval_single(1);
        CPPUNIT_ASSERT(v == 1);
    }
    
    void test_eval_single_2 () {
        const int v = collatz_eval_single(100);
        CPPUNIT_ASSERT(v == 26);
    }
    
    void test_eval_single_3 () {
        const int v = collatz_eval_single(1000);
        CPPUNIT_ASSERT(v == 112);
    }

    void test_eval_single_4 () {
      const int v = collatz_eval_single(1000000);
      CPPUNIT_ASSERT(v == 153);
    }

    void test_eval_single_5 () {
      const int v = collatz_eval_single(113383);
      CPPUNIT_ASSERT(v == 248);
    }

    void test_eval_single_6 () {
      const int v = collatz_eval_single(159487);
      CPPUNIT_ASSERT(v == 184);
    }
    
    // -----
    // print
    // -----
    
    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
    }
    
    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");
    }
    
    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");
    }
    
    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
    }
    
    // -----
    // solve
    // -----
    
    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    }
    
    void test_solve_1 () {
        std::istringstream r("10 100\n1 2\n99 100\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "10 100 119\n1 2 2\n99 100 26\n");
    }
    
    void test_solve_2 () {
        std::istringstream r("1 1\n2 2\n999 999\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n999 999 50\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("1 1000000\n2 1000000\n3 1000000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1000000 525\n2 1000000 525\n3 1000000 525\n");
    }
    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_init_1);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_read_6);
    CPPUNIT_TEST(test_read_7);
    CPPUNIT_TEST(test_read_8);
    CPPUNIT_TEST(test_read_9);
    CPPUNIT_TEST(test_read_10);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_9);
    CPPUNIT_TEST(test_eval_10);
    CPPUNIT_TEST(test_eval_11);
    CPPUNIT_TEST(test_eval_12);
    CPPUNIT_TEST(test_eval_13);
    CPPUNIT_TEST(test_eval_14);
    CPPUNIT_TEST(test_eval_single_1);
    CPPUNIT_TEST(test_eval_single_2);
    CPPUNIT_TEST(test_eval_single_3);
    CPPUNIT_TEST(test_eval_single_4);
    CPPUNIT_TEST(test_eval_single_5);
    CPPUNIT_TEST(test_eval_single_6);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};
// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;
    collatz_init();

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;}
