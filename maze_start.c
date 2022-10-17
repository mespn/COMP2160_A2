#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

#define MAX_DIMENSION 20

// constant definitions for the different cell states
const char WALL    = '1';
const char SPACE   = '0';
const char VISITED = '.';
const char MOUSE   = 'm';
const char EXIT    = 'e';

typedef enum BOOL { false, true } Boolean;

struct CELL
{
  int row;
  int column;
};
typedef struct CELL Cell;

typedef struct CELL_NODE CellNode;
struct CELL_NODE
{
  Cell     cell;
  CellNode *next;
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

CellNode *top = NULL;

// a 2D array used to store the maze
char maze[MAX_DIMENSION][MAX_DIMENSION];
int mazeRows;
int mazeCols;

// holds the location of the mouse and escape hatch
Cell mouse;
Cell escape;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// basic cell manipulation

// returns true if the cells are at the same position in our maze
Boolean equalCells(const Cell , const Cell);
// returns a new cell object
Cell makeCell(const int, const int );
// returns true if the cell is within our maze
Boolean validCell(const Cell);

// routines for managing our backtracking

// returns true if there are no more cells to try
Boolean noMoreCells();
// returns the next cell to try for a path out of the maze
Cell nextCell();
// introduces a new cell to try
void addCell(const Cell cell);

void printMaze();
void loadMaze();

// returns true if there's a solution to the maze
Boolean solveMaze();

// our invariant checker
void checkState();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
    loadMaze();

    if ( solveMaze() )
      printf( "The mouse is free!!!!\n" );
    else
      printf( "The mouse is trapped!!!!\n" );
    
    printf( "\nEnd of processing\n" );
    
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////
// Cell routines
//////////////////////////////////////////////
Boolean equalCells(const Cell cell1, const Cell cell2){
  Boolean equals = false;
  if (cell1.row == cell2.row && cell1.column == cell2.column)
    equals = true;
  return equals;
}

// returns a new cell object
Cell makeCell(const int row, const int col){
  Cell newCell;
  newCell.row = row;
  newCell.column = col;
  return newCell;
}

// returns true if the cell is within our maze
Boolean validCell(const Cell theCell)
{
  Boolean valid = false;
  if (theCell.row >= 0 && theCell.row < mazeRows && 
      theCell.column >= 0 && theCell.column < mazeCols)
  {
    valid = true;
  }
  return valid;
}

//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////
void addCell(const Cell newCell){
  CellNode *node;
  node = malloc(sizeof(CellNode));
  node->cell = newCell;
  node->next = top;
  top = node;
}

Cell nextCell(){
  Cell popped = top->cell;
  CellNode *tempCellPtr = top;
  top = top->next;
  assert(tempCellPtr != NULL);
  free(tempCellPtr);
  return popped;
}

Boolean noMoreCells(){
  return top == NULL;
}

//////////////////////////////////////////////
// Maze routines
//////////////////////////////////////////////

void printMaze(){
  char *rowString;
  rowString = malloc(sizeof(char)* mazeCols);
  rowString[0] = '\0';
  for (int i = 0; i < mazeRows; i++)
  {
    for (int j = 0; j < mazeCols; j++)
    {
      int index = strlen(rowString);
      rowString[index] = maze[i][j];
      rowString[index + 1] = ' ';
      rowString[index + 2] = '\0';
    }
    printf("%s\n", rowString);
    rowString[0] = '\0';
  }
  free(rowString);
}

void loadMaze(){
  mazeRows = fgetc(stdin);
  mazeCols = fgetc(stdin);

  printf("Rows: %d Columns: %d", mazeRows, mazeCols);
}

// returns true if there's a solution to the maze
Boolean solveMaze(){
  return true;
}


//////////////////////////////////////////////
// Design-by-Contract routines
//////////////////////////////////////////////

// our invariant checker
void checkState(){
  
}