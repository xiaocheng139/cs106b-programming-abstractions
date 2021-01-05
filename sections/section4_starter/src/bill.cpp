/*
 * CS106B Section Handout Test Harness: Section 3
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
#include "testing/TestDriver.h"
#include "error.h"
#include "map.h"
#include "set.h"
using namespace std;

/*
 * Splitting the Bill (Code Writing)
 * --------------------------------------------------------
 * Your task is to write a function that takes as input a
 * total amount of money to pay (in dollars) and a set of
 * all the people who ordered something, then lists off every
 * possible way you could split the bill, assuming everyone
 * pays a whole number of dollars.
 */
void listPossiblePaymentsHelper(int total, Set<string>& people, Map<string, int>& options);
void printOption(Map<string, int>& options);

void listPossiblePayments(int total, Set<string>& people) {
    if(total < 0) {
        error("Negative total amount is not allowed");
    }
    Map<string, int> option;
    listPossiblePaymentsHelper(total, people, option);
}

void listPossiblePaymentsHelper(int remaining, Set<string>& people, Map<string, int>& options) {
    if (people.isEmpty()) {
        if (remaining == 0) {
            printOption(options);
        }
    } else {
        string person = people.first();
        people -= person;
        for (int i = 0; i <= remaining; i++) {
            // choose
            options[person] = i;
            // Explore
            listPossiblePaymentsHelper(remaining - i, people, options);
            // Unchoose
            options.remove(person);
        }
        people.add(person);
    }
}

void printOption(Map<string, int>& options) {
    for (string key: options.keys()) {
        cout << key << ": $" << options[key] << " ";
    }
    cout << endl;
}

/* * * * * Provided Tests Below This Point * * * * */

// This test macro allows you to see the text output from a program
// that print results to the screen

MANUAL_TEST("Provided Test: Examples from handout.") {
    Set<string> people = {"A", "B", "C"};
    listPossiblePayments(4, people);
}

