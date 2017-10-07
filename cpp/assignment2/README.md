
# 1) How many ways to make money

## 1a) Implementing `howManyWaysToMake`

In the file HowManyWaysToMake.h, write a function `howManyWaysToMake` that, given:
 
- an integer amount of money
- a vector of integer coin sizes available (with no duplicates)

... returns how many ways there are to make that amount of money, using those coins.

For instance, for an amount of money 9 and coin sizes `{6,2,1}` your function would return 7 -- the following sums all add up to 9:

`1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1`  
`2 + 1 + 1 + 1 + 1 + 1 + 1 + 1`  
`2 + 2 + 1 + 1 + 1 + 1 + 1`  
`2 + 2 + 2 + 1 + 1 + 1`  
`2 + 2 + 2 + 2 + 1`  
`6 + 1 + 1 + 1`  
`6 + 2 + 1`  

Note:

- You don't have to return the different ways of making the amount of money, just how many there are.
- Don't count equivalent combinations more than once.  `6 + 2 + 1` is the same as `6 + 1 + 2` is the same as `1 + 2 + 6` etc.


To perform tests on your code, compile and run `TestCountPossiblities.cpp`.

## 1b) Writing a test case for `howManyWaysToMake`

In the file `YourTestForHowManyWaysToMake.h`, write a test case in the function `testHowManyWaysToMake()`.  This should call the function `howManyWaysToMake` with some inputs, and check it gives the correct output.  If the test passes, the function should return 0; otherwise, it should return 1.

# 2) Calculating how many airport gates are needed

The arrival and departure times of planes at an airport can be defined by a pair of vectors:

- A vector `arrives` containing arrival times
- A vector `departs` containing departure times


We can represent the times as a whole number of minutes after midnight.  For instance, the time 7:17am would be recorded as `(7 * 60) + 17 = 437`.

Plane `i` then arrives at time `arrives[i]` and departs at time `departs[i]`.  The number of gates an airport needs so that no plane needs to wait for a gate is equal to the maximum number of gates needed that day.

In the file `MaximumGates.h` implement a function `maximumGates` that takes:

- The arrives vector
- The departs vector

...and returns the maximum number of gates needed at the airport.  For instance, given the inputs: 

`arrives = {360, 400, 700}`  
`departs = {900, 515, 780}`  

...it should return 2.  Going through the day in chronological order:

* t=360: Plane 0 arrives: 1 gate now in use
* t=400: Plane 1 arrives: *2* gates now in use
* t=515: Plane 1 departs: 1 gate now in use
* t=700: Plane 2 arrives: *2* gates now in use
* t=780: Plane 2 departs: 1 gate now in use
* t=900: Plane 0 departs: 0 gates now in use


Conversely, if plane 2 had arrived *before* plane 1 had departed, e.g:

`arrives = {360, 400, 700}`  
`departs = {900, 720, 780}`  

...the maximum number of gates to return would be 3.

Notes:

- You can assume `arrives` is sorted into ascending order
- One plane will never arrive at the time another departs


# 3) Using stacks

In `Stack.h`, implement a class `Stack` that is a Stack of `double`s.  You should implement this using the provided vector class: Stack.h contains the necessary `include` and `using` lines for this.

Your `Stack` class needs to provide three functions:

- `empty()` that returns true if the stack is empty
- `pop()` that removes and returns the top element off the stack
- `push()` that takes a double and pushes it onto the stack

Once you have written a Stack class, after it -- but still in `Stack.h` -- implement a function `evaluate` that takes a string containing a mathematical expression written in [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation), and returns the result of evaluating the expression.

In reverse polish notation (RPN), operators are written *after* rather than between what they act upon.  For instance:

`3.0 4.0 +`

...is the same as the usual (infix) notation `(3.0 + 4.0)`.  Or:

`3.0 4.0 + 2.0 *`

...is the same as `(3.0 + 4.0) * 2`.  The advantage of RPN is that there is no need to worry about brackets and order of precedence.

To implement the `evaluate` function, use your Stack class.  RPN expressions can be evaluated by splitting the input string by spaces into tokens, and working through it one token at a time:
 
 * If the token is a `+`, pop two numbers a and b off the stack, and push (b + a) onto the stack
 * If the token is a `-`, pop two numbers a and b off the stack, and push (b + a) onto the stack
 * If the token is a `*`, pop two numbers a and b off the stack, and push (b * a) onto the stack
 * If the token is a `/`, pop two numbers a and b off the stack, and push (b / a) onto the stack
 * Otherwise, the token is a number: push it onto the stack
 
 After going through all the tokens, the answer is then on the top of the stack: return it.
 
 To test your code, compile and run `TestStack.cpp`.  This will to evaluate three expressions, and check they give the right answer.
 
 
 
