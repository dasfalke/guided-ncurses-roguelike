#include "rogue.h"

int GameLoop()
{
   Coordinate destination; /* Note: tutorial uses a pointer here */
   int input;
   Level *level;
   level = CreateLevel(1);
   PrintGameHUD(level);


   /* *** Main Game Loop *** */
   while ((input = getch()) != 'q')
   {
      PrintGameHUD(level);
      destination = HandleInput(level->player, input); 
      CheckDestination(level, destination);
      MoveMonsters(level);
      move(level->player->location.y, level->player->location.x);

      if (level->player->health <= 0)
      {
         return -1;
      }
   }

   return 0;
}

void MenuLoop()
{
   int choice;

   while (1)
   {
      char *choices[] = {"Start Game", "End Game"};
      choice = MainMenu(2, choices);

      switch (choice)
      {
         case START_GAME:
            GameLoop();
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


