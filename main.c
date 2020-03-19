#include <stdlib.h>
#include <ncurses.h>

typedef struct Player
{
   int xPosition;
   int yPosition;
   int health;
} Player;

void *SafeMalloc(size_t size);
void ScreenSetup(void);
void MapSetup(void);
Player *PlayerSetup(void);
void HandleInput(int input, Player *player);
void PlayerMove(Player *player, int y, int x);
void CheckDestination(Player *player, int y, int x);

int main(void)
{
   Player *player;
   int input;

   ScreenSetup();
   MapSetup();

   player = PlayerSetup();

   while ((input = getch()) != 'q')     // game loop
   {
      HandleInput(input, player); 
   }

   free(player);              // free memory on heap
   endwin();                  // terminate ncurses

   return 0;
}

void *SafeMalloc(size_t size)
{
   void *vp;

   if ((vp = malloc(size)) == NULL)
   {
      fputs("malloc failure\n", stderr);
      exit(EXIT_FAILURE);
   }

   return vp;
}

void ScreenSetup(void)
{
   initscr();                 // initializes screen
   noecho();                  // Prevents keystrokes from displaying
   refresh();                 // Draw to screen
}

void MapSetup(void)
{
   mvprintw(13, 13, "--------");             // Move cursor and print
   mvprintw(14, 13, "|......|");             // Move cursor and print
   mvprintw(15, 13, "|......|");             // Move cursor and print
   mvprintw(16, 13, "|......|");             // Move cursor and print
   mvprintw(17, 13, "|......|");             // Move cursor and print
   mvprintw(18, 13, "--------");             // Move cursor and print

   mvprintw(2, 40, "--------");              // Move cursor and print
   mvprintw(3, 40, "|......|");              // Move cursor and print
   mvprintw(4, 40, "|......|");              // Move cursor and print
   mvprintw(5, 40, "|......|");              // Move cursor and print
   mvprintw(6, 40, "|......|");              // Move cursor and print
   mvprintw(7, 40, "--------");              // Move cursor and print

   mvprintw(10, 40, "----------");           // Move cursor and print
   mvprintw(11, 40, "|........|");           // Move cursor and print
   mvprintw(12, 40, "|........|");           // Move cursor and print
   mvprintw(13, 40, "|........|");           // Move cursor and print
   mvprintw(14, 40, "|........|");           // Move cursor and print
   mvprintw(15, 40, "----------");           // Move cursor and print
}

Player *PlayerSetup(void)
{
   Player *player = (Player *)SafeMalloc(sizeof(Player));

   player->xPosition = 14;
   player->yPosition = 14;
   player->health = 20;

   PlayerMove(player, player->yPosition, player->xPosition);

   return player;
}

void HandleInput(int input, Player *player)
{
   int yDestination;
   int xDestination;

   switch (input)
   {
      case 'w':
      case 'W':
         yDestination = player->yPosition - 1;
         xDestination = player->xPosition;
         break;
      case 'a':
      case 'A':
         yDestination = player->yPosition;
         xDestination = player->xPosition - 1;
         break;
      case 's':
      case 'S':
         yDestination = player->yPosition + 1;
         xDestination = player->xPosition;
         break;
      case 'd':
      case 'D':
         yDestination = player->yPosition;
         xDestination = player->xPosition + 1;
         break;
      default:
         yDestination = player->yPosition;
         xDestination = player->xPosition;
         break;
   }
   
   CheckDestination(player, yDestination, xDestination);
}

void PlayerMove(Player *player, int y, int x)
{
   mvprintw(player->yPosition, player->xPosition, ".");  // Redraw floor

   player->yPosition = y;  // update player's internal position state
   player->xPosition = x;

   mvprintw(player->yPosition, player->xPosition, "@"); // Redraw player
   move(player->yPosition, player->xPosition); // Fix cursor
}

/* Checks destination tile and processes move. */
void CheckDestination(Player *player, int y, int x)
{
   switch (mvinch(y, x))   // mvinch returns character at (y,x)
   {
      case '.':
         PlayerMove(player, y, x);
         break;
      default:
         move(player->yPosition, player->xPosition);  // Fix cursor
         break;
   }
}
