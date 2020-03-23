#include "rogue.h"

int main(void)
{
   srand(time(NULL));   // Seed the pseudo-random number generator

   Room **rooms;
   Player *player;
   int input;

   ScreenSetup();
   rooms = MapSetup();

   player = PlayerSetup();

   /* *** Main Game Loop *** */
   while ((input = getch()) != 'q')
   {
      HandleInput(input, player); 
   }

   /* Free memory */
   DestroyRooms(rooms);
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

/* Creates the map. */
Room **MapSetup(void)
{
   Room **rooms = (Room **)SafeMalloc(sizeof(Room) * NUM_OF_ROOMS);

   rooms[0] = CreateRoom(13, 13, 6, 8);
   rooms[1] = CreateRoom(2, 40, 6, 8);
   rooms[2] = CreateRoom(10, 40, 6, 12);

   DrawRoom(rooms[0]);
   DrawRoom(rooms[1]);
   DrawRoom(rooms[2]);

   ConnectDoors(&rooms[2]->doors[1], &rooms[0]->doors[3]);
   ConnectDoors(&rooms[0]->doors[0], &rooms[1]->doors[2]);

   return rooms;
}

/* Handles user input. */
void HandleInput(int input, Player *player)
{
   int yDestination;
   int xDestination;

   switch (input)
   {
      case 'w':
      case 'W':
         yDestination = player->location.y - 1;
         xDestination = player->location.x;
         break;
      case 'a':
      case 'A':
         yDestination = player->location.y;
         xDestination = player->location.x - 1;
         break;
      case 's':
      case 'S':
         yDestination = player->location.y + 1;
         xDestination = player->location.x;
         break;
      case 'd':
      case 'D':
         yDestination = player->location.y;
         xDestination = player->location.x + 1;
         break;
      default:
         yDestination = player->location.y;
         xDestination = player->location.x;
         break;
   }

   CheckDestination(player, yDestination, xDestination);
}


