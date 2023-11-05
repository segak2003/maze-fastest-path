# maze-fastest-path
Maze solver written in C++

A program that reads in a maze from a file, attempts to find a path from start to finish, and outputs the result.

Overview
The project consists of a maze solver that uses a specific algorithm to find the path between a start (S) and finish (F) point within a maze. The mazes are represented in text files where each character has a meaning:

#: Wall
.: Open path
S: Start
F: Finish

Features
Reads maze configurations from files.
Attempts to solve the maze and find a path from S to F.
Displays the solved maze with the path indicated by * characters or provides an appropriate message if no path is found.
Validates the maze input to ensure it has exactly one S and one F.
