#include "rogue.h"


void MenuLoop()
{
   int choice;
   char *choices[] = {"Start Game", "End Game"};

   Game game;
   game.currentLevel = 0;

   while (1)
   {
      choice = MainMenu(2, choices);

      switch (choice)
      {
         case START_GAME:
            GameLoop(&game);
            clear(); 
            break;
         case QUIT_GAME:
            return;
      } 
   }
}


int main(void)
{
   srand(time(NULL));   // Seed the pseudo-random number generator

   ScreenSetup();
   MenuLoop();
   endwin();                  // terminate ncurses

   return 0;
}

/* Handles user input. */
Coordinate HandleInput(Player *player, int input)
{
   Coordinate destination;    // Note: Tutorial shows this on the heap for some reason

   switch (input)
   {
      case 'w':
      case 'W':
         destination.y = player->location.y - 1;
         destination.x = player->location.x;
         break;
      case 'a':
      case 'A':
         destination.y = player->location.y;
         destination.x = player->location.x - 1;
         break;
      case 's':
      case 'S':
         destination.y = player->location.y + 1;
         destination.x = player->location.x;
         break;
      case 'd':
      case 'D':
         destination.y = player->location.y;
         destination.x = player->location.x + 1;
         break;
      default:
         destination.y = player->location.y;
         destination.x = player->location.x;
         break;
   }

   return destination;
}


