/*
 * CS106B Section Handout Test Harness: Section 1
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
#include "grid.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

int sumNumbers(string filename);
bool isNumber(string s);


/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */
int sumNumbers(string filename){
    ifstream is;
    int sum = 0;
    if (openFile(is,filename)) {
        Vector<string> lines;
        Vector<string> tokens;
        readEntireFile(is, lines);
        for (string &line: lines) {
            tokens = stringSplit(line, " ");
            for (string &token: tokens) {
                if (isNumber(token)) {
                    sum += stringToInteger(token);
                }
            }
        }
    }
    return sum;

}

bool isNumber(string s) {
    int i = 0;
    if (s[0] == '-') {
        i = 1;
    }

    while (i < s.size()) {
        if (!isdigit(s[i])) {
            return false;
        }
        i++;
    }
    return true;
}

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout"){
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 42);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

