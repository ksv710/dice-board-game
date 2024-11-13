//
//  TestTile2.cpp
//
//  A test program for the Tile module.

#include "Tile.h"
#include "Tile.h" // repeated to test for #include errors

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo> // for typeid

#include "Player.h"
#include "TestHelper.h"

using namespace std;

int main();
bool checkTile(const Tile &tile, unsigned int correct_genus,
               unsigned int correct_species, bool print_messages);
bool checkTile(const Tile &tile, unsigned int correct_genus,
               unsigned int correct_species, unsigned int correct_owner);
unsigned int checkPrintTile();

const int COMPILE_AND_START_MARKS = 5;
const int DID_NOT_CRASH_RUNNING_MARKS = 5;
const int COMPILE_AND_NOT_CRASH_MARKS =
    COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS = 21;
const int TOTAL_MARKS = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int GENUS_COUNT_CORRECT = 4;
const unsigned int GENUS_MONEY_CORRECT = 0;
const unsigned int GENUS_DICE_CORRECT = 1;
const unsigned int GENUS_POINTS_CORRECT = 2;
const unsigned int GENUS_BOMB_CORRECT = 3;

const unsigned int SPECIES_COUNT = 8;
const unsigned int ROLL_PLAYER_COUNT = 5;

const unsigned int PRINT_COUNT = 8;
const unsigned int PRINT_GENUS[PRINT_COUNT] = {
    GENUS_MONEY_CORRECT,  GENUS_MONEY_CORRECT,  GENUS_POINTS_CORRECT,
    GENUS_MONEY_CORRECT,  GENUS_POINTS_CORRECT, GENUS_MONEY_CORRECT,
    GENUS_POINTS_CORRECT, GENUS_POINTS_CORRECT,
};

int main() {
  testHelperStartup("TestTile2", COMPILE_AND_START_MARKS, TOTAL_MARKS);

  string player_names[4] = {"William", "Xerxes", "Yamamoto", "Zenobia"};
  playerInit(4, player_names);

  //
  //  Test constants
  //

  cout << "Checking GENUS_COUNT" << endl;
  bool correct_genus_count =
      testHelperConstant(GENUS_COUNT, GENUS_COUNT_CORRECT, "GENUS_COUNT");
  cout << endl;

  cout << "Checking GENUS_MONEY" << endl;
  bool correct_genus_money =
      testHelperConstant(GENUS_MONEY, GENUS_MONEY_CORRECT, "GENUS_MONEY");
  cout << endl;

  cout << "Checking GENUS_DICE" << endl;
  bool correct_genus_dice =
      testHelperConstant(GENUS_DICE, GENUS_DICE_CORRECT, "GENUS_DICE");
  cout << endl;

  cout << "Checking GENUS_POINTS" << endl;
  bool correct_genus_points =
      testHelperConstant(GENUS_POINTS, GENUS_POINTS_CORRECT, "GENUS_POINTS");
  cout << endl;

  cout << "Checking GENUS_BOMB" << endl;
  bool correct_genus_bomb =
      testHelperConstant(GENUS_BOMB, GENUS_BOMB_CORRECT, "GENUS_BOMB");
  cout << endl;

  //
  //  Test creating tiles of different types
  //

  cout << "Creating Tile without initializing" << endl;
  Tile tile_uninitialized;
  tile_uninitialized; // surpress warning about unused local variable
  cout << "Completed without crashing" << endl;
  cout << endl;

  cout << "Creating unowned money tiles" << endl;
  unsigned int correct_money_unowned = 0;
  for (unsigned int i = 0; i < SPECIES_COUNT; i++) {
    unsigned int money = i + 1;
    unsigned int owner = (1 + i) % 3;
    Tile tile = tileCreate(GENUS_MONEY, money);
    bool correct = checkTile(tile, GENUS_MONEY, money, true);
    if (correct)
      correct_money_unowned++;
  }
  if (correct_money_unowned == SPECIES_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating owned money tiles" << endl;
  unsigned int correct_money_owned = 0;
  for (unsigned int i = 0; i < SPECIES_COUNT; i++) {
    unsigned int money = i + 1;
    unsigned int owner = (1 + i) % 3;
    Tile tile = tileCreate(GENUS_MONEY, money);
    if (checkTile(tile, GENUS_MONEY, money, false)) {
      tileSetOwner(tile, owner);
      bool correct = checkTile(tile, GENUS_MONEY, money, owner);
      if (correct)
        correct_money_owned++;
    } else
      cout << "* Skipped: Didn't try setting owner for $" << money
           << " money tile" << endl;
  }
  if (correct_money_owned == SPECIES_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating unowned dice tiles" << endl;
  unsigned int correct_dice_unowned = 0;
  for (unsigned int i = 0; i < SPECIES_COUNT; i++) {
    unsigned int dice = i + 1;
    unsigned int owner = (1 + i) % 3;
    Tile tile = tileCreate(GENUS_DICE, dice);
    bool correct = checkTile(tile, GENUS_DICE, dice, true);
    if (correct)
      correct_dice_unowned++;
  }
  if (correct_dice_unowned == SPECIES_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating owned dice tiles" << endl;
  unsigned int correct_dice_owned = 0;
  for (unsigned int i = 0; i < SPECIES_COUNT; i++) {
    unsigned int dice = i + 1;
    unsigned int owner = (1 + i) % 3;
    Tile tile = tileCreate(GENUS_DICE, dice);
    if (checkTile(tile, GENUS_DICE, dice, false)) {
      tileSetOwner(tile, owner);
      bool correct = checkTile(tile, GENUS_DICE, dice, owner);
      if (correct)
        correct_dice_owned++;
    } else
      cout << "* Skipped: Didn't try setting owner for $" << dice
           << " dice tile" << endl;
  }
  if (correct_dice_owned == SPECIES_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating unowned points tiles" << endl;
  unsigned int correct_points_unowned = 0;
  for (unsigned int i = 0; i < SPECIES_COUNT; i++) {
    unsigned int points = i + 1;
    unsigned int owner = (1 + i) % 3;
    Tile tile = tileCreate(GENUS_POINTS, points);
    bool correct = checkTile(tile, GENUS_POINTS, points, true);
    if (correct)
      correct_points_unowned++;
  }
  if (correct_points_unowned == SPECIES_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating owned points tiles" << endl;
  unsigned int correct_points_owned = 0;
  for (unsigned int i = 0; i < SPECIES_COUNT; i++) {
    unsigned int points = i + 1;
    unsigned int owner = (1 + i) % 3;
    Tile tile = tileCreate(GENUS_POINTS, points);
    if (checkTile(tile, GENUS_POINTS, points, false)) {
      tileSetOwner(tile, owner);
      bool correct = checkTile(tile, GENUS_POINTS, points, owner);
      if (correct)
        correct_points_owned++;
    } else
      cout << "* Skipped: Didn't try setting owner for $" << points
           << " points tile" << endl;
  }
  if (correct_points_owned == SPECIES_COUNT)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating unowned bomb tile" << endl;
  Tile bomb_tile = tileCreate(GENUS_BOMB, 0);
  bool correct_bomb_unowned = checkTile(bomb_tile, GENUS_BOMB, 0, true);
  if (correct_bomb_unowned)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Creating owned bomb tile" << endl;
  bool correct_bomb_owned = false;
  if (checkTile(bomb_tile, GENUS_BOMB, 0, false)) {
    tileSetOwner(bomb_tile, 2u);
    correct_bomb_owned = checkTile(bomb_tile, GENUS_BOMB, 0, 2u);
  }
  if (correct_bomb_owned)
    cout << "* Correct" << endl;
  cout << endl;

  cout << "Testing printing tiles" << endl;
  unsigned int correct_print = checkPrintTile();
  cout << endl;

  //
  //  Print results
  //

  testHelperPrintSummaryHeader(24, 1, DID_NOT_CRASH_RUNNING_MARKS);
  testHelperPrintSummaryLine("GENUS_COUNT", correct_genus_count);
  testHelperPrintSummaryLine("GENUS_MONEY", correct_genus_money);
  testHelperPrintSummaryLine("GENUS_DICE", correct_genus_dice);
  testHelperPrintSummaryLine("GENUS_POINTS", correct_genus_points);
  testHelperPrintSummaryLine("GENUS_BOMB", correct_genus_bomb);
  testHelperPrintSummaryLine("Money tiles  (unowned)", correct_money_unowned,
                             SPECIES_COUNT);
  testHelperPrintSummaryLine("Money tiles  (  owned)", correct_money_owned,
                             SPECIES_COUNT);
  testHelperPrintSummaryLine("Dice tiles   (unowned)", correct_dice_unowned,
                             SPECIES_COUNT);
  testHelperPrintSummaryLine("Dice tiles   (  owned)", correct_dice_owned,
                             SPECIES_COUNT);
  testHelperPrintSummaryLine("Points tiles (unowned)", correct_points_unowned,
                             SPECIES_COUNT);
  testHelperPrintSummaryLine("Points tiles (  owned)", correct_points_owned,
                             SPECIES_COUNT);
  testHelperPrintSummaryLine("Bomb tiles   (unowned)", correct_bomb_unowned);
  testHelperPrintSummaryLine("Bomb tiles   (  owned)", correct_bomb_owned);
  testHelperPrintSummaryLine("tilePrint", correct_print, PRINT_COUNT);

  unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

  unsigned int genus_correct_number = 0;
  if (correct_genus_money)
    genus_correct_number += 1;
  if (correct_genus_dice)
    genus_correct_number += 1;
  if (correct_genus_points)
    genus_correct_number += 1;
  if (correct_genus_bomb)
    genus_correct_number += 1;

  if (correct_genus_count)
    mark += 1;
  mark += testHelperMarkAnyAll(genus_correct_number, GENUS_COUNT_CORRECT);
  mark += testHelperMarkAnyAll(correct_money_unowned, SPECIES_COUNT);
  mark += testHelperMarkAnyAll(correct_money_owned, SPECIES_COUNT);
  mark += testHelperMarkAnyAll(correct_dice_unowned, SPECIES_COUNT);
  mark += testHelperMarkAnyAll(correct_dice_owned, SPECIES_COUNT);
  mark += testHelperMarkAnyAll(correct_points_unowned, SPECIES_COUNT);
  mark += testHelperMarkAnyAll(correct_points_owned, SPECIES_COUNT);
  if (correct_bomb_unowned)
    mark += 1;
  if (correct_bomb_owned)
    mark += 1;
  mark += correct_print / 2; // max 4

  assert(mark <= TOTAL_MARKS);
  testHelperPrintMark(mark, TOTAL_MARKS);

  testHelperWaitForEnter();
  return 0;
}

bool checkTile(const Tile &tile, unsigned int correct_genus,
               unsigned int correct_species, bool print_messages) {
  if (tileGetGenus(tile) != correct_genus) {
    if (print_messages)
      cout << "* Incorrect: Tile has genus " << tileGetGenus(tile)
           << ", should be " << correct_genus << endl;
    return false;
  }
  if (tileGetSpecies(tile) != correct_species) {
    if (print_messages)
      cout << "* Incorrect: Tile has species " << tileGetSpecies(tile)
           << ", should be " << correct_species << endl;
    return false;
  }
  if (tileIsOwner(tile)) {
    if (print_messages)
      cout << "* Incorrect: Tile has an owner, but shouldn't" << endl;
    return false;
  }

  for (unsigned int i = 0; i < ROLL_PLAYER_COUNT; i++) {
    unsigned int affected = tileGetAffectedPlayer(tile, i);
    if (affected != i) {
      if (print_messages) {
        cout << "* Incorrect: Tile should affects player " << affected << " ("
             << i << " rolled), should be " << i << endl;
      }
      return false;
    }
  }

  // correct will be printed above
  return true;
}

bool checkTile(const Tile &tile, unsigned int correct_genus,
               unsigned int correct_species, unsigned int correct_owner) {
  if (tileGetGenus(tile) != correct_genus) {
    cout << "* Incorrect: Tile has genus " << tileGetGenus(tile)
         << ", should be " << correct_genus << endl;
    return false;
  }
  if (tileGetSpecies(tile) != correct_species) {
    cout << "* Incorrect: Tile has species " << tileGetSpecies(tile)
         << ", should be " << correct_species << endl;
    return false;
  }
  if (!tileIsOwner(tile)) {
    cout << "* Incorrect: Tile doesn't have an owner, but should" << endl;
    return false;
  }

  for (unsigned int i = 0; i < ROLL_PLAYER_COUNT; i++) {
    unsigned int affected = tileGetAffectedPlayer(tile, i);
    if (affected != correct_owner) {
      cout << "* Incorrect: Tile should affects player " << affected << " ("
           << i << " rolled), should be " << correct_owner << endl;
      return false;
    }
  }

  // correct will be printed above
  return true;
}

unsigned int checkPrintTile() {
  static const string PRINTED_CORRECT[PRINT_COUNT] = {
      " $1", "W$2", " *3", "X$4", " *5", "Y$6", " *7", "Z*8"};

  // print "overlines" for rile output
  cout << "         ";
  for (unsigned int i = 0; i < PRINT_COUNT; i++) {
    cout << "  ___";
  }
  cout << endl;

  // print correct tile output
  cout << "Correct: ";
  for (unsigned int i = 0; i < PRINT_COUNT; i++) {
    cout << "  " << PRINTED_CORRECT[i];
  }
  cout << endl;

  // print tile output from program
  cout << "Results: ";
  string printed[PRINT_COUNT];
  for (unsigned int i = 0; i < PRINT_COUNT; i++) {
    unsigned int species = i + 1;
    Tile tile = tileCreate(PRINT_GENUS[i], species);
    if (i % 2 != 0)
      tileSetOwner(tile, i / 2);

    cout << "  ";
    testHelperStartCapture();
    tilePrint(tile);
    printed[i] = testHelperEndCapture();
  }
  cout << endl;

  // check tile output
  unsigned int correct_count = 0;
  for (unsigned int i = 0; i < PRINT_COUNT; i++) {
    if (printed[i] == PRINTED_CORRECT[i])
      correct_count++;
  }

  // print result
  if (correct_count == 0)
    cout << "* Incorrect: All tiles were printed incorrectly" << endl;
  else if (correct_count < PRINT_COUNT)
    cout << "* Incorrect: Some tiles were printed incorrectly" << endl;
  else
    cout << "* Correct" << endl;
  return correct_count;
}
