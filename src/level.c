#include "rogue.h"

Level *CreateLevel(int id)
{
   Level *level = (Level *)SafeMalloc(sizeof(Level));

   level->id = id;
   level->numberOfRooms = 3; /* temporary hardcode */
   level->rooms = RoomSetup();
   level->tiles = SaveLevelPositions();

   level->player = PlayerSetup();
   PlacePlayer(level->rooms, level->player);

   AddMonster(level);

   move(level->player->location.y, level->player->location.x);

   return level;
}

/* Creates the map. */
Room **RoomSetup(void)
{
   Room **rooms = (Room **)SafeMalloc(sizeof(Room) * NUM_OF_ROOMS);

   for (int i = 0; i < NUM_OF_ROOMS; ++i)
   {
      rooms[i] = CreateRoom(i);
      DrawRoom(rooms[i]);
   }

   Pathfind(&rooms[3]->doors[0], &rooms[1]->doors[2]);
   //ConnectDoors(&rooms[2]->doors[1], &rooms[0]->doors[3]);
   //ConnectDoors(&rooms[0]->doors[0], &rooms[1]->doors[2]);

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
         positions[y][x] = (char)mvinch(y, x);
      }
   }

   return positions;
}
