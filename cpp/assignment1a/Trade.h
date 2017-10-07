#ifndef TRADE_H
#define TRADE_H

#include "vector.h"
using pep::vector;


class Trade {
protected:
    int buyTime;
    int sellTime;

public:
    Trade(const int buyTimeIn, const int sellTimeIn)
        : buyTime(buyTimeIn), sellTime(sellTimeIn) {
    }

    int getBuyTime() const {
        return buyTime;
    }

    int getSellTime() const {
        return sellTime;
    }

};

Trade bestBuySellTime(vector<int> v){
    int buyIndex = -1;
    int sellIndex = -1;
    int dif1 = 0, dif2 = 0, dif3 = 0;
        
    if(v.size() == 1){
        buyIndex = 0;
        sellIndex = 0;
    }else {

        for(int i = v.size() - 2 ; i >= 0 ; i-- ){

            int temp1 = v[i];
            int temp2 = v[i+1];
                
                if( buyIndex == -1 ){
                    buyIndex = i;
                }
                if (sellIndex == -1){
                    sellIndex = (i+1);
                }

                if (temp2 >= temp1){

                	dif1 = v[sellIndex] - v[buyIndex];

                    dif2 = temp2 - temp1;

            		dif3 = v[sellIndex] - temp1;
            			
            		if( dif2 >= dif3 && dif2 >= dif1 ){
            			buyIndex = i;
            			sellIndex = (i+1);
            		}else if( dif3 >= dif2 && dif3 >= dif1 ){
            			buyIndex = i;

            		}else{
            			
                        if( temp2 >= v[sellIndex] ){
                            buyIndex = i;
            			    sellIndex = (i+1);
                        }
                    }

                }

        }

	   if( v[0] - v[0] >= dif1 ){
	       buyIndex = 0;
		  sellIndex = 0;	
        }
    }

    Trade t ( buyIndex, sellIndex );
    return t;

} 






// Don't write any code below this line

#endif