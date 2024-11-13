//
//  TestBoard2.cpp
//
//  A test program for the Board module.  This is similar to
//    TestBoard1, but the board array now contains Tiles instead
//    of ints.

#include "Board.h"
#include "Board.h" // repeated to test for #include errors

#include <cassert>
#include <iostream>
#include <string>

#include "BoardSize.h"
#include "Player.h"
#include "TestHelper.h"
#include "Tile.h"

using namespace std;

int main();
double checkBoardAfterInit(const Tile board[BOARD_SIZE][BOARD_SIZE]);
void checkTileAfterInit(const Tile &current, const Tile &desired,
                        unsigned int &wrong_genus_count,
                        unsigned int &wrong_species_count,
                        unsigned int &wrong_owner_count,
                        bool &is_bad_tile_printed, int row, int column);
bool checkTile(const Tile &current, const Tile &desired);

const int COMPILE_AND_START_MARKS = 1;
const int DID_NOT_CRASH_RUNNING_MARKS = 1;
const int COMPILE_AND_NOT_CRASH_MARKS =
    COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS = 3;
const int TOTAL_MARKS = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const int BOARD_SIZE_CORRECT = 7;
const int BOARD_CELL_COUNT_CORRECT = BOARD_SIZE_CORRECT * BOARD_SIZE_CORRECT;

const int BOARD_CENTER = BOARD_SIZE_CORRECT / 2; // integer division
const int MONEY_CENTER = 4;

const unsigned int ROLL_PLAYER_COUNT = 5;

const int SET_1_ROW = 0;
const int SET_1_COLUMN = 1;
const Tile SET_1_VALUE = tileCreate(GENUS_MONEY, 5);
const int SET_1_OWNER = 1;

const int SET_2_ROW = 3;
const int SET_2_COLUMN = 6;
const Tile SET_2_VALUE = tileCreate(GENUS_POINTS, 8);
const int SET_2_OWNER = 0;

int main() {
  testHelperStartup("TestBoard2", COMPILE_AND_START_MARKS, TOTAL_MARKS);

  string player_names[2] = {"Mary", "John"};
  playerInit(2, player_names);

  //
  //  Test board cells
  //

  cout << "Checking board size in bytes" << endl;
  bool correct_board_bytes =
      sizeof(Board) == sizeof(Tile) * BOARD_CELL_COUNT_CORRECT;
  if (!correct_board_bytes)
    cout << "* Incorrect: Board should contain a 2D array of Tiles" << endl;
  else
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Initializing board" << endl;
  Board board;
  boardInit(board);
  cout << "Completed without crashing" << endl;
  double correct_init_fraction = checkBoardAfterInit(board);
  cout << endl;

  cout << "Checking setAt (1)" << endl;
  boardSetAt(board, SET_1_ROW, SET_1_COLUMN, SET_1_VALUE, SET_1_OWNER);
  const Tile &get_after_set1 = boardGetAt(board, SET_1_ROW, SET_1_COLUMN);
  Tile value1_with_owner = SET_1_VALUE;
  tileSetOwner(value1_with_owner, SET_1_OWNER);
  bool correct_set1 = checkTile(get_after_set1, value1_with_owner);
  cout << endl;

  cout << "Checking setAt (2)" << endl;
  boardSetAt(board, SET_2_ROW, SET_2_COLUMN, SET_2_VALUE, SET_2_OWNER);
  const Tile &get_after_set2 = boardGetAt(board, SET_2_ROW, SET_2_COLUMN);
  Tile value2_with_owner = SET_2_VALUE;
  tileSetOwner(value2_with_owner, SET_2_OWNER);
  bool correct_set2 = checkTile(get_after_set2, value2_with_owner);
  cout << endl;

  //
  //  Test display
  //

  cout << "Printing board" << endl;
  boardPrint(board);
  cout << endl;

  //
  //  Print results
  //

  testHelperPrintSummaryHeader(16, 1, DID_NOT_CRASH_RUNNING_MARKS);
  testHelperPrintSummaryLine("Representation", correct_board_bytes);
  testHelperPrintSummaryLine("boardInit", correct_init_fraction);
  testHelperPrintSummaryLine("boardSetAt (1)", correct_set1);
  testHelperPrintSummaryLine("boardSetAt (2)", correct_set2);

  //
  //  Print mark
  //

  unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

  if (correct_board_bytes)
    mark += 1;
  mark += (int)(correct_init_fraction * 1);
  if (correct_set1 && correct_set2)
    mark += 1;

  assert(mark <= TOTAL_MARKS);
  testHelperPrintMark(mark, TOTAL_MARKS);

  testHelperWaitForEnter();
  return 0;
}

double checkBoardAfterInit(const Tile board[BOARD_SIZE][BOARD_SIZE]) {
  unsigned int wrong_genus_count = 0;
  unsigned int wrong_species_count = 0;
  unsigned int wrong_owner_count = 0;
  unsigned int total_count = (BOARD_CENTER * 2 + 1) * (BOARD_CENTER * 2 + 1);

  for (int ring = 0; ring <= BOARD_CENTER; ring++) {
    Tile correct = tileCreate(GENUS_MONEY, MONEY_CENTER - ring);
    bool is_bad_tile_printed = false;

    for (int row = BOARD_CENTER - ring; row <= BOARD_CENTER + ring; row++) {
      const Tile &current1 = boardGetAt(board, row, BOARD_CENTER - ring);
      checkTileAfterInit(current1, correct, wrong_genus_count,
                         wrong_species_count, wrong_owner_count,
                         is_bad_tile_printed, row, BOARD_CENTER - ring);

      if (ring != 0) {
        const Tile &current2 = boardGetAt(board, row, BOARD_CENTER + ring);
        checkTileAfterInit(current2, correct, wrong_genus_count,
                           wrong_species_count, wrong_owner_count,
                           is_bad_tile_printed, row, BOARD_CENTER + ring);
      }
    }

    for (int column = BOARD_CENTER - ring + 1; column < BOARD_CENTER + ring;
         column++) {
      const Tile &current1 = boardGetAt(board, BOARD_CENTER - ring, column);
      checkTileAfterInit(current1, correct, wrong_genus_count,
                         wrong_species_count, wrong_owner_count,
                         is_bad_tile_printed, BOARD_CENTER - ring, column);

      const Tile &current2 = boardGetAt(board, BOARD_CENTER + ring, column);
      checkTileAfterInit(current2, correct, wrong_genus_count,
                         wrong_species_count, wrong_owner_count,
                         is_bad_tile_printed, BOARD_CENTER + ring, column);
    }
  }

  if (wrong_genus_count > 0)
    cout << "* Incorrect: " << wrong_genus_count << " / " << total_count
         << " tile genuses are wrong" << endl;
  if (wrong_species_count > 0)
    cout << "* Incorrect: " << wrong_species_count << " / " << total_count
         << " tile species (money values) are wrong" << endl;
  if (wrong_owner_count > 0)
    cout << "* Incorrect: " << wrong_owner_count << " / " << total_count
         << " tile owners are wrong" << endl;
  if (wrong_genus_count == 0 && wrong_species_count == 0 &&
      wrong_owner_count == 0) {
    cout << "* Correct" << endl;
  }

  double fraction_genus = (double)(wrong_genus_count) / (double)(total_count);
  double fraction_species =
      (double)(wrong_species_count) / (double)(total_count);
  double fraction_owner = (double)(wrong_owner_count) / (double)(total_count);

  double largest_fraction = fraction_genus;
  if (largest_fraction < fraction_species)
    largest_fraction = fraction_species;
  if (largest_fraction < fraction_owner)
    largest_fraction = fraction_owner;

  assert(largest_fraction >= 0.0);
  assert(largest_fraction <= 1.0);
  return 1.0 - largest_fraction;
}

void checkTileAfterInit(const Tile &current, const Tile &desired,
                        unsigned int &wrong_genus_count,
                        unsigned int &wrong_species_count,
                        unsigned int &wrong_owner_count,
                        bool &is_bad_tile_printed, int row, int column) {
  if (tileGetGenus(current) != tileGetGenus(desired)) {
    wrong_genus_count++;
    if (!is_bad_tile_printed) {
      cout << "* Incorrect: Tile at (row = " << row << ", " << column
           << ") has genus " << tileGetGenus(current) << ", should be genus "
           << tileGetGenus(desired) << endl;
      is_bad_tile_printed = true;
    }
  }

  if (tileGetSpecies(current) != tileGetSpecies(desired)) {
    wrong_species_count++;
    if (!is_bad_tile_printed) {
      cout << "* Incorrect: Tile at (row = " << row << ", " << column
           << ") has species " << tileGetSpecies(current)
           << ", should be species " << tileGetSpecies(desired) << endl;
      is_bad_tile_printed = true;
    }
  }

  if (tileIsOwner(current) != tileIsOwner(desired)) {
    wrong_owner_count++;
    if (!is_bad_tile_printed) {
      cout << "* Incorrect: Tile at (row = " << row << ", " << column;
      if (tileIsOwner(current))
        cout << ") has owner but shouldn't" << endl;
      else
        cout << ") should have owner but doesn't" << endl;
      is_bad_tile_printed = true;
    }
  }
}

bool checkTile(const Tile &current, const Tile &desired) {
  if (tileGetGenus(current) != tileGetGenus(desired)) {
    cout << "* Incorrect: Genus was " << tileGetGenus(current) << ", should be "
         << tileGetGenus(desired) << endl;
    return false;
  }
  if (tileGetSpecies(current) != tileGetSpecies(desired)) {
    cout << "* Incorrect: Species was " << tileGetSpecies(current)
         << ", should be " << tileGetSpecies(desired) << endl;
    return false;
  }
  if (tileIsOwner(current) != tileIsOwner(desired)) {
    if (tileIsOwner(current))
      cout << "* Incorrect: Tile has owner but shouldn't" << endl;
    else
      cout << "* Incorrect: Tile should have owner but doesn't" << endl;
    return false;
  }
  if (tileIsOwner(current)) {
    for (unsigned int i = 0; i < ROLL_PLAYER_COUNT; i++) {
      unsigned int current_affected = tileGetAffectedPlayer(current, i);
      unsigned int desired_affected = tileGetAffectedPlayer(desired, i);
      if (current_affected != desired_affected) {
        cout << "* Incorrect: Tile should affects player " << current_affected
             << " (" << i << " rolled), should be " << desired_affected << endl;
        return false;
      }
    }
  }

  cout << "* Correct" << endl;
  return true;
}
