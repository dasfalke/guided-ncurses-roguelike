#include "rogue.h"

Item *CreateSword(int attack, int durability)
{
   Item *item = (Item *)SafeMalloc(sizeof(Item));
   item->type = WEAPON_TYPE;
   strcpy(item->string, "Sword");
   item->item.weapon = (Weapon *)SafeMalloc(sizeof(Weapon));

   item->item.weapon->attack = attack;
   item->item.weapon->durability = durability;

   return item;
}
