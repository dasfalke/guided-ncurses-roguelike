#include "rogue.h"
#include "utils.h"

void AddPositionYX(int **frontier, int y, int x, int count)
{
   frontier[count][0] = y;
   frontier[count][1] = x;
}

int CheckPosition(int y, int x)
{
   char temp = mvinch(y, x);
   return (temp != '.' && temp != '|' && temp != '-');
}

int AddNeighbors(int **frontier, int ***cameFrom, int count, int y, int x)
{
   /* North neighbor */
   if (y > 0 && cameFrom[y - 1][x][0] < 0 && CheckPosition(y - 1, x)) 
   {
      AddPositionYX(frontier, y - 1, x, count);
      cameFrom[y - 1][x][0] = y;
      cameFrom[y - 1][x][1] = x;
      ++count;
   }
   /* South neighbor */
   if (y < SCREEN_HEIGHT - 1 && cameFrom[y + 1][x][0] < 0 && CheckPosition(y + 1, x)) 
   {
      AddPositionYX(frontier, y + 1, x, count);
      cameFrom[y + 1][x][0] = y;
      cameFrom[y + 1][x][1] = x;
      ++count;
   }
   /* East neighbor */
   if (x < SCREEN_WIDTH - 1 && cameFrom[y][x + 1][0] < 0 && CheckPosition(y, x + 1)) 
   {
      AddPositionYX(frontier, y, x + 1, count);
      cameFrom[y][x + 1][0] = y;
      cameFrom[y][x + 1][1] = x;
      ++count;
   }
   /* West neighbor */
   if (x > 0 && cameFrom[y][x - 1][0] < 0 && CheckPosition(y, x - 1)) 
   {
      AddPositionYX(frontier, y, x - 1, count);
      cameFrom[y][x - 1][0] = y;
      cameFrom[y][x - 1][1] = x;
      ++count;
   }

   return count;
}

void Pathfind(Coordinate *end, Coordinate *start)
{
   /* Prepare memory for algorithm */
   int **frontier = (int **)SafeMalloc(sizeof(int *) * SCREEN_HEIGHT * SCREEN_WIDTH);
   int ***cameFrom = (int ***)SafeMalloc(sizeof(int **) * SCREEN_HEIGHT);

   int x, y;
   int frontierIndex;
   int frontierCount;

   for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; ++i)
   {
      frontier[i] = (int *)SafeMalloc(sizeof(int) * 2);
   }

   for (int i = 0; i < SCREEN_HEIGHT; ++i)
   {
      cameFrom[i] = (int **)SafeMalloc(sizeof(int *) * SCREEN_WIDTH);

      for (int j = 0; j < SCREEN_WIDTH; ++j)
      {
         cameFrom[i][j] = (int *)SafeMalloc(sizeof(int) * 2);
         cameFrom[i][j][0] = -1;
         cameFrom[i][j][1] = -1;
      }
   }

   /* Intialize starting conditions */
   frontierIndex = 0;
   frontierCount = 0;

   cameFrom[start->y][start->x][0] = -9;  /* Flags for origin */
   cameFrom[start->y][start->x][1] = -9;

   AddPositionYX(frontier, start->y, start->x, frontierCount); 
   frontierCount++;

   /* Search for end location. */
   while (frontierIndex < frontierCount)
   {
      y = frontier[frontierIndex][0];
      x = frontier[frontierIndex][1];
      ++frontierIndex;

      if (y == end->y && x == end->x)
      {
         break;
      }

      frontierCount = AddNeighbors(frontier, cameFrom, frontierCount, y, x);
   }

   /* Reverse traverse */
   y = end->y;
   x = end->x;

   while (y != start->y || x != start->x)
   {
      int tempY = y;
      y = cameFrom[tempY][x][0];
      x = cameFrom[tempY][x][1];
      mvprintw(y, x, "+");
   }

}
