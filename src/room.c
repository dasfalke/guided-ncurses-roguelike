#include "rogue.h"

#define GRID_RECT_HEIGHT 11
#define GRID_RECT_WIDTH 26
#define MIN_ROOM_HEIGHT 4
#define MIN_ROOM_WIDTH 6
#define MAX_ROOM_VARIABLE_HEIGHT 5
#define MAX_ROOM_VARIABLE_WIDTH 20

/* Creates a single room. */
Room *CreateRoom(int grid)
{
   Room *room = (Room *)SafeMalloc(sizeof(Room));

   switch (grid)
   {
      /* This switch statement breaks the game screen into a 2x3 (row x col) grid. 
       * Upto one room will be generated for each grid square. */
      case 0:
         room->origin.y = 0;
         room->origin.x = 0;
         break;
      case 1:
         room->origin.y = 0;
         room->origin.x = GRID_RECT_WIDTH;
         break;
      case 2:
         room->origin.y = 0;
         room->origin.x = GRID_RECT_WIDTH * 2;
         break;
      case 3:
         room->origin.y = GRID_RECT_HEIGHT;
         room->origin.x = 0;
         break;
      case 4:
         room->origin.y = GRID_RECT_HEIGHT;
         room->origin.x = GRID_RECT_WIDTH;
         break;
      case 5:
         room->origin.y = GRID_RECT_HEIGHT;
         room->origin.x = GRID_RECT_WIDTH * 2;
         break;
   }

   room->height = rand() % MAX_ROOM_VARIABLE_HEIGHT + MIN_ROOM_HEIGHT;   /* Creates a height between 4 and 8 */
   room->width = rand() % MAX_ROOM_VARIABLE_WIDTH + MIN_ROOM_WIDTH;   /* Creates a width between 4 and 23 */

   /* Room origin offset */
   room->origin.y += rand() % (GRID_RECT_HEIGHT - room->height);
   room->origin.x += rand() % (GRID_RECT_WIDTH - room->width);

   /* Top door */
   room->doors[0].y = room->origin.y;
   room->doors[0].x = rand() % (room->width - 2)  + room->origin.x + 1; // Remember to compensate for corners

   /* Left door */
   room->doors[1].y = rand() % (room->height - 2) + room->origin.y + 1;
   room->doors[1].x = room->origin.x;

   /* Bottom door */
   room->doors[2].y = room->origin.y + room->height - 1;
   room->doors[2].x = rand() % (room->width - 2) + room->origin.x + 1;

   /* Right door */
   room->doors[3].y = rand() % (room->height - 2) + room->origin.y + 1;
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

