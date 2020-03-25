#include "rogue.h"

void Combat(Player *player, Monster *monster, AttackOrder order)
{
   /* Player attacking */
   if (order == PLAYER)
   {
      monster->health -= player->attack;

      if (monster->health > 0)
      {
         player->health -= monster->attack;
      }
      else 
      {
         KillMonster(monster);
      }
   }
   /* Monster attacking */
   else 
   {
      player->health -= monster->attack;

      if (player->health > 0)
      {
         monster->health -= player->attack;
      }
   }
}
