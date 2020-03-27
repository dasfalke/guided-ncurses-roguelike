#include "rogue.h"

/* Creates a new player. */
Player *PlayerSetup(void)
{
   Player *player = (Player *)SafeMalloc(sizeof(Player));

   player->health = 20;
   player->maxHealth = 20;
   player->attack = 1;
   player->gold = 0;
   player->xp = 0;

   player->numberOfItems = 0;
   player->items = (Item **)SafeMalloc(sizeof(Item *) * MAX_ITEMS);

   // Grant player starting weapon
   player->items[player->numberOfItems] = CreateSword(1, 20);
   player->numberOfItems++;

   return player;
}

void PlacePlayer(Room **rooms, Player *player)
{
   player->location.y = rooms[3]->origin.y + 1; /* Starting position is hard coded for the time being. */
   player->location.x = rooms[3]->origin.x + 1; 
}

/* Frees player memory. */
void DestroyPlayer(Player *player)
{
   if (player)
   {
      free(player);
   }
}

/* Moves player character. */
void PlayerMove(Player *player, char **tiles, Coordinate destination)
{
   player->location.y = destination.y;  // update player's internal position state
   player->location.x = destination.x;
}

/* Checks destination tile and processes move. */
void CheckDestination(Level *level, Coordinate destination)
{
   switch (mvinch(destination.y, destination.x))   // mvinch returns character at (y,x)
   {
      case '.':
      case '+':
      case '#':
         PlayerMove(level->player, level->tiles, destination);
         break;
      case 'X':
      case 'G':
      case 'T':
         Combat(level->player, GetMonsterAt(&destination, level->monsters), PLAYER);
      default:
         break;
   }
}

void DrawPlayer(Player *player)
{
   mvprintw(player->location.y, player->location.x, "@");
   move(player->location.y, player->location.x);
}
