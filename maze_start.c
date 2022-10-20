//-----------------------------------------
// NAME: Manuel Espinoza 
// STUDENT NUMBER: 7946366
// COURSE: COMP 2160, SECTION: A02
// INSTRUCTOR: Rasit Eskicioglu
// ASSIGNMENT: Assignment #2
// 
// REMARKS: This code uses a backtracking
//          algorithm to find a path through a
//          maze. In order to accomplish this,
//          a linked-list-based stack has been 
//          implemented to keep track of the 
//          possible paths
//
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

#define MAX_DIMENSION 20
#define MAX_STRING_SIZE MAX_DIMENSION*2

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

CellNode *top;

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
void destroyList();

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

// creates a new cell
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
  assert(validCell(newCell));
  checkState();
  CellNode *node;
  node = malloc(sizeof(CellNode));
  assert(node != NULL);
  node->cell = newCell;
  node->next = top;
  top = node;
  checkState();
}

Cell nextCell(){
  checkState();
  Cell popped = top->cell;
  CellNode *tempCellPtr = top;
  top = top->next;
  assert(tempCellPtr != NULL);
  free(tempCellPtr);
  checkState();
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
  assert(rowString != NULL);
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
  checkState();
  printf("\n");
}

void loadMaze(){
  char inputLine[MAX_STRING_SIZE];
  fgets(inputLine, MAX_STRING_SIZE, stdin);
  mazeRows = atoi(strtok(inputLine, " "));
  mazeCols = atoi(strtok(inputLine, "\n"));

  for (int row = 0; row < mazeRows; row++)
  {
    fgets(inputLine, MAX_STRING_SIZE, stdin);
    if (inputLine[strlen(inputLine)-1] == '\n'){
      inputLine[strlen(inputLine)-1] = '\0';
    }
    for(int col = 0; col < mazeCols; col++)
    {
      assert(validCell(makeCell(row, col)));
      maze[row][col] = inputLine[col*2];
      if (maze[row][col] == MOUSE)
      {
        mouse.row = row;
        mouse.column = col;
      }
      if (maze[row][col] == EXIT)
      {
        escape.row = row;
        escape.column = col;
      }
    }
  }
  // checkState();
  printMaze();
  checkState();
}

// returns true if there's a solution to the maze
Boolean solveMaze(){
  Boolean solution = true;
  // initialize list
  top = malloc(sizeof(CellNode));
  checkState();

  // currentCell = startCell;
  Cell currentCell = mouse;

  // while currentCell is not the goalCell
  while (!equalCells(currentCell, escape) && solution)
  {
    //   mark currentCell as visited;
    maze[currentCell.row][currentCell.column] = VISITED;
    //   add to the list the unvisited open neighbours of currentCell;
    // add lower neighbour
    if (maze[currentCell.row+1][currentCell.column] != VISITED && 
        maze[currentCell.row+1][currentCell.column] != WALL)
    {
      Cell newCell = makeCell(currentCell.row +1, currentCell.column);
      addCell(newCell);
    }
    // add upper neighbour
    if (maze[currentCell.row-1][currentCell.column] != VISITED && 
        maze[currentCell.row-1][currentCell.column] != WALL)
    {
      Cell newCell = makeCell(currentCell.row-1, currentCell.column);
      assert(validCell(newCell));
      addCell(newCell);
    }
    // add left neighbour
    if (maze[currentCell.row][currentCell.column-1] != VISITED && 
        maze[currentCell.row][currentCell.column-1] != WALL)
    {
      Cell newCell = makeCell(currentCell.row, currentCell.column-1);
      assert(validCell(newCell));
      addCell(newCell);
    }
    // add right neighbour
    if (maze[currentCell.row][currentCell.column+1] != VISITED && 
        maze[currentCell.row][currentCell.column+1] != WALL)
    {
      Cell newCell = makeCell(currentCell.row, currentCell.column+1);
      assert(validCell(newCell));
      addCell(newCell);
    }
    printMaze();
    //   if the list is empty
    if (noMoreCells())
    {
      solution = false;
    }
    else{
    //     get the next cell from the list and make it currentCell;
      currentCell = nextCell();
    }
  }
  // end while;

  // the mouse can escape the maze: we reached the goal cell
  maze[currentCell.row][currentCell.column] = MOUSE;
  printMaze();
  destroyList();
  return solution;
}

void destroyList(){
  while (NULL != top){
    CellNode *tempCellPtr = top;
    top = top->next;
    free(tempCellPtr);
  }
}

//////////////////////////////////////////////
// Design-by-Contract routines
//////////////////////////////////////////////

// our invariant checker
void checkState(){
  assert(validCell(mouse));
  assert(validCell(escape));
  
  // assert(top != NULL);
}