/* 
queue.h
*/

#ifndef QUEUE_H
#define QUEUE_H

// position [3][5] in an array would have row 3, col 5
struct Location {
   int row;
   int col;
};

// API for the Queue class which contains a series of Locations
class Queue {
public: 
   
   /*  the constructor 
    *  maxlen must be as large as the total number of
    *  Locations that will ever be entered into this Queue
    */
   Queue(int maxlen);
   
   // destructor
   ~Queue();
   
   // return and "remove" the oldest Location not already extracted
   Location remove_from_front();
   
   // insert a new Location at the end/back of our list   
   void add_to_back(Location loc);

   // is this Queue empty? (did we extract everything added?)
   bool is_empty();

   // member variables of a Queue
private:

   Location* contents; // pointer to dynamically-allocated array
   int tail; // index of next free item at the end
   int head;  // index of the first occupied location
            
};

#endif
