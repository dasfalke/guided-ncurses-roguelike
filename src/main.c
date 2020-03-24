#include "rogue.h"

int main(void)
{
   srand(time(NULL));   // Seed the pseudo-random number generator

   Level *level;
   Player *player;
   Coordinate destination; /* Note: tutorial uses a pointer here */
   int input;

   ScreenSetup();

   level = CreateLevel(1);

   player = PlayerSetup();

   /* *** Main Game Loop *** */
   while ((input = getch()) != 'q')
   {
      destination = HandleInput(player, input); 
      CheckDestination(player, level->tiles, destination);
   }

   /* Free memory */
   DestroyPlayer(player);

   endwin();                  // terminate ncurses

   return 0;
}

/* Utility function for allocating memory on the heap. */
void *SafeMalloc(size_t size)
{
   void *vp;

   if ((vp = malloc(size)) == NULL)
   {
      fputs("malloc failure\n", stderr);
      exit(EXIT_FAILURE);
   }

   return vp;
}

/* Prepares the ncurses screen. */
void ScreenSetup(void)
{
   initscr();                 // initializes screen
   noecho();                  // Prevents keystrokes from displaying
   refresh();                 // Draw to screen
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


