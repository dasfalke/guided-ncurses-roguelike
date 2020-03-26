#include "rogue.h"

Level *CreateLevel(int id)
{
   Level *level = (Level *)SafeMalloc(sizeof(Level));

   level->id = id;
   level->numberOfRooms = NUM_OF_ROOMS; 
   level->rooms = RoomSetup();
   ConnectDoors(level);
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
      rooms[i] = CreateRoom(i, 4);
      DrawRoom(rooms[i]);
   }

   //Pathfind(&rooms[3]->doors[0]->location, &rooms[1]->doors[2]->location);
   //ConnectDoors(&rooms[2]->doors[1], &rooms[0]->doors[3]);
   //ConnectDoors(&rooms[0]->doors[0], &rooms[1]->doors[2]);

   return rooms;
}

void ConnectDoors(Level *level)
{
   int randomRoom, randomDoor, count;

   for (int i = 0; i < level->numberOfRooms; ++i)
   {
      for (int j = 0; j < level->rooms[i]->numberOfDoors; ++j)
      {
         /* If a source door is already connected, skip it.*/
         if (level->rooms[i]->doors[j]->connected)
         {
            continue;
         }

         count = 0;

         while (count < 10) /* randomly selected magic number */
         {
            ++count;

            randomRoom = rand() % level->numberOfRooms;
            randomDoor = rand() % level->rooms[randomRoom]->numberOfDoors;

            /* Don't connect to an already connected door. Don't connect to the source room. */
            if (level->rooms[randomRoom]->doors[randomDoor]->connected || randomRoom == 1)
            {
               continue;
            }

            Pathfind(&level->rooms[i]->doors[j]->location, &level->rooms[randomRoom]->doors[randomDoor]->location);
            level->rooms[randomRoom]->doors[randomDoor]->connected = 1;
            level->rooms[i]->doors[j]->connected = 1;
            break;

         }
      }
   }
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
