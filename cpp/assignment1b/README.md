# Items to collect on a map

For this piece of coursework, you will write code to store and work with a map of items to collect, each of which is available for just 15 minutes starting at a certain number of seconds past the hour.  You then will write an algorithm that finds a route that (attempts to) collect them all.

# Part (i): The Item class

Items are described by four properties:

- Their latitude (a number in degrees, e.g. 51.75087595155126)
- Their longitude (a number in degrees, e.g. -0.33483137537806396)
- A string ID
- The time at which they become available: an integral number of seconds past the hour

In Item.h, make a class Item that contains these as private member variables.

Give the class an appropriate constructor that initialises these four variables to the arguments passed to the constructor (passed in the above order).

Implement an `operator<<` function for printing out Item objects, so that the following code will work:

`Item strand(51.5115, -0.116, "StrandCampus", 600);`  
`cout << strand << endl;`  

...and will produce output of the form:

`{latitude, longitude, "ID", time}`

...in this case:

`{51.5115, -0.116, "StrandCampus", 600}`  


Once you have done this, create a class function `distanceTo` that will take another Item, and return the distance to it in metres.  To compute this distance, use the [Haversine Formula](http://andrew.hedges.name/experiments/haversine/), which can be implemented using the following pseudo-code:

`dlon = lon2 - lon1`  
`dlat = lat2 - lat1`  
`a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2)`  
`c = 2 * atan2( sqrt(a), sqrt(1-a) )`  
`distance = R * c (where R is the radius of the Earth)`  

Note that this pseudo-code assumes the latitude and longitude are in *radians*, whereas your class stores them in degrees, so you will need to convert them to radians first.  `cos`, `sin` and the other trignometric functions can be obtained by putting `#include <cmath>` at the top of Item.h.  You should assume `R`, the radius of the earth in metres, is 6373000.

To test your code, you can use ItemTest.cpp.  To compile to an executable `ItemTest`, run:

`g++ -std=c++11 -o ItemTest ItemTest.cpp`  

Note that this will only work once you have implemented the constructor and functions discussed above.

# Part (ii): A Map of Items

In, Item.h, make another class `MapOfItems`.  You need to define this *after the Item* class.  It needs to have:

- a private member variable that stores a vector of `Item's
- a public function 'addItem' for adding an item to the end of this vector
- a public function 'size()' for returning the size of this vector

Note that where relevant, these should use `const`.


# Part (iii): Taking a tour of the Map

For this part of the assignment, you will implement a greedy algorithm that finds an order in which to visit the Items, allowing for a walking speed between them, and during the times at which they are available (i.e. from a given number of seconds past the hour, until 15 minutes after).

It should be in a class function called `getTour`, implemented within the MapOfItems class.  It should take a walking speed as an argument.  The tour should take no longer than 3600 seconds; that is, the last item you visit, must be visited before 3600.  It should return the tour as a `vector` of `Item`s.

The algorithm specification is as follows:

- The tour must finish before time 3600.
- The tour must start at the Item that is available first, at the time it becomes available.  For instance, if there are five items on the map, available from times 3,10,14,16,18, the item at time 3 would be visited first, at time 3.  (That is, the current time is 3.)
- Then, repeatedly:
  - For each Item *I* that hasn't been visited yet, 
    - Calculate the time that it would take to walk from the previous Item visited, to *I* (using the distance between them, and the walking speed).  This time, plus the current time, is the time that *I* would be visited -- if we went there next.  This time is denoted *visit(I)*.
    - If *visit(I)* is too late (more than fifteen minutes after the item appears), we can't visit that Item
    - If it's too early (before the time at which the item appears), we would need to wait at *I* until it appeared.  This is okay. but we would set *visit(I)* to the time at which *I* appears.
  - The next item to visit is then the one with the smallest *visit(I)*: add this to the tour, and set the current time to *visit(I)*..
  - Or, if we are too late for all the remaining Items, the tour has finished.  (Yes, it might not be able to visit all the items.)
- The function then returns the tour


To test your implementation, use MapOfItemsTest.cpp.  To compile to an executable `MapOfItemsTest`:

`g++ -std=c++11 -o MapOfItemsTest MapOfItemsTest.cpp`  

