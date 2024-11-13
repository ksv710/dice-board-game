//
//  Board.cpp
//

#include "Board.h"

#include <cmath>
#include <iostream>

#include "BoardSize.h"
#include "Tile.h"

using namespace std;



void boardInit (Board board)
{
	for(int r = 0; r < BOARD_SIZE; r++)
	{               
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			int r2 = abs(r - BOARD_SIZE / 2);
			int c2 = abs(c - BOARD_SIZE / 2);

			int larger = r2;
			if(c2 > r2)
				larger = c2;
			int money = 4 - larger;
      board[r][c] = tileCreate (GENUS_MONEY, money);
		}
	}
}

const Tile& boardGetAt (const Board board, int row, int column)
{
	return board[row][column];
}

void boardSetAt (Board board, int row, int column, const Tile& value, unsigned int owner)
{
	board[row][column] = value;
  tileSetOwner (board[row][column], owner);
}

void boardPrint (const Board board)
{
	boardPrintColumnNameRow();
	boardPrintBorderRow();

	for(int r = 0; r < BOARD_SIZE; r++)
	{
		boardPrintEmptyRow();
		boardPrintDataRow(board, r);
	}
	boardPrintEmptyRow();

	boardPrintBorderRow();
	boardPrintColumnNameRow();
}

void boardPrintColumnNameRow ()
{
	cout << "    ";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		char label = getColumnName(c);
		cout << "   " << label << " ";
	}
	cout << endl;
}

void boardPrintBorderRow ()
{
	cout << "   +";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		cout << "-----";
	}
	cout << "--+" << endl;
}

void boardPrintEmptyRow ()
{
	cout << "   |";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		cout << "     ";
	}
	cout << "  |" << endl;
}

void boardPrintDataRow (const Board board, int row)
{
	char label = getRowName(row);
	cout << " " << label << " |";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
    cout << "  ";
    tilePrint (board[row][c]);
	}
	cout << "  | " << label << endl;
}


