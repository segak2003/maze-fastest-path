/* 
readMaze.cpp
*/

#include <iostream>
#include <fstream>
#include "readMaze.h"


//this function Reads the maze from the given filename into a 2D dynamically allocated array
    //the The first argument is the filename of the maze input.
char** read_maze(char* filename, int* rows, int* cols) {
    std::ifstream inputFile(filename);
  
    // Check if the file was opened successfully and return NULL if unsuccessfull
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return nullptr;
    }
  
    // Read maze dimensions and return NULL if Unable
    inputFile >> *rows >> *cols;
    if (inputFile.fail()) {
        std::cerr << "No values to read in" << std::endl;
        return nullptr;
    }
  
    // Allocate maze memory
    char** maze = new char*[*rows];
    for (int i = 0; i < *rows; i++) {
        maze[i] = new char[*cols];
    }
  
    // Populate the maze from the file
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (!(inputFile >> maze[i][j])) {
                std::cerr << "Nothing to read in!" << std::endl;
                return nullptr;
            }
        }
    }
    return maze;
}

//this functions prints out the maze
void print_maze(char** maze, int rows, int cols) {
    std::cout << rows << " " << cols << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}
