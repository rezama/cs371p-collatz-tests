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

int max_over_range[] = {179, 182, 217, 238, 215, 236, 262, 252, 247, 260, 268, 250, 263, 276, 271, 271, 266, 279, 261, 274, 256, 269, 269, 282, 264, 264, 308, 259, 259, 272, 272, 285, 267, 267, 311, 324, 249, 306, 244, 306, 288, 257, 288, 270, 270, 314, 283, 314, 296, 296, 278, 309, 340, 322, 260, 260, 322, 304, 273, 304, 335, 317, 286, 330, 299, 268, 268, 312, 312, 299, 312, 325, 263, 294, 325, 307, 307, 351, 338, 307, 320, 320, 320, 289, 320, 302, 302, 333, 333, 315, 315, 333, 315, 284, 315, 328, 297, 297, 284, 328, 341, 310, 310, 248, 310, 341, 354, 292, 279, 310, 292, 323, 323, 292, 305, 349, 305, 305, 336, 305, 318, 336, 318, 331, 287, 318, 331, 287, 331, 344, 331, 300, 331, 313, 300, 344, 313, 331, 313, 313, 344, 326, 375, 282, 326, 295, 357, 295, 326, 326, 370, 295, 308, 308, 352, 308, 383, 339, 321, 352, 370, 290, 339, 321, 334, 321, 352, 321, 321, 334, 290, 334, 303, 347, 334, 272, 334, 334, 347, 303, 365, 316, 334, 254, 316, 329, 347, 329, 316, 360, 329, 329, 347, 329, 342, 360, 298, 285, 329, 329, 342, 311, 342, 311, 311, 355, 373, 311, 311, 311, 342, 355, 355, 373, 293, 280, 386, 324, 324, 355, 324, 355, 324, 324, 324, 368, 368, 306, 355, 306, 443, 350, 337, 368, 381, 306, 337, 350, 306, 350, 368, 275, 319, 337, 275, 319, 332, 350, 288, 350, 332, 319, 319, 332, 363, 288, 332, 345, 301, 345, 332, 332, 301, 407, 332, 332, 314, 345, 270, 345, 407, 283, 314, 358, 332, 345, 314, 389, 345, 314, 345, 358, 314, 358, 358, 376, 314, 327, 389, 345, 327, 327, 340, 358, 296, 358, 327, 327, 371, 327, 371, 296, 340, 340, 340, 265, 309, 309, 371, 340, 371, 309, 384, 340, 278, 340, 353, 309, 353, 322, 371, 353, 309, 322, 384, 340, 247, 322, 291, 353, 322, 291, 353, 335, 322, 322, 366, 366, 335, 366, 304, 335, 353, 335, 304, 441, 348, 322, 335, 366, 304, 379, 335, 304, 348, 379, 348, 304, 379, 348, 410, 348, 361, 317, 317, 361, 348, 286, 317, 361, 392, 348, 317, 348, 330, 361, 423, 361, 330, 361, 379, 374, 361, 330, 330, 348, 330, 299, 330, 436, 361, 330, 299, 361, 405, 312, 330, 330, 374, 299, 374, 387, 268, 343, 343, 405, 361, 268, 312, 312, 449, 330, 343, 374, 374, 312, 387, 343, 343, 281, 343, 325, 356, 418, 356, 356, 356, 374, 294, 281, 312, 343, 387, 343, 356, 281, 325, 387, 400, 356, 325, 294, 356, 338, 325, 338, 325, 325, 369, 369, 387, 307, 294, 369, 338, 338, 356, 338, 307, 307, 307, 444, 369, 325, 338, 369, 369, 413, 382, 338, 307, 276, 338, 307, 382, 320, 307, 382, 351, 351, 413, 382, 351, 307, 320, 338, 382, 382, 382, 351, 320, 320, 426, 395, 351, 320, 320, 289, 351, 395, 364, 320, 426, 320, 364, 364, 382, 364, 377, 364, 333, 470, 333, 351, 364, 395, 302, 333, 439, 364, 333, 364, 333, 302, 364, 408, 408, 377, 377, 333, 346, 346, 377, 377, 346, 302, 333, 377, 346, 346, 408, 364, 346, 359, 315, 346, 452, 377, 333, 315, 346, 377, 315, 346, 421, 390, 346, 315, 315, 284, 359, 328, 359, 328, 421, 328, 359, 359, 359, 359, 377, 359, 372, 359, 328, 346, 390, 390, 346, 359, 266, 328, 328, 434, 372, 359, 359, 328, 315, 297, 359, 403, 328, 328, 328, 328, 372, 372, 341, 372, 372, 403, 297, 297, 372, 341, 328, 341, 403, 359, 341, 354, 310, 310, 310, 447, 372, 372, 310, 341, 372, 372, 310, 354, 385, 354, 509, 341, 279, 279, 341, 310, 385, 354, 310, 416, 310, 354, 354, 354, 416, 372, 416, 279, 279, 310, 323, 341, 323, 385, 341, 336, 354, 385, 323, 385, 429, 354, 398, 354, 323, 323, 292, 292, 367, 442, 323, 367, 323, 336, 323, 323, 367, 336, 367, 385, 336, 336, 380, 367, 336, 336, 305, 380, 336, 354, 398, 380, 292, 336, 336, 442, 323, 367, 367, 336, 336, 318, 367, 367, 367, 411, 380, 349, 504, 380, 305, 349, 349, 336, 380, 380, 411, 380, 305, 305, 380, 349, 336, 349, 411, 367, 411, 349, 362, 305, 349, 318, 362, 318, 380, 336, 380, 349, 349, 424, 318, 380, 424, 424, 393, 318, 349, 318, 318, 349, 287, 362, 318, 393, 362, 331, 318, 424, 318, 362, 362, 331, 362, 362, 380, 362, 331, 375, 362, 331, 331, 468, 331, 393, 349, 344, 393, 362, 331, 437, 331, 393, 437, 362, 344, 362, 331, 331, 313, 375, 300, 362, 406, 406, 375, 344, 437, 375, 331, 331, 468, 344, 300, 375, 375, 406, 388, 300, 331, 375, 344, 406, 331, 344, 406, 287, 362, 375, 313, 357, 344, 344, 450, 357, 450, 375, 344, 375, 326, 344, 313, 419, 313, 375, 344, 419, 388, 357, 344, 313, 344, 525, 344, 388, 357, 313, 388, 331, 357, 401, 313, 419, 313, 357, 357, 357, 326, 357, 419, 388, 375, 357, 370, 313, 357, 326, 326, 344, 326, 388, 326, 344, 357, 388, 326, 432, 326, 326, 388, 432, 370, 401, 326, 357, 326, 326, 313, 370, 295, 370, 445, 401, 295, 370, 339, 326, 295, 326, 370, 326, 370, 339, 370, 295, 401, 401, 383, 295, 383, 295, 445, 326, 370, 326, 476, 383, 401, 357, 370, 339, 339, 383, 339, 432, 339, 339, 445, 308, 370, 339, 370, 476, 383, 339, 370, 308, 370, 370, 414, 414, 383, 352, 445, 507, 383, 339, 339, 352, 383, 352, 383, 383, 383, 352, 414, 383, 414, 414, 383, 339, 352, 352, 321, 352, 414, 352, 383, 414, 352, 321, 365, 308, 321, 352, 458, 352, 321, 383, 383, 339, 383, 334, 383, 334, 427, 321, 383, 383, 352, 427, 352, 396, 321, 352, 321, 321, 352, 290, 365, 365, 365, 440, 396};

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
        std::istringstream r("10 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    10);
        CPPUNIT_ASSERT(j ==   1);}

    void test_read_3 () {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    void test_read_4 () {
        std::istringstream r("101 100\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    101);
        CPPUNIT_ASSERT(j ==   100);}

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
        const int v = collatz_eval(10, 1);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_6 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}

    void test_eval_7 () {
        const int v = collatz_eval(1000, 900);
        CPPUNIT_ASSERT(v == 174);}

    void test_eval_8 () {
        const int v = collatz_eval(210, 201);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_9 () {
        const int v = collatz_eval(200, 100);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_10 () {
        const int v = collatz_eval(10, 10);
        CPPUNIT_ASSERT(v == 7);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 10, 1, 20);
        CPPUNIT_ASSERT(w.str() == "10 1 20\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 101, 100, 26);
        CPPUNIT_ASSERT(w.str() == "101 100 26\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2 () {
        std::istringstream r("1 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_solve_3 () {
        std::istringstream r("1 10\n10 1\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n10 1 20\n");}

    void test_solve_4 () {
        std::istringstream r("");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}

    // ---------
    // findsteps
    // ---------

    void test_findsteps_1 () {
	CPPUNIT_ASSERT(collatz_findsteps(1) == 1);}

    void test_findsteps_2 () {
	CPPUNIT_ASSERT(collatz_findsteps(2) == 2);}

    void test_findsteps_3 () {
	CPPUNIT_ASSERT(collatz_findsteps(5) == 6);}

    void test_findsteps_4 () {
	CPPUNIT_ASSERT(collatz_findsteps(3) == 8);}


    // -----
    // eval2
    // -----

    void test_eval2_1 () {
	int v = collatz_eval2(1, 10, max_over_range);
	CPPUNIT_ASSERT(v == 20);}

    void test_eval2_2 () {
	int v = collatz_eval2(100, 200, max_over_range);
	CPPUNIT_ASSERT(v == 125);}

    void test_eval2_3 () {
	int v = collatz_eval2(201, 210, max_over_range);
	CPPUNIT_ASSERT(v == 89);}

    void test_eval2_4 () {
	int v = collatz_eval2(900, 1000, max_over_range);
	CPPUNIT_ASSERT(v == 174);}

    void test_eval2_5 () {
	int v = collatz_eval2(10, 1, max_over_range);
	CPPUNIT_ASSERT(v == 20);}

    void test_eval2_6 () {
	int v = collatz_eval2(1, 1, max_over_range);
	CPPUNIT_ASSERT(v == 1);}

    void test_eval2_7 () {
	int v = collatz_eval2(1000, 900, max_over_range);
	CPPUNIT_ASSERT(v == 174);}

    void test_eval2_8 () {
	int v = collatz_eval2(210, 201, max_over_range);
	CPPUNIT_ASSERT(v == 89);}

    void test_eval2_9 () {
	int v = collatz_eval2(200, 100, max_over_range);
	CPPUNIT_ASSERT(v == 125);}

    void test_eval2_10 () {
	int v = collatz_eval2(10, 10, max_over_range);
	CPPUNIT_ASSERT(v == 7);}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
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
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_findsteps_1);
    CPPUNIT_TEST(test_findsteps_2);
    CPPUNIT_TEST(test_findsteps_3);
    CPPUNIT_TEST(test_findsteps_4);
    CPPUNIT_TEST(test_eval2_1);
    CPPUNIT_TEST(test_eval2_2);
    CPPUNIT_TEST(test_eval2_3);
    CPPUNIT_TEST(test_eval2_4);
    CPPUNIT_TEST(test_eval2_5);
    CPPUNIT_TEST(test_eval2_6);
    CPPUNIT_TEST(test_eval2_7);
    CPPUNIT_TEST(test_eval2_8);
    CPPUNIT_TEST(test_eval2_9);
    CPPUNIT_TEST(test_eval2_10);
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
