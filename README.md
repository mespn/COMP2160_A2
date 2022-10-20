# Maze Solver

**Author:** Manuel Espinoza Narro

**Student Number:** 7946366

---

## Summary

The program maze_start.c is the solution to the problem assigned in COMP2160  (Programming Practices)Assignment 2s.

This code uses a backtracking algorithm to find a path through a maze. In order to accomplish this, a linked-list-based stack has been implemented to keep track of the possible paths

---

## Compilation and run

### To compile

>`clang -Wall maze_start.c -o [mazeSolver]`

`mazeSolver` can be replaced with any filename 

### To run

>`mazeSolver <[maze]`

`maze` is the text file containing the maze to be solved

---

## Maze format

Every maze should be given in the following format:


    [# rows] [# columns]

    1 1 1 1 1 1 1 ... 1
    1 _ _ _ _ _ _ ... 1
    1 _ _ _ _ _ _ ... 1
    1 _ _ _ _ _ _ ... 1
    1 _ _ _ _ _ _ ... 1
    1 _ _ _ _ _ _ ... 1
    1 _ _ _ _ _ _ ... 1
    : : : : : : :  :  :
    1 1 1 1 1 1 1 ... 1

### Where:

`# rows` integer value corresponding to the
correct number of rows in the maze

`# columns` integer value corresponding to the
correct number of columns in the maze

`'_'` characters are replaced 
with `'1'` (walls), `'0'` (paths), and exactly one `'m'` and one `'e'` characters 
which will represent the mouse and exit respectively.