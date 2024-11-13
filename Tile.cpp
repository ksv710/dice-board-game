#include <iostream>
#include "Tile.h"
#include "Player.h"
using namespace std;

const unsigned int NO_OWNER = 100000000;

 Tile tileCreate (unsigned int genus1, unsigned int species1)
 {
   Tile x;
   assert (genus1 < GENUS_COUNT);
   x.genus = genus1;
   x.species = species1;
   x.owner = NO_OWNER;
   return x;
 }
 bool tileIsOwner (const Tile& tile)
 {
   if (tile.owner == NO_OWNER)
     return 0;
   else 
     return 1;
 }

 void tileSetOwner (Tile& tile, unsigned int owner1)
 {
   tile.owner = owner1;
 }

 unsigned int tileGetGenus (const Tile& tile)
 {
   return tile.genus;
 }

 unsigned int tileGetSpecies (const Tile& tile)
 {
   return tile.species;
 }

 unsigned int tileGetAffectedPlayer (const Tile& tile, unsigned int whose_turn)
 {
   if (tileIsOwner (tile) == 1)
   return tile.owner;
   else 
   return whose_turn;
 }

void tilePrintOwnerChar (const Tile& tile)
{
if (tileIsOwner (tile) == 0)
cout << " ";
else 
{
char s = playerGetTileChar (tile.owner);
cout << s;
}
}

void tilePrintGenusChar (const Tile& tile)
{
if (tile.genus == GENUS_MONEY)
cout << "$";
else if (tile.genus == GENUS_POINTS)
cout << "*"; 
}

void tilePrintSpeciesChar (const Tile& tile)
{
  cout << tile.species;
}

void tilePrint (const Tile& tile)
{
  tilePrintOwnerChar (tile);
  tilePrintGenusChar (tile);
  tilePrintSpeciesChar (tile);

}

void tileActivate (const Tile& tile, unsigned int whose_turn)
{
  int o = tileGetAffectedPlayer (tile, whose_turn);

  if(tile.genus == GENUS_MONEY)
  {
     playerIncreaseMoneyAndPrint (o, tile.species);
  }
else if(tile.genus == GENUS_POINTS)
  {
    playerIncreasePointsAndPrint (o, tile.species);
  }
}

 