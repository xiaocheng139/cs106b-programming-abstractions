#include <iostream>
#include "console.h"
#include "vector.h"
#include "testing/SimpleTest.h"

using namespace std;
void changeNums(Vector<int>& nums);

int main() 
{
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    return 0;
}
