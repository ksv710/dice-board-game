//
//  Main.cpp

#include <iostream>
#include <string>

#include "Board.h"
#include "BoardSize.h"
#include "CellId.h"
#include "Dice.h"
#include "Player.h"
#include "Tile.h"

using namespace std;

const int PLAYER_COUNT = 2;

int main() {
  // setup

  diceInit();

  Board board;
  boardInit(board);

  string player_names[PLAYER_COUNT];
  player_names[0] = "Akash";
  player_names[1] = "Kiara";
  playerInit(PLAYER_COUNT, player_names);

  cout << "Welcome to the game." << endl;

  // run main loop

  unsigned int current_player = 0;
  string input;

  do {
    // print game state

    cout << endl;
    cout << endl;
    boardPrint(board);
    cout << endl;
    string name = playerGetName(current_player);
    cout << name << "'s turn:" << endl;
    cout << endl;

    // handle dice

    int row1 = diceRoll();
    int row2 = diceRoll();
    int column1 = diceRoll();
    int column2 = diceRoll();

    dicePrint2and2(row1, row2, column1, column2);
    cout << endl;

    int row_chosen = row1 + row2;
    int column_chosen = column1 + column2;
    char row_name = getRowName(row_chosen);
    char column_name = getColumnName(column_chosen);
    cout << "Rolled cell: " << row_name << column_name << endl;

    // handle cell effects

    Tile income = boardGetAt(board, row_chosen, column_chosen);

    tileActivate(income, current_player);
    cout << endl;
    playerPrint(current_player);
    // get input
    cout << "Choose a cell: ";
    getline(cin, input);

    bool c = isOnBoard(input);
    if (c == 1) {
      CellId ID = toCellId(input);
      Tile location = boardGetAt(board, ID.row, ID.column);
      bool c1 = tileIsOwner(location);
      if (c1 == 1)
        cout << "Failure: Invalid cell" << endl;

      else {
        Tile x = tileCreate(GENUS_POINTS, 1);
        boardSetAt(board, ID.row, ID.column, x, current_player);
        cout << "Success: Tile added";
      }
    } else
      cout << "Failure: Invalid cell" << endl;

    // set up for next player

    current_player++;
    if (current_player >= PLAYER_COUNT)
      current_player = 0;
  } while (input != "q" && playerHasPointsAnyone(5) == 0);

  // print end messages

  cout << endl;
  cout << endl;
  for (int p = 0; p < PLAYER_COUNT; p++) {
    playerPrint(p);
  }
  cout << endl;
  cout << "Thank you for playing!" << endl;

  return 0; // program exited without crashing
}
