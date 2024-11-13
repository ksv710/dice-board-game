#pragma once

#include <cassert>

struct Tile
{
unsigned int owner;
unsigned int genus;
unsigned int species;
};

const unsigned int GENUS_COUNT = 4;
const unsigned int GENUS_MONEY = 0;
const unsigned int GENUS_DICE = 1;
const unsigned int GENUS_POINTS = 2;
const unsigned int GENUS_BOMB = 3;

 Tile tileCreate (unsigned int genus1, unsigned int species1);
 bool tileIsOwner (const Tile& tile);
 unsigned int tileGetAffectedPlayer (const Tile& tile, unsigned int whose_turn);
 unsigned int tileGetGenus (const Tile& tile);
 unsigned int tileGetSpecies (const Tile& tile);
 void tileSetOwner (Tile& tile, unsigned int owner1);
 void tileActivate (const Tile& tile, unsigned int whose_turn);
 void tilePrint (const Tile& tile);
 void tilePrintOwnerChar (const Tile& tile);
 void tilePrintGenusChar (const Tile& tile);
 void tilePrintSpeciesChar (const Tile& tile);