#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "BoardSize.h"
#include "CellId.h"
using namespace std;

CellId toCellId (int row1, int column1)
{
  CellId Id;
  Id.row = row1;
  Id.column = column1;
  return Id;  
}
bool isOnBoard (const CellId& cell_id)
{  
  if (cell_id.row >= 0 && cell_id.row < BOARD_SIZE && cell_id.column >= 0 && cell_id.column < BOARD_SIZE)
  return 1;
  else 
  return 0;
}
void printCellId (const CellId& cell_id)
{
  char r = getRowName (cell_id.row);
  char c = getColumnName (cell_id.column);
  cout << r << c;
}
bool isOnBoard (const std::string& str)
{
  if (str.length() == 2)
    {
      if (str[0] == 'A' || str[0] == 'B' || str[0] == 'C' || str[0] == 'D'|| str[0] == 'E' || str[0] == 'F' || str[0] == 'G')
      {
        if(str[1] == '0' || str[1] == '1' || str[1] == '2' || str[1] == '3'|| str[1] == '4' || str[1] == '5' || str[1] == '6')
        {
          return 1;
        }
        
        else
        return 0;
      }
      else
      return 0;
    }
  else
  return 0;
}

CellId toCellId (const std::string& str)
{
  CellId str1;
  
  assert(isOnBoard(str) == 1);

  int a = str[0] - 'A';
  str1.row = a; 
  
  int b = str[1] - '0';
  str1.column = b;
  return str1;
}





