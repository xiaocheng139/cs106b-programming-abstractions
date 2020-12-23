/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "error.h"
using namespace std;

/*
 * Sum of Squares (Code Writing)
 * --------------------------------------------------------
 * Write a recursive function that takes an integer n and returns
 * the sum of squares from 1 to n.
 */

int sumOfSquares(int n){
    if (n < 0) {
        error("Negative input is not allowed");
    } else if (n == 0) {
        return 0;
    } else {
        return sumOfSquares(n - 1) + n * n;
    }
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Example from handout.") {
    EXPECT_EQUAL(sumOfSquares(3), 14);
}

PROVIDED_TEST("Provided Test: Check error on negative input."){
    EXPECT_ERROR(sumOfSquares(-5));
}
