#include "rogue.h"

/*
 * Add monsters to the level.
 */
void AddMonster(Level *level)
{
   /* Number of monsters currently on level. */
   level->numberOfMonsters = 0;

   /* Create a structure for storing monsters. Another dynamic allocation without free'ing...
   */
   level->monsters = (Monster **)SafeMalloc(sizeof(Monster *) * MAX_MONSTERS_PER_LEVEL); 

   /* For each room on the level... */
   for (int i = 0; i < level->numberOfRooms; ++i)
   {
      /* 50% chance to add a monster to a room. */
      if (rand() % 2)
      {
         level->monsters[level->numberOfMonsters] = SelectMonster(level->id);
         SetStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[i]);
         level->numberOfMonsters++;
      }
   }
}

/* Select a level appropriate monster. */
Monster *SelectMonster(int levelId)
{
   Bestiary monster;

   switch (levelId)
   {
      case 1:
      case 2:
      case 3:
         /* Levels 1-3 are home to SPIDERs and GOBLINs. */
         monster = rand() % 2 ? GOBLIN : SPIDER;   
         break;
      case 4:
      case 5:
         /* Levels 4-5 are home to GOBLINs and TROLLs. */
         monster = rand() % 2 ? GOBLIN : TROLL;
         break;
      case 6:
         /* Level 6 is home to TROLLs. */
         monster = TROLL;
         break;
      default:
         fputs("Monster init failed.\n", stderr);
         exit(EXIT_FAILURE);
         break;
   } 

   switch (monster)
   {
      case SPIDER:
         return CreateMonster('X', 2, 1, 1, 1, RANDOM);
      case GOBLIN:
         return CreateMonster('G', 5, 3, 1, 1, SEEKING);
      case TROLL:
         return CreateMonster('T', 15, 5, 1, 1, SEEKING);
      default:
         fputs("Monster init failed.\n", stderr);
         exit(EXIT_FAILURE);
         break;
   }
}

/* Initialize a monster. */
Monster *CreateMonster(char symbol, int health, int attack, int speed, int defense, Pathing pathfinding)
{
   Monster *monster = (Monster *)SafeMalloc(sizeof(Monster));

   monster->symbol = symbol;
   monster->health = health;
   monster->alive = 1;
   monster->attack = attack;
   monster->speed = speed;
   monster->defense = defense;
   monster->pathfinding = pathfinding;

   sprintf(monster->string, "%c", symbol);

   return monster;
}

void SetStartingPosition(Monster *monster, Room *room)
{
   monster->location.y = (rand() % (room->height - 2)) + room->origin.y + 1;
   monster->location.x = (rand() % (room->width - 2)) + room->origin.x + 1;
}

void MoveMonsters(Level *level)
{
   for (int i = 0; i < level->numberOfMonsters; ++i)
   {
      /* Dead monsters don't get to participate */
      if (!level->monsters[i]->alive)
      {
         continue;
      }

      if (level->monsters[i]->pathfinding == RANDOM)
      {
         PathingRandom(&level->monsters[i]->location);
      }
      else
      {
         PathingSeek(&level->player->location, &level->monsters[i]->location);   
      }
   }
}

void PathingRandom(Coordinate *start)
{
   Direction random = rand() % 5; /* Cardinal directions plus not moving. */

   switch (random)
   {
      case NORTH:
         if (mvinch(start->y - 1, start->x) == '.')
         {
            start->y -= 1;
         }
         break;
      case WEST:
         if (mvinch(start->y, start->x - 1) == '.')
         {
            start->x -= 1;
         }
         break;
      case SOUTH:
         if (mvinch(start->y + 1, start->x) == '.')
         {
            start->y += 1;
         }
         break;
      case EAST:
         if (mvinch(start->y, start->x + 1) == '.')
         {
            start->x += 1;
         }
         break;
      default:
         break;
   }
}

void PathingSeek(Coordinate *target, Coordinate *start)
{
   if ((abs((start->y - 1) - target->y) < abs(start->y - target->y)) && 
         (mvinch(start->y - 1, start->x) == '.'))
   {
      start->y -= 1;
   }

   /* Try to grow left. */
   else if ((abs((start->x - 1) - target->x) < abs(start->x - target->x)) && 
         (mvinch(start->y, start->x - 1) == '.'))
   {
      start->x -= 1;
   }

   /* Try to grow down. */
   else if ((abs((start->y + 1) - target->y) < abs(start->y - target->y)) && 
         (mvinch(start->y + 1, start->x) == '.'))
   {
      start->y += 1;
   }

   /* Try to grow right. */
   else if ((abs((start->x + 1) - target->x) < abs(start->x - target->x)) && 
         (mvinch(start->y, start->x + 1) == '.'))
   {
      start->x += 1;
   }
}

Monster *GetMonsterAt(Coordinate *location, Monster **monsters)
{
   for (int i = 0; i < MAX_MONSTERS_PER_LEVEL; ++i)
   {
      if (location->y == monsters[i]->location.y && location->x == monsters[i]->location.x)
      {
         return monsters[i];
      }
   }

   fputs("Failed to find monster\n", stderr);
   exit(EXIT_FAILURE);
}

void KillMonster(Monster *monster)
{
   monster->alive = 0;
}

void DrawMonster(Monster *monster)
{
   if (monster->alive)
   {
      mvprintw(monster->location.y, monster->location.x, monster->string);
   }
}
