#ifndef YOUR_TEST_FOR_HOW_MANY_WAYS_TO_MAKE_H
#define YOUR_TEST_FOR_HOW_MANY_WAYS_TO_MAKE_H

#include "HowManyWaysToMake.h"


const int testHowManyWaysToMake() {

    const int result = howManyWaysToMake(3, {6,2});

   	if(result == 0) return 0;
	
	return 1;
}


// Do not write any code below this line

#endif
