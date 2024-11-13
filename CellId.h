#pragma once

#include <string>
#include <cassert>

struct CellId
{
  int row, column;
};



//  toCellId
//
// Purpose: To accept integer values for row and column to
//          return a exact location or ID of a cell which is 
//          stored in the structure.         
//  Parameter(s):
//    <1> row1: Represents the row number
//    <2> column1: Represents the column number
//  Precondition(s): N/A
//  Returns: The ID of a cell
//  Side Effect: N/A

CellId toCellId (int row1, int column1);




//  isOnBoard
//
// Purpose: Examines weather the row and column are part of the
//          board game or not. Function verifies that their values 
//          are not below 0 and beyond BOARD_SIZE
//  Parameter(s):
//    <1> cell_id: Object for structure CellId
//  Precondition(s): N/A
//  Returns: Whether the values of row and column are within the 
//           limits of BoardSize
//  Side Effect: N/A
bool isOnBoard (const CellId& cell_id);




//  isOnBoard
//
// Purpose: Transforms the type of row and column to character 
//          type and prints them. 
//  Parameter(s):
//    <1> cell_id: Object for structure CellId
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: N/A
void printCellId (const CellId& cell_id);



//  isOnBoard
//
// Purpose: Examines whether the string is a name of a cell on board 
//          or not. Function checks the length of the string to be 2, 
//          uppercase letter representing a row and digit representing 
//          a column
//  Parameter(s): 
//    <1> str: The string comprised of characters for row and column
//  Precondition(s): N/A
//  Returns: Whether or not the string names a cell on the board
//  Side Effect: N/A
bool isOnBoard (const std::string& str);



//  toCellId
//
// Purpose: Converts the characters of a string to their corresponding integer type. 
//  Parameter(s):
//    <1> str: The string comprised of characters for row and column 
//  Precondition(s):
//    <1> isOnBoard(str) == 1
//  Returns: N/A
//  Side Effect: N/A
CellId toCellId (const std::string& str);