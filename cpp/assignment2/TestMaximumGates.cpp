#include "MaximumGates.h"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main() {
    int retval = 0;
    
    {
        vector<int> arrives{360, 400, 700};
        vector<int> departs{900, 515, 780};
        
        int maxGates = maximumGates(arrives,departs);
        
        if (maxGates == 2) {
            cout << "0) Pass: 2 gates needed for first test scenario described in README.md\n";
        } else {
            cout << "0) Fail: 2 gates should be needed for first test scenario described in README.md, but maximumGates returned " << maxGates << endl;
            ++retval;
        }
    }
    
    {
        vector<int> arrives{360, 400, 700};
        vector<int> departs{900, 720, 780};
        
        int maxGates = maximumGates(arrives,departs);
        
        if (maxGates == 3) {
            cout << "1) Pass: 3 gates needed for the second test scenario described in README.md\n";
        } else {
            cout << "1) Fail: 3 gates should be needed for second test scenario described in README.md, but maximumGates returned " << maxGates << endl;
            ++retval;
        }
    }
    
    return retval;
}
