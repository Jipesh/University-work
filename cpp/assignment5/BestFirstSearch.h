#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::unique_ptr;

#include <queue>
using std::priority_queue;

struct CompareSudoku{

    bool operator()(const unique_ptr<Searchable> & s1, const unique_ptr<Searchable> & s2) const{ return s1->heuristicValue() >= s2->heuristicValue(); }

};

class BestFirstSearch {

private:

    /** A queue of incomplete solutions: initially, the board we start with */
    priority_queue<unique_ptr<Searchable>, vector< unique_ptr<Searchable> >, CompareSudoku > Q;

protected:

    /// Make sure you increment this every time you 'expand' a node, by getting it successors and putting them on the queue        
    int nodes = 0;
    
    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        Q.push(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {

        // If there are still incomplete solutions on the queue
        while (!Q.empty()) {
            
            // If the solution on the front of the queue is a solution 
            if (Q.top()->isSolution()) {
                return Q.top().get(); // return the pointer 
            }
                  
             // we've now looked at one more node, increment our counter
            
            
            //current->write(cout);

            unique_ptr<Searchable> current (std::move(const_cast< unique_ptr<Searchable> &> (Q.top()) ));
            
            // Steal the pointer to the board at the front of the queue, by moving it into a unique_ptr here
            // After this, the pointer on the front of the queue is `nullptr`...
            Q.pop();

            // Get the successors...
            vector<unique_ptr<Searchable>> successors = current->successors();

           //Q.pop();

            if(!successors.empty()){

                ++nodes;
                
                for (auto & successor : successors) {
                    Q.push(std::move(successor));
                }
            }

        }
    
        return nullptr;
    }
};

// Do not edit below this line

#endif
