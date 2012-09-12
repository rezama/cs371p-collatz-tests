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

#include <iostream>  // cout, endl
#include <sstream>   // istringtstream, ostringstream
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"              // TestFixture
#include "cppunit/TextTestRunner.h"           // TextTestRunner

#include "./Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // =========================
    // meta cache helper methods
    // =========================

    // --------------------------
    // collatz_cache_inCacheBlock
    // --------------------------

    void test_collatz_cache_inCacheBlock_1() {
        const unsigned int v = collatz_cache_inCacheBlock(1, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    void test_collatz_cache_inCacheBlock_2() {
        const unsigned int v = collatz_cache_inCacheBlock(499, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    void test_collatz_cache_inCacheBlock_3() {
        const unsigned int v = collatz_cache_inCacheBlock(500, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    void test_collatz_cache_inCacheBlock_4() {
        const unsigned int v = collatz_cache_inCacheBlock(501, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_collatz_cache_inCacheBlock_5() {
        const unsigned int v = collatz_cache_inCacheBlock(999, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_collatz_cache_inCacheBlock_6() {
        const unsigned int v = collatz_cache_inCacheBlock(1000, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    void test_collatz_cache_inCacheBlock_7() {
        const unsigned int v = collatz_cache_inCacheBlock(1001, 500);
        CPPUNIT_ASSERT(v == 2);
    }

    void test_collatz_cache_inCacheBlock_8() {
        const unsigned int v = collatz_cache_inCacheBlock(789456, 500);
        CPPUNIT_ASSERT(v == 1578);
    }

    void test_collatz_cache_inCacheBlock_9() {
        const unsigned int v = collatz_cache_inCacheBlock(1000000, 500);
        CPPUNIT_ASSERT(v == 1999);
    }

    void test_collatz_cache_inCacheBlock_10() {
        const unsigned int v = collatz_cache_inCacheBlock(999999, 500);
        CPPUNIT_ASSERT(v == 1999);
    }

    void test_collatz_cache_inCacheBlock_11() {
        const unsigned int v = collatz_cache_inCacheBlock(999501, 500);
        CPPUNIT_ASSERT(v == 1999);
    }

    void test_collatz_cache_inCacheBlock_12() {
        const unsigned int v = collatz_cache_inCacheBlock(999500, 500);
        CPPUNIT_ASSERT(v == 1998);
    }

    /**
     * Check what happens when input is out of cache range.
     */
    void test_collatz_cache_inCacheBlock_13() {
        const unsigned int v = collatz_cache_inCacheBlock(1000001, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500);
        // would equal NUMBLOCKS but I hardcoded 500 into the tests
    }

    /**
     * Check what happens when input is out of cache range.
     */
    void test_collatz_cache_inCacheBlock_14() {
        const unsigned int v = collatz_cache_inCacheBlock(123456789, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500);
        // would equal NUMBLOCKS but I hardcoded 500 into the tests
    }

    // -----------------------------
    // collatz_cache_isBottomOfRange
    // -----------------------------

    /**
     * true for bottom of range 0
     */
    void test_collatz_cache_isBottomOfRange_1() {
        const bool b = collatz_cache_isBottomOfRange(1, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * false for top of range 0
     */
    void test_collatz_cache_isBottomOfRange_2() {
        const bool b = collatz_cache_isBottomOfRange(500, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * false for random sample from range 0
     */
    void test_collatz_cache_isBottomOfRange_3() {
        const bool b = collatz_cache_isBottomOfRange(123, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * bottom of random range
     */
    void test_collatz_cache_isBottomOfRange_4() {
        const bool b = collatz_cache_isBottomOfRange(50501, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * bottom of random range
     */
    void test_collatz_cache_isBottomOfRange_5() {
        const bool b = collatz_cache_isBottomOfRange(1001, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * top of random range
     */
    void test_collatz_cache_isBottomOfRange_6() {
        const bool b = collatz_cache_isBottomOfRange(50500, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * top of random range
     */
    void test_collatz_cache_isBottomOfRange_7() {
        const bool b = collatz_cache_isBottomOfRange(1000, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * bottom of highest range
     */
    void test_collatz_cache_isBottomOfRange_8() {
        const bool b = collatz_cache_isBottomOfRange(999501, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * top of highest range
     */
    void test_collatz_cache_isBottomOfRange_9() {
        const bool b = collatz_cache_isBottomOfRange(1000000, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * middle of highest range
     */
    void test_collatz_cache_isBottomOfRange_10() {
        const bool b = collatz_cache_isBottomOfRange(999767, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * beyond highest input
     */
    void test_collatz_cache_isBottomOfRange_11() {
        const bool b = collatz_cache_isBottomOfRange(1000001, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * beyond highest input
     */
    void test_collatz_cache_isBottomOfRange_12() {
        const bool b = collatz_cache_isBottomOfRange(1000501, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * beyond highest input
     */
    void test_collatz_cache_isBottomOfRange_13() {
        const bool b = collatz_cache_isBottomOfRange(2000501, 500);
        CPPUNIT_ASSERT(b == false);
    }

    // -----------------------------
    // collatz_cache_isTopOfRange
    // -----------------------------

    /**
     * true for bottom of range 0
     */
    void test_collatz_cache_isTopOfRange_1() {
        const bool b = collatz_cache_isTopOfRange(1, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * false for top of range 0
     */
    void test_collatz_cache_isTopOfRange_2() {
        const bool b = collatz_cache_isTopOfRange(500, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * false for random sample from range 0
     */
    void test_collatz_cache_isTopOfRange_3() {
        const bool b = collatz_cache_isTopOfRange(123, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * bottom of random range
     */
    void test_collatz_cache_isTopOfRange_4() {
        const bool b = collatz_cache_isTopOfRange(50501, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * bottom of random range
     */
    void test_collatz_cache_isTopOfRange_5() {
        const bool b = collatz_cache_isTopOfRange(1001, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * top of random range
     */
    void test_collatz_cache_isTopOfRange_6() {
        const bool b = collatz_cache_isTopOfRange(50500, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * top of random range
     */
    void test_collatz_cache_isTopOfRange_7() {
        const bool b = collatz_cache_isTopOfRange(1000, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * bottom of highest range
     */
    void test_collatz_cache_isTopOfRange_8() {
        const bool b = collatz_cache_isTopOfRange(999501, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * top of highest range
     */
    void test_collatz_cache_isTopOfRange_9() {
        const bool b = collatz_cache_isTopOfRange(1000000, 500);
        CPPUNIT_ASSERT(b == true);
    }

    /**
     * middle of highest range
     */
    void test_collatz_cache_isTopOfRange_10() {
        const bool b = collatz_cache_isTopOfRange(999767, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * beyond highest input
     */
    void test_collatz_cache_isTopOfRange_11() {
        const bool b = collatz_cache_isTopOfRange(1000500, 500);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * beyond highest input
     */
    void test_collatz_cache_isTopOfRange_12() {
        const bool b = collatz_cache_isTopOfRange(2000500, 500);
        CPPUNIT_ASSERT(b == false);
    }

    // ----------------------
    // collatz_cache_lowIndex
    // ----------------------

    /**
     * There is no cache range which is fully covered by any part
     * of the given range. We should still say to use the next highest range.
     */
    void test_collatz_cache_lowIndex_1() {
        const unsigned int v = collatz_cache_lowIndex(123, 421, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * Lower bound is lowest of this range, so return this range.
     */
    void test_collatz_cache_lowIndex_2() {
        const unsigned int v = collatz_cache_lowIndex(1, 421, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * Same as 1; upper bound is highest of the range, but that doesn't affect
     * this test.
     */
    void test_collatz_cache_lowIndex_3() {
        const unsigned int v = collatz_cache_lowIndex(123, 500, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * This is a valid range for using the cache because 1 and 500 are the
     * endpoints of a cached range. Specifically, this is range 0.
     */
    void test_collatz_cache_lowIndex_4() {
        const unsigned int v = collatz_cache_lowIndex(1, 500, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * This is a valid range for using the cache, as above. Check that the
     * range is one less than NUMBLOCKS. This is the highest possible range.
     */
    void test_collatz_cache_lowIndex_5() {
        const unsigned int v = collatz_cache_lowIndex(999501, 1000000, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500 - 1);
    }

    /**
     * This should give the range corresponding to 1501 i.e. 3
     */
    void test_collatz_cache_lowIndex_6() {
        const unsigned int v = collatz_cache_lowIndex(1234, 456132, 500);
        CPPUNIT_ASSERT(v == 3);
    }

    /**
     * This is at the bottom of a valid range.
     */
    void test_collatz_cache_lowIndex_7() {
        const unsigned int v = collatz_cache_lowIndex(15001, 456132, 500);
        CPPUNIT_ASSERT(v == 30);
    }

    /**
     * This range is not wide enough to use the cache,
     * but that will be handled by some other program logic,
     * return this range, as above.
     */
    void test_collatz_cache_lowIndex_8() {
        const unsigned int v = collatz_cache_lowIndex(15001, 15111, 500);
        CPPUNIT_ASSERT(v == 30);
    }

    /**
     * Not at the bottom of a valid range, return the next highest.
     */
    void test_collatz_cache_lowIndex_9() {
        const unsigned int v = collatz_cache_lowIndex(15111, 456132, 500);
        CPPUNIT_ASSERT(v == 31);
    }

    /**
     * Above max input (low).
     */
    void test_collatz_cache_lowIndex_10() {
        const unsigned int v = collatz_cache_lowIndex(1000001, 1000001, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500);
    }

    /**
     * Above max input (high). Should be no effect.
     */
    void test_collatz_cache_lowIndex_11() {
        const unsigned int v = collatz_cache_lowIndex(123, 2000000, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * Near the top, will become an invalid index unless corrected to cap
     * at NUMBLOCKS-1
     */
    void test_collatz_cache_lowIndex_12() {
        const unsigned int v = collatz_cache_lowIndex(999900, 999999, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500-1);
    }

    // -----------------------
    // collatz_cache_highIndex
    // -----------------------

    /**
     * High index is at bottom of range, this is the lowest range.
     * Low cap at zero. Do not go below zero.
     */
    void test_collatz_cache_highIndex_1() {
        const unsigned int v = collatz_cache_highIndex(1, 1, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * High index is not top of a range, this is the lowest range.
     * Low cap at zero. Do not go below zero.
     */
    void test_collatz_cache_highIndex_2() {
        const unsigned int v = collatz_cache_highIndex(1, 345, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * High index is top of a range, use this range.
     */
    void test_collatz_cache_highIndex_3() {
        const unsigned int v = collatz_cache_highIndex(1, 500, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * High index is top of a range, use this range.
     */
    void test_collatz_cache_highIndex_4() {
        const unsigned int v = collatz_cache_highIndex(123, 500, 500);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * High index is top of a range, use this range.
     */
    void test_collatz_cache_highIndex_5() {
        const unsigned int v = collatz_cache_highIndex(654, 1000, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * Wider range. High index is top of a range, use this range.
     */
    void test_collatz_cache_highIndex_6() {
        const unsigned int v = collatz_cache_highIndex(11654, 15500, 500);
        CPPUNIT_ASSERT(v == 30);
    }

    /**
     * Wider range. High index is not top of a range, use previous range.
     */
    void test_collatz_cache_highIndex_7() {
        const unsigned int v = collatz_cache_highIndex(11654, 15400, 500);
        CPPUNIT_ASSERT(v == 29);
    }

    /**
     * Wide range. High index is not top of the range, use this range.
     */
    void test_collatz_cache_highIndex_8() {
        const unsigned int v = collatz_cache_highIndex(900456, 1000000, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500 - 1);
    }

    /**
     * Above MAX_INPUT. Return NUMBLOCKS = MAX_INPUT/INCREMENT.
     */
    void test_collatz_cache_highIndex_9() {
        const unsigned int v = collatz_cache_highIndex(900456, 1000005, 500);
        CPPUNIT_ASSERT(v == MAX_INPUT/500);
    }

    /**
     * High index is at bottom of range.
     */
    void test_collatz_cache_highIndex_10() {
        const unsigned int v = collatz_cache_highIndex(512, 1001, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * High index is not top of a range.
     */
    void test_collatz_cache_highIndex_11() {
        const unsigned int v = collatz_cache_highIndex(512, 1234, 500);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * High index is top of a range, use this range.
     */
    void test_collatz_cache_highIndex_12() {
        const unsigned int v = collatz_cache_highIndex(512, 1500, 500);
        CPPUNIT_ASSERT(v == 2);
    }

    // -----------------
    // collatz_cache_max
    // -----------------

    /*
     * These tests assume the specific iteration of the cache for intervals of 500.
     */

    void test_collatz_cache_max_500_1() {
        const unsigned int v = collatz_cache_max(0, 2);
        CPPUNIT_ASSERT(v == 182);
    }

    void test_collatz_cache_max_500_2() {
        const unsigned int v = collatz_cache_max(0, 3);
        CPPUNIT_ASSERT(v == 182);
    }

    void test_collatz_cache_max_500_3() {
        const unsigned int v = collatz_cache_max(0, 4);
        CPPUNIT_ASSERT(v == 209);
    }

    /**
     * Begin and end of range is same.
     */
    void test_collatz_cache_max_500_4() {
        const unsigned int v = collatz_cache_max(0, 0);
        CPPUNIT_ASSERT(v == 144);
    }

    /**
     * Middle range of indexes.
     */
    void test_collatz_cache_max_500_5() {
        const unsigned int v = collatz_cache_max(10, 12);
        CPPUNIT_ASSERT(v == 262);
    }

    void test_collatz_cache_max_500_6() {
        const unsigned int v = collatz_cache_max(1997, 1999);
        CPPUNIT_ASSERT(v == 396);
    }

    // -----------
    // USAGE TESTS
    // -----------

    /**
     * Test how the functions can be used together.
     *      collatz_cache_lowIndex
     *      collatz_cache_highIndex
     *      collatz_cache_max
     *
     * Range picked so that there is no caching range.
     */
    void test_collatz_cache_500_usage_1() {
        unsigned int low = 5123;
        unsigned int high = 5234;

        unsigned int lowIndex = collatz_cache_lowIndex(low, high, INCREMENT);
        unsigned int highIndex = collatz_cache_highIndex(low, high, INCREMENT);

        CPPUNIT_ASSERT(highIndex < lowIndex);  // strictly less
        CPPUNIT_ASSERT(lowIndex == 11);
        CPPUNIT_ASSERT(highIndex == 9);

        unsigned int v = collatz_cache_max(lowIndex, highIndex);
        CPPUNIT_ASSERT(v == 1);  // in other words, cache wasn't searched
    }

    /**
     * Test how the functions can be used together.
     *      collatz_cache_lowIndex
     *      collatz_cache_highIndex
     *      collatz_cache_max
     */
    void test_collatz_cache_500_usage_2() {
        unsigned int low = 5001;
        unsigned int high = 5678;

        unsigned int lowIndex = collatz_cache_lowIndex(low, high, INCREMENT);
        unsigned int highIndex = collatz_cache_highIndex(low, high, INCREMENT);

        CPPUNIT_ASSERT(highIndex == lowIndex);
        CPPUNIT_ASSERT(lowIndex == 10);
        CPPUNIT_ASSERT(highIndex == 10);

        unsigned int v = collatz_cache_max(lowIndex, highIndex);
        CPPUNIT_ASSERT(v == 192);
    }

    /**
     * Test how the functions can be used together.
     *      collatz_cache_lowIndex
     *      collatz_cache_highIndex
     *      collatz_cache_max
     *
     * Range endpoints are at the bottom and top of a single range.
     */
    void test_collatz_cache_500_usage_3() {
        unsigned int low = 5001;
        unsigned int high = 5500;

        unsigned int lowIndex = collatz_cache_lowIndex(low, high, INCREMENT);
        unsigned int highIndex = collatz_cache_highIndex(low, high, INCREMENT);

        CPPUNIT_ASSERT(highIndex == lowIndex);
        CPPUNIT_ASSERT(lowIndex == 10);
        CPPUNIT_ASSERT(highIndex == 10);

        unsigned int v = collatz_cache_max(lowIndex, highIndex);
        CPPUNIT_ASSERT(v == 192);
    }

    /**
     * Test how the functions can be used together.
     *      collatz_cache_lowIndex
     *      collatz_cache_highIndex
     *      collatz_cache_max
     *
     * Range endpoints span more than one cache block.
     */
    void test_collatz_cache_500_usage_4() {
        unsigned int low = 5123;
        unsigned int high = 7123;

        unsigned int lowIndex = collatz_cache_lowIndex(low, high, INCREMENT);
        unsigned int highIndex = collatz_cache_highIndex(low, high, INCREMENT);

        CPPUNIT_ASSERT(highIndex >= lowIndex);
        CPPUNIT_ASSERT(lowIndex == 11);
        CPPUNIT_ASSERT(highIndex == 13);

        unsigned int v = collatz_cache_max(lowIndex, highIndex);
        CPPUNIT_ASSERT(v == 262);
    }

    // =====================
    // core solution methods
    // =====================

    // ----
    // read
    // ----

    /**
     * Test the basic read operation.
     */
    void test_read_1() {
        std::istringstream r("1 10\n");
        unsigned int i;
        unsigned int j;
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
        unsigned int i;
        unsigned int j;
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
        unsigned int i;
        unsigned int j;
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
        unsigned int i;
        unsigned int j;
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
        unsigned int i;
        unsigned int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * Try reading large numbers. Near the top of the range of a 32-bit int.
     */
    void test_read_6() {
        std::istringstream r("1000000000 1500000000\n");
        unsigned int i;
        unsigned int j;
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
        unsigned int i;
        unsigned int j;
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
        unsigned int i;
        unsigned int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
    }

    /**
     * Try reading input that is entirely empty.
     */
    void test_read_9() {
        std::istringstream r("");
        unsigned int i;
        unsigned int j;
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
        const unsigned int v = collatz_next(1);
        CPPUNIT_ASSERT(v == 0);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     * Also test that the value 1 is computed as the final step.
     */
    void test_next_2() {
        const unsigned int v = collatz_next(2);
        CPPUNIT_ASSERT(v == 1);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_3() {
        const unsigned int v = collatz_next(4);
        CPPUNIT_ASSERT(v == 2);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_4() {
        const unsigned int v = collatz_next(8);
        CPPUNIT_ASSERT(v == 4);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_5() {
        const unsigned int v = collatz_next(16);
        CPPUNIT_ASSERT(v == 8);
    }

    /**
     * Test that the next step for powers of two 2^n = 2^(n-1).
     */
    void test_next_6() {
        const unsigned int v = collatz_next(1024);
        CPPUNIT_ASSERT(v == 512);
    }

    /**
     * Test that the next step for odd numbers is 3n+1.
     */
    void test_next_7() {
        const unsigned int v = collatz_next(5);
        CPPUNIT_ASSERT(v == 16);
    }

    /**
     * Test that the next step for odd numbers is 3n+1.
     */
    void test_next_8() {
        const unsigned int v = collatz_next(341);
        CPPUNIT_ASSERT(v == 1024);
    }

    /**
     * Test that the next step for odd numbers is 3n+1.
     */
    void test_next_9() {
        const unsigned int v = collatz_next(123);
        const unsigned int expected = 123 * 3 + 1;  // = 370
        CPPUNIT_ASSERT(v == expected);
        CPPUNIT_ASSERT(v == 370);
    }

    /**
     * Test that the next step for even numbers n/2.
     */
    void test_next_10() {
        const unsigned int v = collatz_next(370);
        const unsigned int expected = 370/2;  // = 185
        CPPUNIT_ASSERT(v == expected);
        CPPUNIT_ASSERT(v == 185);
    }

    /**
     * Test that the next step for even numbers n/2.
     */
    void test_next_11() {
        const unsigned int v = collatz_next(50);
        const unsigned int expected = 50/2;  // = 25
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
        const unsigned int v = collatz_cycle(4);
        CPPUNIT_ASSERT(v == 3);
    }

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_2() {
        const unsigned int v = collatz_cycle(8);
        CPPUNIT_ASSERT(v == 4);
    }

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_3() {
        const unsigned int v = collatz_cycle(16);
        CPPUNIT_ASSERT(v == 5);
    }

    /**
     * Check cycle length of powers of 2.
     */
    void test_cycle_4() {
        const unsigned int v = collatz_cycle(1024);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Check cycle length for inputs away from powers of 2 by one step.
     */
    void test_cycle_5() {
        const unsigned int v = collatz_cycle(5);
        CPPUNIT_ASSERT(v == 6);
    }

    /**
     * Check cycle length for inputs away from powers of 2 by one step.
     */
    void test_cycle_6() {
        const unsigned int v = collatz_cycle(341);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_7() {
        const unsigned int v = collatz_cycle(9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_8() {
        const unsigned int v = collatz_cycle(28);
        CPPUNIT_ASSERT(v == 19);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_9() {
        const unsigned int v = collatz_cycle(14);
        CPPUNIT_ASSERT(v == 18);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_10() {
        const unsigned int v = collatz_cycle(7);
        CPPUNIT_ASSERT(v == 17);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_11() {
        const unsigned int v = collatz_cycle(22);
        CPPUNIT_ASSERT(v == 16);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_12() {
        const unsigned int v = collatz_cycle(11);
        CPPUNIT_ASSERT(v == 15);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_13() {
        const unsigned int v = collatz_cycle(34);
        CPPUNIT_ASSERT(v == 14);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_14() {
        const unsigned int v = collatz_cycle(17);
        CPPUNIT_ASSERT(v == 13);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_15() {
        const unsigned int v = collatz_cycle(52);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_16() {
        const unsigned int v = collatz_cycle(26);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_17() {
        const unsigned int v = collatz_cycle(13);
        CPPUNIT_ASSERT(v == 10);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_18() {
        const unsigned int v = collatz_cycle(40);
        CPPUNIT_ASSERT(v == 9);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_19() {
        const unsigned int v = collatz_cycle(20);
        CPPUNIT_ASSERT(v == 8);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     */
    void test_cycle_20() {
        const unsigned int v = collatz_cycle(10);
        CPPUNIT_ASSERT(v == 7);
    }

    /**
     * Check cycle length for a sample input from Sphere.
     * Here is a result that is seen in later tests so this is a good stopping place.
     */
    void test_cycle_21() {
        const unsigned int v = collatz_cycle(5);
        CPPUNIT_ASSERT(v == 6);
    }

    /**
     * Check that this cycle length doesn't cause overflow and terminates.
     */
    void test_cycle_22() {
        const unsigned int v = collatz_cycle(999167);
        CPPUNIT_ASSERT(v == 321);
    }

    // ----------------
    // max_cycle_length
    // ----------------

    /**
     * Check sample input from sphere, first 10 valid inputs to the sequence.
     */
    void test_max_cycle_length_1() {
        const unsigned int v = collatz_max_cycle_length(1, 10);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check sample input from sphere, low 3-digit range.
     */
    void test_max_cycle_length_2() {
        const unsigned int v = collatz_max_cycle_length(100, 200);
        CPPUNIT_ASSERT(v == 125);
    }

    /**
     * Check sample input from sphere, small range of 3-digit numbers.
     */
    void test_max_cycle_length_3() {
        const unsigned int v = collatz_max_cycle_length(201, 210);
        CPPUNIT_ASSERT(v == 89);
    }

    /**
     * Check sample input from sphere, high 3-digit range.
     */
    void test_max_cycle_length_4() {
        const unsigned int v = collatz_max_cycle_length(900, 1000);
        CPPUNIT_ASSERT(v == 174);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 16 has five bits.
     */
    void test_max_cycle_length_5() {
        const unsigned int v = collatz_max_cycle_length(16, 16);
        CPPUNIT_ASSERT(v == 5);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 1024 has 11 bits.
     */
    void test_max_cycle_length_6() {
        const unsigned int v = collatz_max_cycle_length(1024, 1024);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Take a power of two and apply odd rule backwards.
     * (x-1)/3 = n. Where x=1024.
     * Add one to the cycle length for this input.
     */
    void test_max_cycle_length_7() {
        const unsigned int v = collatz_max_cycle_length(5, 5);
        CPPUNIT_ASSERT(v == 6);
    }

    /**
     * Take a power of two and apply odd rule backwards.
     * (x-1)/3 = n. Where x=1024.
     * Add one to the cycle length for this input.
     */
    void test_max_cycle_length_8() {
        const unsigned int v = collatz_max_cycle_length(341, 341);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Test the range where an integer overflow was detected.
     */
    void test_max_cycle_length_9() {
        const unsigned int v = collatz_max_cycle_length(999164, 999170);
        CPPUNIT_ASSERT(v == 321);
    }

    // ----
    // eval
    // ----

    /**
     * Check sample input from sphere, first 10 valid inputs to the sequence.
     */
    void test_eval_1() {
        const unsigned int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check sample input from sphere, low 3-digit range.
     */
    void test_eval_2() {
        const unsigned int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
    }

    /**
     * Check sample input from sphere, small range of 3-digit numbers.
     */
    void test_eval_3() {
        const unsigned int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
    }

    /**
     * Check sample input from sphere, high 3-digit range.
     */
    void test_eval_4() {
        const unsigned int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_5() {
        const unsigned int v = collatz_eval(10, 1);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_6() {
        const unsigned int v = collatz_eval(200, 100);
        CPPUNIT_ASSERT(v == 125);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_7() {
        const unsigned int v = collatz_eval(210, 201);
        CPPUNIT_ASSERT(v == 89);
    }

    /**
     * Check sample input from sphere, reversed inputs, same output.
     */
    void test_eval_8() {
        const unsigned int v = collatz_eval(1000, 900);
        CPPUNIT_ASSERT(v == 174);
    }

    /**
     * Check that we get the correct results for a single input
     * (use the same start and end numbers for the range).
     * Use powers of two because they are easy to calculate.
     */
    void test_eval_9() {
        const unsigned int v = collatz_eval(4, 4);
        CPPUNIT_ASSERT(v == 3);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 8 has 4 bits.
     */
    void test_eval_10() {
        const unsigned int v = collatz_eval(8, 8);
        CPPUNIT_ASSERT(v == 4);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 16 has five bits.
     */
    void test_eval_11() {
        const unsigned int v = collatz_eval(16, 16);
        CPPUNIT_ASSERT(v == 5);
    }

    /**
     * Check that we get correct results for a single input,
     * a power of two. 1024 has 11 bits.
     */
    void test_eval_12() {
        const unsigned int v = collatz_eval(1024, 1024);
        CPPUNIT_ASSERT(v == 11);
    }

    /**
     * Take a power of two and apply odd rule backwards.
     * (x-1)/3 = n. Where x=1024.
     * Add one to the cycle length for this input.
     */
    void test_eval_13() {
        const unsigned int v = collatz_eval(5, 5);
        CPPUNIT_ASSERT(v == 6);
    }

    /**
     * Take a power of two and apply odd rule backwards.
     * (x-1)/3 = n. Where x=1024.
     * Add one to the cycle length for this input.
     */
    void test_eval_14() {
        const unsigned int v = collatz_eval(341, 341);
        CPPUNIT_ASSERT(v == 12);
    }

    /**
     * Confirm correct value for 9 for next tests.
     */
    void test_eval_15() {
        const unsigned int v = collatz_eval(9, 9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the end of the range,
     * the correct value is returned.
     */
    void test_eval_16() {
        const unsigned int v = collatz_eval(1, 9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the beginning of the range,
     * the correct value is returned.
     */
    void test_eval_17() {
        const unsigned int v = collatz_eval(9, 17);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the end of the range,
     * the correct value is returned, even when range is reversed.
     */
    void test_eval_18() {
        const unsigned int v = collatz_eval(9, 1);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Check that when the max value falls at the beginning of the range,
     * the correct value is returned, even when range is reversed.
     */
    void test_eval_19() {
        const unsigned int v = collatz_eval(17, 9);
        CPPUNIT_ASSERT(v == 20);
    }

    /**
     * Test for large inputs in range of the problem statement.
     */
    void test_eval_20() {
        const unsigned int v = collatz_eval(999999, 999999);
        CPPUNIT_ASSERT(v == 259);
    }

    /**
     * Test for inputs outside the range of the problem statement.
     */
    void test_eval_21() {
        const unsigned int v = collatz_eval(1000000, 1000000);
        CPPUNIT_ASSERT(v == 153);
    }

    /**
     * Test for very large inputs, outside the range of the problem statement.
     */
    void test_eval_22() {
        const unsigned int v = collatz_eval(1000000000, 1000000000);
        CPPUNIT_ASSERT(v == 101);
    }

    /**
     * Test for very large inputs. This will produce 32-bit integer overflow.
     * Solution is to use 64-bit long longs on the inside of the computation.
     */
    void test_eval_23() {
        const unsigned int v = collatz_eval(999999999, 999999999);
        CPPUNIT_ASSERT(v == 362);
    }

    /**
     * Test for very large inputs. This will produce 32-bit integer overflow.
     * Solution is to use 64-bit long longs on the inside of the computation.
     */
    void test_eval_24() {
        const unsigned int v = collatz_eval(1499999999, 1499999999);
        CPPUNIT_ASSERT(v == 360);
    }

    /**
     * Test the range where an integer overflow was detected.
     */
    void test_eval_25() {
        const unsigned int v = collatz_eval(999170, 999164);
        CPPUNIT_ASSERT(v == 321);
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
    // SUITE
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);

    // =========================
    // meta cache helper methods
    // =========================

    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_1);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_2);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_3);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_4);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_5);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_6);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_7);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_8);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_9);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_10);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_11);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_12);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_13);
    CPPUNIT_TEST(test_collatz_cache_inCacheBlock_14);

    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_1);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_2);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_3);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_4);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_5);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_6);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_7);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_8);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_9);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_10);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_11);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_12);
    CPPUNIT_TEST(test_collatz_cache_isBottomOfRange_13);

    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_1);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_2);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_3);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_4);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_5);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_6);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_7);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_8);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_9);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_10);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_11);
    CPPUNIT_TEST(test_collatz_cache_isTopOfRange_12);

    CPPUNIT_TEST(test_collatz_cache_lowIndex_1);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_2);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_3);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_4);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_5);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_6);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_7);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_8);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_9);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_10);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_11);
    CPPUNIT_TEST(test_collatz_cache_lowIndex_12);

    CPPUNIT_TEST(test_collatz_cache_highIndex_1);
    CPPUNIT_TEST(test_collatz_cache_highIndex_2);
    CPPUNIT_TEST(test_collatz_cache_highIndex_3);
    CPPUNIT_TEST(test_collatz_cache_highIndex_4);
    CPPUNIT_TEST(test_collatz_cache_highIndex_5);
    CPPUNIT_TEST(test_collatz_cache_highIndex_6);
    CPPUNIT_TEST(test_collatz_cache_highIndex_7);
    CPPUNIT_TEST(test_collatz_cache_highIndex_8);
    CPPUNIT_TEST(test_collatz_cache_highIndex_9);
    CPPUNIT_TEST(test_collatz_cache_highIndex_10);
    CPPUNIT_TEST(test_collatz_cache_highIndex_11);
    CPPUNIT_TEST(test_collatz_cache_highIndex_12);

    CPPUNIT_TEST(test_collatz_cache_max_500_1);
    CPPUNIT_TEST(test_collatz_cache_max_500_2);
    CPPUNIT_TEST(test_collatz_cache_max_500_3);
    CPPUNIT_TEST(test_collatz_cache_max_500_4);
    CPPUNIT_TEST(test_collatz_cache_max_500_5);
    CPPUNIT_TEST(test_collatz_cache_max_500_6);

    CPPUNIT_TEST(test_collatz_cache_500_usage_1);
    CPPUNIT_TEST(test_collatz_cache_500_usage_2);
    CPPUNIT_TEST(test_collatz_cache_500_usage_3);
    CPPUNIT_TEST(test_collatz_cache_500_usage_4);

    // =====================
    // core solution methods
    // =====================

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
    CPPUNIT_TEST(test_cycle_22);

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

    CPPUNIT_TEST(test_max_cycle_length_1);
    CPPUNIT_TEST(test_max_cycle_length_2);
    CPPUNIT_TEST(test_max_cycle_length_3);
    CPPUNIT_TEST(test_max_cycle_length_4);
    CPPUNIT_TEST(test_max_cycle_length_5);
    CPPUNIT_TEST(test_max_cycle_length_6);
    CPPUNIT_TEST(test_max_cycle_length_7);
    CPPUNIT_TEST(test_max_cycle_length_8);
    CPPUNIT_TEST(test_max_cycle_length_9);

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
    CPPUNIT_TEST(test_eval_24); */
    CPPUNIT_TEST(test_eval_25);

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
