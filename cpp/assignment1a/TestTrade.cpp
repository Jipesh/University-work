#include "Trade.h"

#include "vector.h"
using pep::vector;

#include <iostream>
using std::cout;
using std::endl;

int main() {
    vector<int> prices{28, 18, 20, 26, 24};
    
    
    // NB this next line won't compile until you've implemented bestBuySellTime
    Trade trade = bestBuySellTime(prices);
    
    int retval = 0;
    
    if (trade.getBuyTime() == 1) {
        cout << "Buy time of 1 is correct\n";
    } else {
        cout << "Buy time of " << trade.getBuyTime() << " is incorrect\n";
        ++retval;
    } 
    
    
    if (trade.getSellTime() == 3) {
        cout << "Sell time of 3 is correct\n";
    } else {
        cout << "Sell time of " << trade.getSellTime() << " is incorrect\n";
        ++retval;
    }             
    
    return retval;
}
