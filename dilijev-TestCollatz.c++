// --------------------------------
// cs371p-collatz/TestCollatz.c++
// Copyright (C) 2012
// Doug Ilijev (dci89)
// --------------------------------

// -------ORIGINAL COPYRIGHT-------
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

#include "./Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

    /**
     * Test the basic read operation.
     */
    void test_read_1() {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);
    }

    /**
     * When there is only one input to read, the read should fail.
     */
    void test_read_2() {
        std::istringstream r("1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
        CPPUNIT_ASSERT(i == 1);
    }

    /**
     * When there are a number of complete lines followed by a line with only
     * one input, the read should fail.
     */
    void test_read_3() {
        std::istringstream r("1 10\n3\n");
        int i;
        int j;
        const bool b1 = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b1 == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);
        const bool b2 = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b2 == false);
        CPPUNIT_ASSERT(i == 3);
    }

    /**
     * Check whether the inputs can be read from multiple lines.
     * This should be allowed so that the reader is more robust.
     */
    void test_read_4() {
        std::istringstream r("1\n10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);
    }

    /**
     * Try reading text. The read should fail.
     */
    void test_read_5() {
        std::istringstream r("asd jkl\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * Try reading large numbers. Near the top of the range of a 32-bit int.
     */
    void test_read_6() {
        std::istringstream r("1000000000 1500000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1000000000);
        CPPUNIT_ASSERT(j == 1500000000);
    }

    /**
     * Try reading input with no newline following.
     */
    void test_read_7() {
        std::istringstream r("1 10");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);
    }

    /**
     * Try reading input that is ONLY a newline.
     */
    void test_read_8() {
        std::istringstream r("\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * Try reading input that is entirely empty.
     */
    void test_read_9() {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }

    // ----
    // next
    // ----

    /**
     * Test that for an input 1, the collatz_next returns an invalid number (0).
     * There is no next step when 1 is the input. Returning 0 allows the caller
     * to use the result of collatz_next to count how many next steps there are.
     */
    void test_next_1() {
        const int v = collatz_next(1);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     * Also test that the value 1 is computed as the final step.
     */
    void test_next_2() {
        const int v = collatz_next(2);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_3() {
        const int v = collatz_next(4);
        CPPUNIT_ASSERT(v == 2);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_4() {
        const int v = collatz_next(8);
        CPPUNIT_ASSERT(v == 4);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_5() {
        const int v = collatz_next(16);
        CPPUNIT_ASSERT(v == 8);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_6() {
        const int v = collatz_next(1024);
        CPPUNIT_ASSERT(v == 512);
    }

    /**
     * Test that the next step for odd numbers is 3n+1.
     */
    void test_next_7() {
        const int v = collatz_next(5);
        CPPUNIT_ASSERT(v == 16);
    }

    /**
     * Test that the next step for odd numbers is 3n+1.
     */
    void test_next_8() {
        const int v = collatz_next(341);
        CPPUNIT_ASSERT(v == 1024);
    }

    /**
     * Test that the next step for odd numbers is 3n+1.
     */
    void test_next_9() {
        const int v = collatz_next(123);
        const int expected = 123 * 3 + 1;  // = 370
        CPPUNIT_ASSERT(v == expected);
        CPPUNIT_ASSERT(v == 370);
    }

    /**
     * Test that the next step for even numbers n/2.
     */
    void test_next_10() {
        const int v = collatz_next(370);
        const int expected = 370/2;  // = 185
        CPPUNIT_ASSERT(v == expected);
        CPPUNIT_ASSERT(v == 185);
    }

    /**
     * Test that the next step for even numbers n/2.
     */
    void test_next_11() {
        const int v = collatz_next(50);
        const int expected = 50/2;  // = 25
        CPPUNIT_ASSERT(v == expected);
        CPPUNIT_ASSERT(v == 25);
    }

    // -----
    // cycle
    // -----

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_1() {
        const int v = collatz_cycle(4);
        CPPUNIT_ASSERT(v == 3);
    }

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_2() {
        const int v = collatz_cycle(8);
        CPPUNIT_ASSERT(v == 4);
    }

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_3() {
        const int v = collatz_cycle(16);
        CPPUNIT_ASSERT(v == 5);
    }

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_4() {
        const int v = collatz_cycle(1024);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Check cycle length for inputs away from powers of 2 by one step.
     */
    void test_cycle_5() {
        const int v = collatz_cycle(5);
        CPPUNIT_ASSERT(v == 6);
    }

    /**
     * Check cycle length for inputs away from powers of 2 by one step.
     */
    void test_cycle_6() {
        const int v = collatz_cycle(341);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_7() {
        const int v = collatz_cycle(9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_8() {
        const int v = collatz_cycle(28);
        CPPUNIT_ASSERT(v == 19);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_9() {
        const int v = collatz_cycle(14);
        CPPUNIT_ASSERT(v == 18);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_10() {
        const int v = collatz_cycle(7);
        CPPUNIT_ASSERT(v == 17);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_11() {
        const int v = collatz_cycle(22);
        CPPUNIT_ASSERT(v == 16);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_12() {
        const int v = collatz_cycle(11);
        CPPUNIT_ASSERT(v == 15);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_13() {
        const int v = collatz_cycle(34);
        CPPUNIT_ASSERT(v == 14);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_14() {
        const int v = collatz_cycle(17);
        CPPUNIT_ASSERT(v == 13);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_15() {
        const int v = collatz_cycle(52);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_16() {
        const int v = collatz_cycle(26);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_17() {
        const int v = collatz_cycle(13);
        CPPUNIT_ASSERT(v == 10);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_18() {
        const int v = collatz_cycle(40);
        CPPUNIT_ASSERT(v == 9);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_19() {
        const int v = collatz_cycle(20);
        CPPUNIT_ASSERT(v == 8);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_20() {
        const int v = collatz_cycle(10);
        CPPUNIT_ASSERT(v == 7);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     * Here is a result that is seen in later tests so this is a good stopping place.
     */
    void test_cycle_21() {
        const int v = collatz_cycle(5);
        CPPUNIT_ASSERT(v == 6);
    }

    // ----
    // eval
    // ----

    /**
     * Check sample input from sphere, first 10 valid inputs to the sequence.
     */
    void test_eval_1() {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check sample input from sphere, low 3-digit range.
     */
    void test_eval_2() {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
    }

    /**
     * Check sample input from sphere, small range of 3-digit numbers.
     */
    void test_eval_3() {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
    }

    /**
     * Check sample input from sphere, high 3-digit range.
     */
    void test_eval_4() {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_5() {
        const int v = collatz_eval(10, 1);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_6() {
        const int v = collatz_eval(200, 100);
        CPPUNIT_ASSERT(v == 125);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_7() {
        const int v = collatz_eval(210, 201);
        CPPUNIT_ASSERT(v == 89);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_8() {
        const int v = collatz_eval(1000, 900);
        CPPUNIT_ASSERT(v == 174);
    }

    /**
     * Check that we get the correct results for a single input
     * (use the same start and end numbers for the range).
     * Use powers of two because they are easy to calculate.
     */
    void test_eval_9() {
        const int v = collatz_eval(4, 4);
        CPPUNIT_ASSERT(v == 3);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 8 has 4 bits.
     */
    void test_eval_10() {
        const int v = collatz_eval(8, 8);
        CPPUNIT_ASSERT(v == 4);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 16 has five bits.
     */
    void test_eval_11() {
        const int v = collatz_eval(16, 16);
        CPPUNIT_ASSERT(v == 5);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 1024 has 11 bits.
     */
    void test_eval_12() {
        const int v = collatz_eval(1024, 1024);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Take a power of two and apply odd rule backwards.
     * (x-1)/3 = n. Where x=1024.
     * Add one to the cycle length for this input.
     */
    void test_eval_13() {
        const int v = collatz_eval(5, 5);
        CPPUNIT_ASSERT(v == 6);
    }

    /**
     * Take a power of two and apply odd rule backwards.
     * (x-1)/3 = n. Where x=1024.
     * Add one to the cycle length for this input.
     */
    void test_eval_14() {
        const int v = collatz_eval(341, 341);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Confirm correct value for 9 for next tests.
     */
    void test_eval_15() {
        const int v = collatz_eval(9, 9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the end of the range,
     * the correct value is returned.
     */
    void test_eval_16() {
        const int v = collatz_eval(1, 9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the beginning of the range,
     * the correct value is returned.
     */
    void test_eval_17() {
        const int v = collatz_eval(9, 17);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the end of the range,
     * the correct value is returned, even when range is reversed.
     */
    void test_eval_18() {
        const int v = collatz_eval(9, 1);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the beginning of the range,
     * the correct value is returned, even when range is reversed.
     */
    void test_eval_19() {
        const int v = collatz_eval(17, 9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Test for large inputs in range of the problem statement.
     */
    void test_eval_20() {
        const int v = collatz_eval(999999, 999999);
        CPPUNIT_ASSERT(v == 259);
    }

    /**
     * Test for inputs outside the range of the problem statement.
     */
    void test_eval_21() {
        const int v = collatz_eval(1000000, 1000000);
        CPPUNIT_ASSERT(v == 153);
    }

    /**
     * Test for very large inputs, outside the range of the problem statement.
     */
    void test_eval_22() {
        const int v = collatz_eval(1000000000, 1000000000);
        CPPUNIT_ASSERT(v == 101);
    }

    /**
     * Test for very large inputs. This will produce 32-bit integer overflow.
     * Solution is to use 64-bit long longs on the inside of the computation.
     */
    void test_eval_23() {
        const int v = collatz_eval(999999999, 999999999);
        CPPUNIT_ASSERT(v == 362);
    }

    /**
     * Test for very large inputs. This will produce 32-bit integer overflow.
     * Solution is to use 64-bit long longs on the inside of the computation.
     */
    void test_eval_24() {
        const int v = collatz_eval(1499999999, 1499999999);
        CPPUNIT_ASSERT(v == 360);
    }

    // -----
    // print
    // -----

    /**
     * Print bounds in ascending order.
     */
    void test_print_1() {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
    }

    /**
     * Print bounds in descending order.
     */
    void test_print_2() {
        std::ostringstream w;
        collatz_print(w, 10, 1, 20);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");
    }

    /**
     * Make sure the print function doesn't make any assumptions about the
     * answer to the problem for the given range (3rd arg is wrong answer).
     */
    void test_print_3() {
        std::ostringstream w;
        collatz_print(w, 10, 1, 1);
        CPPUNIT_ASSERT(w.str() == "10 1 1\n");
    }

    /**
     * Make sure the print function can handle the same number for each argument.
     */
    void test_print_4() {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");
    }

    /**
     * Make sure the print function can handle the same number for both ends of
     * the range.
     */
    void test_print_5() {
        std::ostringstream w;
        collatz_print(w, 10, 10, 1);
        CPPUNIT_ASSERT(w.str() == "10 10 1\n");
    }

    /**
     * Make sure the print function can handle large numbers.
     */
    void test_print_6() {
        std::ostringstream w;
        collatz_print(w, 1000000000, 1500000000, 2000000000);
        CPPUNIT_ASSERT(w.str() == "1000000000 1500000000 2000000000\n");
    }

    // -----
    // solve
    // -----

    /**
     * These inputs taken from sphere input set
     * and tested in test_eval_1-4.
     */
    void test_solve_1() {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(
                w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    }

    /**
     * These inputs taken from sphere input set (reversed range)
     * and tested in test_eval_5-8.
     */
    void test_solve_2() {
        std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(
                w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");
    }

    /**
     * These inputs are all powers of two and are therefore easy to desk check
     * and tested independently in test_eval_9-12.
     */
    void test_solve_3() {
        std::istringstream r("4 4\n8 8\n16 16\n1024 1024\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(
                w.str() == "4 4 3\n8 8 4\n16 16 5\n1024 1024 11\n");
    }

    /**
     * These inputs are one step away from a power of 2
     * and are therefore easy to desk check
     * and tested independently in test_eval_13-14.
     */
    void test_solve_4() {
        std::istringstream r("5 5\n341 341\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(
                w.str() == "5 5 6\n341 341 12\n");
    }

    /**
     * Test solving of range checks in test_eval_15-19.
     */
    void test_solve_5() {
        std::istringstream r("9 9\n1 9\n9 17\n9 1\n17 9\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(
                w.str() == "9 9 20\n1 9 20\n9 17 20\n9 1 20\n17 9 20\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);

    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_read_6);
    CPPUNIT_TEST(test_read_7);
    CPPUNIT_TEST(test_read_8);
    CPPUNIT_TEST(test_read_9);

    CPPUNIT_TEST(test_cycle_1);
    CPPUNIT_TEST(test_cycle_2);
    CPPUNIT_TEST(test_cycle_3);
    CPPUNIT_TEST(test_cycle_4);
    CPPUNIT_TEST(test_cycle_5);
    CPPUNIT_TEST(test_cycle_6);
    CPPUNIT_TEST(test_cycle_7);
    CPPUNIT_TEST(test_cycle_8);
    CPPUNIT_TEST(test_cycle_9);
    CPPUNIT_TEST(test_cycle_10);
    CPPUNIT_TEST(test_cycle_11);
    CPPUNIT_TEST(test_cycle_12);
    CPPUNIT_TEST(test_cycle_13);
    CPPUNIT_TEST(test_cycle_14);
    CPPUNIT_TEST(test_cycle_15);
    CPPUNIT_TEST(test_cycle_16);
    CPPUNIT_TEST(test_cycle_17);
    CPPUNIT_TEST(test_cycle_18);
    CPPUNIT_TEST(test_cycle_19);
    CPPUNIT_TEST(test_cycle_20);
    CPPUNIT_TEST(test_cycle_21);

    CPPUNIT_TEST(test_next_1);
    CPPUNIT_TEST(test_next_2);
    CPPUNIT_TEST(test_next_3);
    CPPUNIT_TEST(test_next_4);
    CPPUNIT_TEST(test_next_5);
    CPPUNIT_TEST(test_next_6);
    CPPUNIT_TEST(test_next_7);
    CPPUNIT_TEST(test_next_8);
    CPPUNIT_TEST(test_next_9);
    CPPUNIT_TEST(test_next_10);
    CPPUNIT_TEST(test_next_11);

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
    CPPUNIT_TEST(test_eval_15);
    CPPUNIT_TEST(test_eval_16);
    CPPUNIT_TEST(test_eval_17);
    CPPUNIT_TEST(test_eval_18);
    CPPUNIT_TEST(test_eval_19);
    CPPUNIT_TEST(test_eval_20);
    /*  These inputs are outside the range of the problem statement.
    CPPUNIT_TEST(test_eval_21);
    CPPUNIT_TEST(test_eval_22);
    CPPUNIT_TEST(test_eval_23);
    CPPUNIT_TEST(test_eval_24);
    */

    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_print_5);
    CPPUNIT_TEST(test_print_6);

    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);

    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
