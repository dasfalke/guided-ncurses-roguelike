#include "rogue.h"

/* Creates a single room. */
Room *CreateRoom(int y, int x, int height, int width)
{
   Room *room = (Room *)SafeMalloc(sizeof(Room));

   room->origin.y = y;
   room->origin.x = x;
   room->height = height;
   room->width = width;

   /* Top door */
   room->doors[0].y = room->origin.y;
   room->doors[0].x = rand() % (width - 2)  + room->origin.x + 1; // Remember to compensate for corners

   /* Left door */
   room->doors[1].y = rand() % (height - 2) + room->origin.y + 1;
   room->doors[1].x = room->origin.x;

   /* Bottom door */
   room->doors[2].y = room->origin.y + room->height - 1;
   room->doors[2].x = rand() % (width - 2) + room->origin.x + 1;

   /* Right door */
   room->doors[3].y = rand() % (height - 2) + room->origin.y + 1;
   room->doors[3].x = room->origin.x + room->width - 1;

   return room;
}

/* Draws the rooms on the screen. */
void DrawRoom(Room *room)
{
   /* Draw top & bottom walls */
   for (int i = room->origin.x; i < room->origin.x + room->width; ++i)
   {
      mvprintw(room->origin.y, i, "-");  // Top wall
      mvprintw(room->origin.y + room->height - 1, i, "-"); //bottom wall
   }

   /* Draw side walls and floors */
   for (int i = room->origin.y + 1; i < room->origin.y + room->height - 1; ++i)
   {
      mvprintw(i, room->origin.x, "|"); // Left wall
      mvprintw(i, room->origin.x + room->width - 1, "|"); // right wall

      for (int j = room->origin.x + 1; j < room->origin.x + room->width - 1; ++j)
      {
         mvprintw(i, j, "."); // Floors
      }
   }

   /* Draw the doors */
   mvprintw(room->doors[0].y, room->doors[0].x, "+");
   mvprintw(room->doors[1].y, room->doors[1].x, "+");
   mvprintw(room->doors[2].y, room->doors[2].x, "+");
   mvprintw(room->doors[3].y, room->doors[3].x, "+");

}


void ConnectDoors(Coordinate *doorDest, Coordinate *doorSrc)
{
   /* Temporary end of the hallway as it grows towards its destination. */
   Coordinate hallTail; 
   hallTail.y = doorSrc->y;
   hallTail.x = doorSrc->x;

   /* Remember previous hallway coordinate. Used when needing to step back. */
   Coordinate hallPrevious;
   hallPrevious = hallTail;

   int steppedBack = 0;

   /* Algorithm to grow the hallway. */
   while (1)
   {
      /* Try to grow up. Check if space to up is closer to destination. If
       * it is then check if that space is empty. If it is then grow the hallway. */
      if ((abs((hallTail.y - 1) - doorDest->y) < abs(hallTail.y - doorDest->y)) && 
            (mvinch(hallTail.y - 1, hallTail.x) == ' '))
         {
            hallPrevious.y = hallTail.y;
            hallTail.y -= 1;
         }
      
      /* Try to grow left. */
      else if ((abs((hallTail.x - 1) - doorDest->x) < abs(hallTail.x - doorDest->x)) && 
            (mvinch(hallTail.y, hallTail.x - 1) == ' '))
         {
            hallPrevious.x = hallTail.x;
            hallTail.x -= 1;
         }

      /* Try to grow down. */
      else if ((abs((hallTail.y + 1) - doorDest->y) < abs(hallTail.y - doorDest->y)) && 
            (mvinch(hallTail.y + 1, hallTail.x) == ' '))
         {
            hallPrevious.y = hallTail.y;
            hallTail.y += 1;
         }

      /* Try to grow right. */
      else if ((abs((hallTail.x + 1) - doorDest->x) < abs(hallTail.x - doorDest->x)) && 
            (mvinch(hallTail.y, hallTail.x + 1) == ' '))
         {
            hallPrevious.x = hallTail.x;
            hallTail.x += 1;
         }
      else 
      {
         if (!steppedBack)
         {
            hallTail = hallPrevious;
            steppedBack = 1;
            continue;
         }
         else 
         {
            return;
         }
      }

      mvprintw(hallTail.y, hallTail.x, "#");
   }

}


/* Frees memory used by room structs. */
void DestroyRooms(Room **rooms)
{
   if (rooms)
   {
      for (int i = 0; i < NUM_OF_ROOMS; ++i)
      {
         if (rooms[i])
         {
            free(rooms[i]);
         }
      }

      free(rooms);
   }
}

