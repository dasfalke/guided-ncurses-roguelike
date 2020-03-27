#include "rogue.h"

void render(Game *game)
{
   clear();
   DrawLevel(game->levels[game->currentLevel - 1]);
   PrintGameHUD(game->levels[game->currentLevel - 1]);
}

int GameLoop(Game *game)
{
   Coordinate destination; /* Note: tutorial uses a pointer here */
   int input = '\0';
   Level *level;

   if (game->currentLevel == 0)
   {
      game->levels[game->currentLevel] = CreateLevel(1);
      game->currentLevel++;
   }

   level = game->levels[game->currentLevel - 1];


   /* *** Main Game Loop *** */
   while (1)
   {
      if (input == 'q' || input == 'Q')
      {
         break;
      }

      if (input == 'i' || input == 'I')
      {
         PrintInventory(level->player);
      } 
      else 
      {
         destination = HandleInput(level->player, input); 
         CheckDestination(level, destination);
         MoveMonsters(level);

         render(game);

         if (level->player->health <= 0)
         {
            game->currentLevel = 0;
            return -1;
         }
      }

      input = getch();
   } 
   return 0;
}

