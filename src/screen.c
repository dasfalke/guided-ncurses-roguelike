#include "rogue.h"

/* Prepares the ncurses screen. */
void ScreenSetup(void)
{
   initscr();                 // initializes screen
   noecho();                  // Prevents keystrokes from displaying
   refresh();                 // Draw to screen
}

void PrintGameHUD(Level *level)
{
   mvprintw(23, 0, "   Level: %d", level->id);
   printw("   Gold: %d", level->player->gold);
   printw("   HP: %d(%d)", level->player->health, level->player->maxHealth);
   printw("   Attack: %d", level->player->attack);
   printw("   XP: %d", level->player->xp);
   printw("         "); /* Max sure row is fully overwritten on each refresh */
}

