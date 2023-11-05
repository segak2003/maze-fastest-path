/* 
readMaze.h
*/

#ifndef READMAZE_H
#define READMAZE_H

// reads the maze from the given filename, then allocates and returns a maze 2D array,
char** read_maze(char* filename, int* rows, int* cols);

// prints the maze
void print_maze(char** maze, int rows, int cols);

#endif
