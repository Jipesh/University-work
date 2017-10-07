#ifndef MAXIMUM_GATES_H
#define MAXIMUM_GATES_H

#include <vector>

using std::vector;

int maximumGates(const vector<int> & arrives, const vector<int> & departs){
	
	int start_1, current_time, min_time, gatesUsed;

	int maximumGatesUsed = 0;
	
	if(arrives.size() >= 1){

		start_1 = 0;
		min_time = -1;
		gatesUsed = 0;

		for( int i = start_1 ; i < arrives.size() ; ++i){

			current_time = arrives[i];

			for(int time : departs){
				
				if( ( time < current_time ) ){

					if (min_time == -1 || (time > min_time )){
					
						min_time = time;
						--gatesUsed;
					}
					
				}
			}

			++gatesUsed;

			if(gatesUsed > maximumGatesUsed) maximumGatesUsed = gatesUsed;


		}

	}
	return maximumGatesUsed;
}



// Do not write any code below this line


#endif
