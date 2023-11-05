/* 
queue.cpp
*/

#include "queue.h"

// The code for the Queue Constructor
Queue::Queue(int maxlen) {
    
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

//The Destructor for the Queue
Queue::~Queue() {
  delete[] contents;
}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
  
  head++;
  return contents[head-1];
}

//Insert a new Location at the end/back of our list   
void Queue::add_to_back(Location loc) {
	
  contents[tail] = loc;
  tail++;
}

//returns true if the queue is empty, returns false otherwise
bool Queue::is_empty() {
   return (head == tail);
}
