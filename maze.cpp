/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for BFS_search, 
int BFS_search(char**, int, int);

// main function to read the maze and print result
int main(int argc, char* argv[]) {
    
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
   mymaze = read_maze(argv[1], &rows, &cols); 
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   
   result = BFS_search(mymaze, rows, cols); 

   // examine value returned by BFS_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 2) {
     cout << "Error, input format incorrect" << endl; 
     return 1; 
   }
   else if (result == 0) { // no path found
      cout << "No path could be found!" << endl;
   }
   else { // maze has invalid format
      cout << "Invalid maze." << endl;
   }

   // de-allocates all memory that read_maze allocated
   for (int i = 0; i < rows; i++) {
     delete[] mymaze[i]; 
   }
   delete[] mymaze;
   
   return 0;
}

//values returned by BFS_search function
enum Result {
    PATH_FOUND = 1,
    NO_PATH = 0,
    INVALID_MAZE = -1
};


//This is where the BFS algorithm is used to find the quickest path
//If path is found it will be filled in with '*' characters
int BFS_search(char** maze, int rows, int cols) 
{
  Location start; 
  Location end; 
  int numS = 0; 
  int numF; 
  bool pathFound = false; 
  
  //check to see if the maze is valid 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      if (!(maze[i][j] == '#' || maze[i][j] == '.') || 
            maze[i][j] == 'S' || maze[i][j] == 'F')) {
        //means that the maze is not valid, because it contains a different characters
        cout << "Error, input format incorrect" << endl; 
        return INVALID_MAZE; 
      }     
    }
  }
  
  //begin by finding the starting and finishing location 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        
      if (maze[i][j] == 'S') {
        start.row = i; 
        start.col = j; 
        numS = 1; 
      }
      else if (maze[i][j] == 'F') {
        end.row = i; 
        end.col = j; 
        numF = 1; 
      }
    }
  }
  
  //return INVALID_MAZE (-1) if necessary
  if (!(countS == 1 && countF == 1)) {
    cout << "Maze is not valid" << endl; 
    return INVALID_MAZE; 
  }
  
  Location predecessorInitial; 
  predecessorInitial.row = -1; 
  predecessorInitial.col = -1; 
  
  //set up queue 
  Queue queue(rows*cols); 
  
  //create predecessor 
  Location** predecessor = new Location*[rows];
  for (int i = 0; i < rows; i++) {
    predecessor[i] = new Location[cols]; 
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      predecessor[i][j] = predecessorInitial; 
    }
  }
  
  //create visited array 
  int** visited = new int*[rows]; 
  for (int i = 0; i < rows; i++) {
    visited[i] = new int[cols]; 
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      visited[i][j] = 0; 
    }
  }
  
  //put the location into the queue
  queue.add_to_back(start); 
  //loop 
  while (!(queue.is_empty())) {
    
    //extract first location 
    Location curr = queue.remove_from_front();  
    
    //visit each neighbor 
    //North 
    Location north; 
    north.row = curr.row - 1; 
    north.col = curr.col; 
    //check to see if it in the array 
    if ((north.col >= 0 && north.col < cols) && 
             (north.row >= 0 && north.row < rows)) {
       
      //check if we have found the finish 
      if (maze[north.row][north.col] == 'F') {
        //backtrace
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col]; 
        }
        pathFound = true; 
        break;   
      }
      
      //check to see if it is an open space
      else if (maze[north.row][north.col] == '.' 
               && visited[north.row][north.col] ==0) {
        //add it to the back of the queue
        queue.add_to_back(north);
        //mark it as visited 
        visited[north.row][north.col] = 1; 
        //record predecessor 
        predecessor[north.row][north.col] = curr; 
      }
    }
        
    //West
    Location west; 
    west.row = curr.row; 
    west.col = curr.col - 1; 
    //check to see if it in the array 
    if ((west.col >= 0 && west.col < cols) && 
             (west.row >= 0 && west.row < rows)) {  
      
      //check if we have found the finish 
      if (maze[west.row][west.col] == 'F') {
        //now backtrack
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col];  
        }
        pathFound = true; 
        break; 
      }
          
      //check to see if it is an open space
      else if (maze[west.row][west.col] == '.' && 
               visited[west.row][west.col] == 0) {  
        //add it to the back of the queue
        queue.add_to_back(west);
        //mark it as visited 
        visited[west.row][west.col] = 1; 
        //record predecessor 
        predecessor[west.row][west.col] = curr; 
      }
    }
         
    //South
    Location south; 
    south.row = curr.row + 1; 
    south.col = curr.col; 
     //check to see if it in the array 
    if ((south.col >= 0 && south.col < cols) && 
             (south.row >= 0 && south.row < rows)) {
           
      //check if we have found the finish 
      if (maze[south.row][south.col] == 'F') {
        //if f, then we can backtrace until we find S
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col];  
        }
        pathFound = true; 
        break;   
      }
     
       //check to see if it is an open space
      else if (maze[south.row][south.col] =='.' 
               && visited[south.row][south.col] == 0) {     
        //add it to the back of the queue
        queue.add_to_back(south);
        //mark it as visited 
        visited[south.row][south.col] = 1; 
        //record predecessor 
        predecessor[south.row][south.col] = curr; 
      }
    }
       
    //East
    Location east; 
    east.row = curr.row; 
    east.col = curr.col + 1;     
     //check to see if it in the array 
    if ((east.col >= 0 && east.col < cols) && 
             (east.row >= 0 && east.row < rows)) {
      
      //check if we have found the finish 
      if (maze[east.row][east.col] == 'F') {
        //backtrace
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col]; 
         
        }
        pathFound = true; 
        break;   
      }
      //check to see if it is an open space
      else if (maze[east.row][east.col]=='.' 
               && visited[east.row][east.col] == 0) {
        //add it to the back of the queue
        queue.add_to_back(east);
        //mark it as visited 
        visited[east.row][east.col] = 1; 
        //record predecessor 
        predecessor[east.row][east.col] = curr; 
      }
    }
  }
  
  //Delete all memory 
  for (int i = 0; i < rows; i++) {
    delete[] predecessor[i]; 
    delete[] visited[i]; 
  }
  delete[] predecessor; 
  delete[] visited; 
  
  //return correct values 
  if (pathFound) {
    return PATH_FOUND; 
  }
  else {
    return NO_PATH; 
  }
}
