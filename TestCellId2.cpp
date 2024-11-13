//
//  TestCellId2.cpp
//
//  A test program for the CellId module.

#include "CellId.h"
#include "CellId.h" // repeated to test for #include errors

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo> // for typeid

#include "TestHelper.h"

using namespace std;

int main();
bool checkCellId(const CellId &cell_id, int correct_row, int correct_column);
unsigned int checkPrintCellId();

const int COMPILE_AND_START_MARKS = 3;
const int DID_NOT_CRASH_RUNNING_MARKS = 3;
const int COMPILE_AND_NOT_CRASH_MARKS =
    COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS = 17;
const int TOTAL_MARKS = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const int CELL_ID_1_ROW = 2;
const int CELL_ID_1_COLUMN = 6;

const int CELL_ID_2_ROW = 9;
const int CELL_ID_2_COLUMN = -1;

const int CHECK_ON_BOARD_MIN = 0;
const int CHECK_ON_BOARD_MAX = 6;
const int CHECK_ON_BOARD_MIDDLE = (CHECK_ON_BOARD_MIN + CHECK_ON_BOARD_MAX) / 2;

const unsigned int CORNER_COUNT = 4;
const unsigned int SIDE_COUNT = 4;

const unsigned int CELL_ID_AS_STRING_TOTAL_COUNT = 20;
const unsigned int CELL_ID_AS_STRING_GOOD_COUNT = 8;
const string CELL_ID_AS_STRING[CELL_ID_AS_STRING_TOTAL_COUNT] = {
    "A0", "B2", "D6", "E1", "G4",  "G3",  "A2", "D3", "H0", "F7",
    "Z1", "3C", "AA", "55", "A10", "D 2", "A",  "1",  " ",  "",
};
const int CELL_ID_ROW_FOR_STRING[CELL_ID_AS_STRING_GOOD_COUNT] = {
    0, 1, 3, 4, 6, 6, 0, 3,
};
const int CELL_ID_COLUMN_FOR_STRING[CELL_ID_AS_STRING_GOOD_COUNT] = {
    0, 2, 6, 1, 4, 3, 2, 3};

int main() {
  testHelperStartup("TestCellId2", COMPILE_AND_START_MARKS, TOTAL_MARKS);

  //
  //  Run tests
  //

  cout << "Creating CellId without initializing" << endl;
  CellId cell_id_uninitialized;
  cell_id_uninitialized; // surpress warning about unused local variable
  cout << "Completed without crashing" << endl;
  cout << endl;

  cout << "Creating CellId #1 for (row " << CELL_ID_1_ROW << ", column "
       << CELL_ID_1_COLUMN << ")" << endl;
  CellId cell_id1 = toCellId(CELL_ID_1_ROW, CELL_ID_1_COLUMN);
  bool correct_init1 = checkCellId(cell_id1, CELL_ID_1_ROW, CELL_ID_1_COLUMN);
  cout << endl;

  cout << "Creating CellId #2 for (row " << CELL_ID_2_ROW << ", column "
       << CELL_ID_2_COLUMN << ")" << endl;
  CellId cell_id2 = toCellId(CELL_ID_2_ROW, CELL_ID_2_COLUMN);
  bool correct_init2 = checkCellId(cell_id2, CELL_ID_2_ROW, CELL_ID_2_COLUMN);
  cout << endl;

  cout << "Checking if CellIds are on the board" << endl;
  bool correct_on_board1 = isOnBoard(cell_id1) == true;
  bool correct_on_board2 = isOnBoard(cell_id2) == false;
  if (!correct_on_board1)
    cout << "* Incorrect: CellId #1 is on the board, but says it isn't" << endl;
  if (!correct_on_board2)
    cout << "* Incorrect: CellId #2 is not on the board, but says it is"
         << endl;
  if (correct_on_board1 && correct_on_board2)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Checking if CellIds in the corners are on the board" << endl;
  assert(CORNER_COUNT == 4);
  unsigned int correct_corner = 0;
  for (unsigned int i = 0; i < CORNER_COUNT; i++) {
    int row = (i % 2 == 0) ? CHECK_ON_BOARD_MIN : CHECK_ON_BOARD_MAX;
    int column = (i / 2 == 0) ? CHECK_ON_BOARD_MIN : CHECK_ON_BOARD_MAX;
    CellId cell_id = toCellId(row, column);
    bool correct = isOnBoard(cell_id) == true;
    if (correct)
      correct_corner++;
    else {
      cout << "* Incorrect: Corner cell ";
      printCellId(cell_id);
      cout << " is on the board, but says it isn't" << endl;
    }
  }
  if (correct_corner == CORNER_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Checking if CellIds just off the sides are on the board" << endl;
  assert(SIDE_COUNT == 4);
  unsigned int correct_side = 0;
  CellId cell_id_side[SIDE_COUNT];
  cell_id_side[0] = toCellId(CHECK_ON_BOARD_MIDDLE, CHECK_ON_BOARD_MIN - 1);
  cell_id_side[1] = toCellId(CHECK_ON_BOARD_MIDDLE, CHECK_ON_BOARD_MAX + 1);
  cell_id_side[2] = toCellId(CHECK_ON_BOARD_MIN - 1, CHECK_ON_BOARD_MIDDLE);
  cell_id_side[3] = toCellId(CHECK_ON_BOARD_MAX + 1, CHECK_ON_BOARD_MIDDLE);
  for (unsigned int i = 0; i < SIDE_COUNT; i++) {
    bool correct = isOnBoard(cell_id_side[i]) == false;
    if (correct)
      correct_side++;
    else {
      cout << "* Incorrect: Side cell ";
      printCellId(cell_id_side[i]);
      cout << " is not on the board, but says it is" << endl;
    }
  }
  if (correct_side == SIDE_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Checking isOnBoard(string)" << endl;
  unsigned int correct_is_cell_id = 0;
  for (unsigned int i = 0; i < CELL_ID_AS_STRING_TOTAL_COUNT; i++) {
    bool is_cell_on_board = isOnBoard(CELL_ID_AS_STRING[i]);
    bool correct_value = (i < CELL_ID_AS_STRING_GOOD_COUNT);
    if (is_cell_on_board == correct_value)
      correct_is_cell_id++;
    else if (is_cell_on_board)
      cout << "* Incorrect: Reported \"" << CELL_ID_AS_STRING[i]
           << "\" as a valid cell ID, but isn't" << endl;
    else
      cout << "* Incorrect: \"" << CELL_ID_AS_STRING[i]
           << "\" is a valid cell ID, but reported as not" << endl;
  }
  if (correct_is_cell_id == CELL_ID_AS_STRING_TOTAL_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Checking toCellId(string)" << endl;
  unsigned int correct_to_cell_id = 0;
  for (unsigned int i = 0; i < CELL_ID_AS_STRING_GOOD_COUNT; i++) {
    if (isOnBoard(CELL_ID_AS_STRING[i])) {
      CellId cell_id = toCellId(CELL_ID_AS_STRING[i]);
      if (cell_id.row != CELL_ID_ROW_FOR_STRING[i])
        cout << "* Incorrect: Cell row for \"" << CELL_ID_AS_STRING[i]
             << "\" parsed as " << cell_id.row << ", but should be "
             << CELL_ID_ROW_FOR_STRING[i] << endl;
      if (cell_id.column != CELL_ID_COLUMN_FOR_STRING[i])
        cout << "* Incorrect: Cell column for \"" << CELL_ID_AS_STRING[i]
             << "\" parsed as " << cell_id.column << ", but should be "
             << CELL_ID_COLUMN_FOR_STRING[i] << endl;
      if (cell_id.row == CELL_ID_ROW_FOR_STRING[i] &&
          cell_id.column == CELL_ID_COLUMN_FOR_STRING[i]) {
        correct_to_cell_id++;
      }
    } else
      cout << "* Skipped: Didn't try parsing \"" << CELL_ID_AS_STRING[i]
           << "\" because reported as not a valid cell ID" << endl;
  }
  if (correct_to_cell_id == CELL_ID_AS_STRING_GOOD_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Testing printCellId" << endl;
  unsigned int correct_print = checkPrintCellId();
  cout << endl;

  //
  //  Print results
  //

  testHelperPrintSummaryHeader(20, 2, DID_NOT_CRASH_RUNNING_MARKS);
  testHelperPrintSummaryLine("toCellId (1)", correct_init1);
  testHelperPrintSummaryLine("toCellId (2)", correct_init2);
  testHelperPrintSummaryLine("isOnBoard (1)", correct_on_board1);
  testHelperPrintSummaryLine("isOnBoard (2)", correct_on_board2);
  testHelperPrintSummaryLine("Is corner on board", correct_corner,
                             CORNER_COUNT);
  testHelperPrintSummaryLine("Off sides on board", correct_side, SIDE_COUNT);
  testHelperPrintSummaryLine("isOnBoard(string)", correct_is_cell_id,
                             CELL_ID_AS_STRING_TOTAL_COUNT);
  testHelperPrintSummaryLine("toCellId(string)", correct_to_cell_id,
                             CELL_ID_AS_STRING_GOOD_COUNT);
  testHelperPrintSummaryLine("printCellId", correct_print,
                             CELL_ID_AS_STRING_GOOD_COUNT);

  unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

  if (correct_init1)
    mark += 1;
  if (correct_init2)
    mark += 1;
  if (correct_on_board1 && correct_on_board2)
    mark += 1;
  mark += testHelperMarkAnyAll(correct_corner, CORNER_COUNT);
  mark += testHelperMarkAnyAll(correct_side, SIDE_COUNT);
  mark += correct_is_cell_id / 5; // max 4
  mark += correct_to_cell_id / 2; // max 4
  mark += testHelperMarkAnyAll(correct_print, CELL_ID_AS_STRING_GOOD_COUNT);

  assert(mark <= TOTAL_MARKS);
  testHelperPrintMark(mark, TOTAL_MARKS);

  testHelperWaitForEnter();
  return 0;
}

string toString(const CellId &cell_id) {
  stringstream ss;
  ss << "(row " << cell_id.row << ", column " << cell_id.column << ")";
  return ss.str();
}

bool checkCellId(const CellId &cell_id, int correct_row, int correct_column) {
  if (cell_id.row != correct_row) {
    cout << "* Incorrect: Row is " << cell_id.row << ", should be "
         << correct_row << endl;
    return false;
  } else if (cell_id.column != correct_column) {
    cout << "* Incorrect: Column is " << cell_id.column << ", should be "
         << correct_column << endl;
    return false;
  } else {
    cout << "* Correct" << endl;
    return true;
  }
}

unsigned int checkPrintCellId() {
  // print correct cell names
  cout << "Correct: ";
  string printed_correct[CELL_ID_AS_STRING_GOOD_COUNT];
  for (unsigned int i = 0; i < CELL_ID_AS_STRING_GOOD_COUNT; i++) {
    char row_char = 'A' + CELL_ID_ROW_FOR_STRING[i];
    char column_char = '0' + CELL_ID_COLUMN_FOR_STRING[i];
    cout << "  ";
    testHelperStartCapture();
    cout << row_char << column_char;
    printed_correct[i] = testHelperEndCapture();
  }
  cout << endl;

  // print cell names from program
  cout << "Results: ";
  string printed[CELL_ID_AS_STRING_GOOD_COUNT];
  for (unsigned int i = 0; i < CELL_ID_AS_STRING_GOOD_COUNT; i++) {
    CellId cell_id =
        toCellId(CELL_ID_ROW_FOR_STRING[i], CELL_ID_COLUMN_FOR_STRING[i]);
    cout << "  ";
    testHelperStartCapture();
    printCellId(cell_id);
    printed[i] = testHelperEndCapture();
  }
  cout << endl;

  // check cell names
  unsigned int correct_count = 0;
  for (unsigned int i = 0; i < CELL_ID_AS_STRING_GOOD_COUNT; i++) {
    if (printed[i] == printed_correct[i])
      correct_count++;
  }

  // print result
  if (correct_count == 0)
    cout << "* Incorrect: All cell names were printed incorrectly" << endl;
  else if (correct_count < CELL_ID_AS_STRING_GOOD_COUNT)
    cout << "* Incorrect: Some cell names were printed incorrectly" << endl;
  else
    cout << "* Correct" << endl;
  return correct_count;
}
