#include "rogue.h"

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

char **SaveLevelPositions(void)
{
   char **positions = (char **)SafeMalloc(sizeof(char *) * 25);

   /* Magic number 25 is the size of the map */
   for (int y = 0; y < 25; ++y)
   {
      positions[y] = (char *)SafeMalloc(sizeof(char) * 100);
      /* Magic number 100 is the size of the map */
      for (int x = 0; x < 100; ++x)
      {
         positions[y][x] = mvinch(y, x);
      }
   }

   return positions;
}
