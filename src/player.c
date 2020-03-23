#include "rogue.h"

/* Creates a new player. */
Player *PlayerSetup(void)
{
   Player *player = (Player *)SafeMalloc(sizeof(Player));

   player->location.y = 14;
   player->location.x = 14;
   player->health = 20;

   PlayerMove(player, player->location.y, player->location.x);

   return player;
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
void PlayerMove(Player *player, int y, int x)
{
   mvprintw(player->location.y, player->location.x, ".");  // Redraw floor

   player->location.y = y;  // update player's internal position state
   player->location.x = x;

   mvprintw(player->location.y, player->location.x, "@"); // Redraw player
   move(player->location.y, player->location.x); // Fix cursor
}

/* Checks destination tile and processes move. */
void CheckDestination(Player *player, int y, int x)
{
   switch (mvinch(y, x))   // mvinch returns character at (y,x)
   {
      case '.':
      case '+':
      case '#':
         PlayerMove(player, y, x);
         break;
      default:
         move(player->location.y, player->location.x);  // Fix cursor
         break;
   }
}
