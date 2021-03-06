#include "rogue.h"

/* Prepares the ncurses screen. */
void ScreenSetup(void)
{
   initscr();                 // initializes screen
   noecho();                  // Prevents keystrokes from displaying
   keypad(stdscr, TRUE);      // Gives ncurses access to arrow keys

   refresh();                 // Draw to screen
}

void PrintGameHUD(Level *level)
{
   mvprintw(22, 0, "   Level: %d", level->id);
   printw("   Gold: %d", level->player->gold);
   printw("   HP: %d(%d)", level->player->health, level->player->maxHealth);
   printw("   Attack: %d", level->player->attack);
   printw("   XP: %d", level->player->xp);
   printw("         "); /* Max sure row is fully overwritten on each refresh */
}

void PrintInventory(Player *player)
{
   mvprintw(23, 0, "   Inventory : ");
   
   for (int i = 0; i < player->numberOfItems; ++i)
   {
      printw(player->items[i]->string);
   }
}

