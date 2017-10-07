#include "HowManyWaysToMake.h"
#include "YourTestForHowManyWaysToMake.h"

// NB Do not save any work in this file
//
// Only code in HowManyWaysToMake.h and YourTestForHowManyWaysToMake.h will be marked


#include <iostream>
using std::cout;
using std::endl;

int testOne() {
    const int possibilities = howManyWaysToMake(9, {1});
    
    if (possibilities == 1) {
        cout << "1) Pass: code correctly returns that there is 1 way to make 9 out of {1}\n";     
        return 0;
    } else {
        cout << "1) Fail: code returns that there are " << possibilities << " ways to make 9 out of {1} -- but the answer is 1\n";     
        return 1;
    }
}

int testTwo() {
    const int possibilities = howManyWaysToMake(9, {6,2,1});
    
    if (possibilities == 7) {
        cout << "2) Pass: code correctly returns that there are 7 ways to make 9 out of {6,2,1}\n";     
        return 0;
    } else {
        cout << "2) Fail: code returns that there are " << possibilities << " ways to make 9 out of {6,2,1} -- but the answer is 7\n";     
        return 1;
    }
}

int main() {
    int retval = 0;
    
    retval += testOne();
    retval += testTwo();    
    {
        cout << "Running your test case\n";
        int yourReturnValue = testHowManyWaysToMake();
        if (yourReturnValue == 0) {
            cout << "Your test case returned: Pass\n";
        } else {
            cout << "Your test case returned: Fail\n";
        }
        retval += yourReturnValue;
    }
    
    return retval;
}
