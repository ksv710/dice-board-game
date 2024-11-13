//
//  Board.h
//
//  A module to represent the game board.
//
#pragma once

#include "BoardSize.h"
#include "Tile.h"

typedef Tile Board[BOARD_SIZE][BOARD_SIZE];

void boardInit (Board board);

const Tile& boardGetAt (const Board board, int row, int column);

void boardSetAt (Board board, int row, int column, const Tile& value, unsigned int owner);

void boardPrint (const Board board);
void boardPrintColumnNameRow ();
void boardPrintBorderRow ();
void boardPrintEmptyRow ();
void boardPrintDataRow (const Board board, int row);