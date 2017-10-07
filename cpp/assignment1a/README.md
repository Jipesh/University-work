# Basic building blocks of C++

For this assignment you will code using some of the basic building blocks of C++: vectors, functions, and classes.  

## The PEP vector class -- technical note

To ensure you are using `vector` correctly, for this work you will be using a version specially adapted for this assignment.  It is used by all the skeleton code provided, and involves writing:

`#include "vector.h"`  
`using pep::vector;`  

... instead of the usual:

`#include <vector>`  
`using std::vector;`  

This should not affect your solution, but note that outwith this assignment you should use the regular std vector implementation where appropriate.


# Buy low, sell high

The price of a given commodity, can be represented by a vector of prices.  For instance:

`vector<int> prices {28, 18, 20, 26, 24};`  

To maximise profit, we would want to buy low and sell high -- in this case, buy at time 1 (when the cost is 18), sell at time 3 (when the cost is 26).

In `Trade.h` implement a function `bestBuySellTime` that takes a vector of prices and returns a `Trade' object with the buy and sell time that maximises profit.  This function does not live inside any class -- it is to be defined as a global function.  *(Note that as the price vector may be large, avoid copying it within your implementation.)*

To perform some basic testing on your code, once you have implemented the function (or at least declared it) `TestTrade.cpp` defines a simple test harness.  To compile this, run:

`g++ -std=c++11 -o TestTrade TestTrade.cpp`  

If it compiles, you can then run:

`./TestTrade`  



# A circular buffer

## What is a circular buffer?

Circular buffers use a fixed-size block of memory to temporary buffer data.  For instance, keypresses on the keyboard put characters in the buffer; and when the operating system is ready to process them, it reads characters from the buffer.

The buffer starts as being empty.  For instance, if we had a buffer of size 5 it would look like:

`[   |   |   |   |   ]`  


If we then write 'a' and 'b' into the buffer it would look like:

`[ a | b |   |   |   ]`  


...and then removing the next item in the buffer would give:

`[   | b |   |   |   ]`  


If we continue to write elements into the buffer, e.g. 'c', 'd', 'e', 'f' then when the end is reached, elements start being written into any spare space at the start:

`[ f | b | c | d | e ]`  


At this point the buffer is full.  We can't write any more data to it -- in the case of keyboard buffers, the computer would start beeping.  We can though remove an element, which always removes the *oldest*, i.e. the letter 'b', which would leave the buffer:

`[ f |   | c | d | e ]`  

We could then remove the next element (c), or as there is now a space again, write another character into the buffer.

## Implement a circular buffer

In the file`CircularBuffer.h` complete the definition of the CircularBuffer class.  Your implementation should be based on a vector of characters.

The constructor of the class should take the capacity of the buffer as an argument.  There should be no default constructor.

It needs to have the functions:  
1. `count()` which returns how many things are in the buffer  
2. `full()` which returns true *iff* the buffer is full  
3. `add()` which takes a character and adds it to the buffer (you can assume the buffer is not full)  
4. `remove()` which removes and returns the next character from the buffer (you can assume the buffer is not empty)  
 
Once you have provided the constructor and functions, you can test your code using `TestCircularBuffer.cpp`.  To compile this, run:

`g++ -std=c++11 -o TestCircularBuffer TestCircularBuffer.cpp`  

If it compiles, you can then run:

`./TestCircularBuffer`  

As well as being confident your solution behaves correctly, you should ensure that any functions that should be `const` (because they do not change the buffer) are marked as const; and ensure you use the initialisation syntax with your constructor to appropriately initialise the vector to be the right size.


