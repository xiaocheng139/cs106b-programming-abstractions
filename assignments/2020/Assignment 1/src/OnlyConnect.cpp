/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "vector.h"
#include "strlib.h"
#include "Testing/OnlyConnectTests.h"
using namespace std;

string onlyConnectizeHelper(string phrase, const Vector<char>& consonant);

string onlyConnectize(string phrase) {
    Vector<char> consonant = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};
    return onlyConnectizeHelper(toLowerCase(phrase), consonant);

}


string onlyConnectizeHelper(string phrase, const Vector<char>& consonant) {
    if (phrase.length() == 0) {
        return "";
    } else {
        char c = phrase[0];
        string rest = phrase.substr(1);
        if (consonant.contains(c)) {
            return toUpperCase(charToString(c)) + onlyConnectizeHelper(rest, consonant);
        } else {
            return onlyConnectizeHelper(rest, consonant);
        }
    }
}




/* * * * * * Test Cases * * * * * */

ADD_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

ADD_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

ADD_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
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

ADD_TEST("Handles empty input.") {
    EXPECT_EQUAL(onlyConnectize(""), "");
}

ADD_TEST("Handles weird input.") {
    EXPECT_EQUAL(onlyConnectize("#$#%#$#asdRT$@#@#@#"), "SDRT");
}

ADD_TEST("Handles long input.") {
    EXPECT_EQUAL(onlyConnectize("asdaklsejqawbasdaliWWDSDassdasdakasdj*asdasd"), "SDKLSJQWBSDLWWDSDSSDSDKSDJSDSD");
}

