#include "YouGotHufflepuff.h"
#include "Testing/YouGotHufflepuffTests.h"
#include "set.h"
using namespace std;

HashMap<char, double> normaliseScore(HashMap<char, int> scores);
double getSimilarity(HashMap<char, double> scores1, HashMap<char, double> scores2);

void administerQuiz(const HashSet<Question>& questions,
                    int numQuestions,
                    const HashSet<Person>& people) {
    HashSet<Question> asked;
    HashMap<char, int> scores;

    int i = 0;
    while (i < numQuestions) {
        Question randomQuestion = randomElement(questions);

        if (!asked.contains(randomQuestion)) {
            int absScore = askPersonalityQuestion(randomQuestion);
            HashMap<char, int> factors = randomQuestion.factors;

            for (char key: factors.keys()) {
                scores[key] += factors[key] * absScore;
            }
            i++;
        }
    }
    displayScores(scores);

    // Normalise
    HashMap<char, double> nomalisedScore = normaliseScore(scores);
    double highestSimilarity = 0;
    Person matchPerson;

    for (Person per: people) {
        double similarity = getSimilarity(nomalisedScore, normaliseScore(per.scores));
        if ( similarity > highestSimilarity) {
            highestSimilarity = similarity;
            matchPerson = per;
        }
    }
    string message = "You Got " + matchPerson.name + "! (Similarity: " + to_string(highestSimilarity) + " )";
    displayMessage(message);
}

HashMap<char, double> normaliseScore(HashMap<char, int> scores) {
    double baseVal = 0;
    bool valid = false;
    HashMap<char, double> normalisedScore;
    for (char key: scores.keys()) {
        if (scores[key] > 0) {
            valid = true;
            baseVal += (scores[key] * scores[key]);
        }
    }
    if (!valid) {
        displayMessage("You don’t have enough information to make a determination of who they’re most similar to.");
    }
    for (char key: scores.keys()) {
        normalisedScore[key] = scores[key] / sqrt(baseVal);
    }
    return normalisedScore;
}

double getSimilarity(HashMap<char, double> scores1, HashMap<char, double> scores2) {
    double similarity = 0;
    for (char key: scores1.keys()) {
        similarity += scores1[key] * scores2[key];
    }
    return similarity;
}


/* * * * *   Test Cases Below This Point   * * * * */

/* Because administerQuiz is a function that requires interaction with the user,
 * you won't be able to directly test that administerQuiz returns the correct
 * values. Similarly, you can't call the askPersonalityQuestion, displayScores,
 * or displayMessage functions, as those are wired into the demo and don't
 * work in testing.
 *
 * However, you are welcome to add test cases to test any helper functions you
 * write! To do so, use the ADD_TEST macro to define tests, just as you did in
 * Assignment 1 and for Rising Tides.
 *
 * You aren't required to include test cases in this part of the assignment,
 * though we definitely would encourage you to do so! This is a multistep
 * assignment that's going to require each individual function to work
 * correctly, and adding tests for the functions you write is a great way to
 * find and fix bugs early on.
 */

