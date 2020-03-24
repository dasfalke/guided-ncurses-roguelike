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
         return CreateMonster('X', 2, 1, 1, 1, 1);
      case GOBLIN:
         return CreateMonster('G', 5, 3, 1, 1, 2);
      case TROLL:
         return CreateMonster('T', 15, 5, 1, 1, 1);
      default:
         fputs("Monster init failed.\n", stderr);
         exit(EXIT_FAILURE);
         break;
   }
}

/* Initialize a monster. */
Monster *CreateMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding)
{
   Monster *monster = (Monster *)SafeMalloc(sizeof(Monster));

   monster->symbol = symbol;
   monster->health = health;
   monster->attack = attack;
   monster->speed = speed;
   monster->defense = defense;
   monster->pathfinding = pathfinding;

   return monster;
}

void SetStartingPosition(Monster *monster, Room *room)
{
   monster->location.y = (rand() % (room->height - 2)) + room->origin.y + 1;
   monster->location.x = (rand() % (room->width - 2)) + room->origin.x + 1;

   char symbol[8];
   sprintf(symbol, "%c", monster->symbol);
   mvprintw(monster->location.y, monster->location.x, symbol);
}
