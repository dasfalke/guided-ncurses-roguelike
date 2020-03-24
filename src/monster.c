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

   mvprintw(monster->location.y, monster->location.x, monster->string);
}

void MoveMonsters(Level *level)
{
   for (int i = 0; i < level->numberOfMonsters; ++i)
   {
      if (level->monsters[i]->pathfinding == RANDOM)
      {

      }
      else
      {
         /* Seeking Pathfinding */
         mvprintw(level->monsters[i]->location.y, level->monsters[i]->location.x, ".");
         PathingSeek(&(level->player->location), &(level->monsters[i]->location));   
         mvprintw(level->monsters[i]->location.y, level->monsters[i]->location.x, level->monsters[i]->string);
      }
   }
}

void PathingSeek(Coordinate *destination, Coordinate *start)
{
   if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && 
         (mvinch(start->y - 1, start->x) == '.'))
   {
      start->y -= 1;
   }

   /* Try to grow left. */
   else if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && 
         (mvinch(start->y, start->x - 1) == '.'))
   {
      start->x -= 1;
   }

   /* Try to grow down. */
   else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && 
         (mvinch(start->y + 1, start->x) == '.'))
   {
      start->y += 1;
   }

   /* Try to grow right. */
   else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && 
         (mvinch(start->y, start->x + 1) == '.'))
   {
      start->x += 1;
   }
}