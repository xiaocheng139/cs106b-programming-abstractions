/* File: PlayingFair.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "PlayingFair.h"
#include "Testing/PlayingFairTests.h"
#include "error.h"
using namespace std;

string reverse(string s);

string aSequenceOfOrder(int n) {
    if (n == 0) {
        return "A";
    } else if (n < 0) {
        error("Negative number is not allowed!");
    } else {
        return aSequenceOfOrder(n - 1) + reverse(aSequenceOfOrder(n - 1));
    }
}

string bSequenceOfOrder(int n) {
    if (n == 0) {
        return "B";
    } else if (n < 0) {
        error("Negative number is not allowed!");
    } else {
        return bSequenceOfOrder(n - 1) + reverse(bSequenceOfOrder(n - 1));
    }
}

string reverse(string s) {
    string newStr;
    for (char c : s) {
        if (c == 'A') {
            newStr += "B";
        } else {
            newStr += "A";
        }
    }
    return newStr;
}




/* * * * * * Tests Below This Point * * * * * */

ADD_TEST("Sequences of order 3 are correct.") {
    /* Some very basic checks. */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

ADD_TEST("Only characters should be As and Bs.") {
    for (int i = 0; i < 10; i++) {
        for (char ch: aSequenceOfOrder(i)) {
            EXPECT(ch == 'A' || ch == 'B');
        }
    }
}

ADD_TEST("A-sequence of positive order should have equal As and Bs.") {
    /* Exclude the sequence of order 0, which is just a single character. */
    for (int i = 1; i < 10; i++) {
        int as = 0;
        int bs = 0;
        for (char ch: aSequenceOfOrder(i)) {
            if (ch == 'A') as++;
            else bs++;
        }

        EXPECT_EQUAL(as, bs);
    }
}

ADD_TEST("Triggers error on negative inputs.") {
    /* The EXPECT_ERROR macro expects the given expression to call error(). Remember that
     * you need to guard against invalid inputs.
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */

ADD_TEST("Sequences of order 0.") {
    /* Check order 0*/
    EXPECT_EQUAL(aSequenceOfOrder(0), "A");
    EXPECT_EQUAL(bSequenceOfOrder(0), "B");
}
