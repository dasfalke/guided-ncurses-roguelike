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

int main(void)
{
   Player *player;
   int input;
   
   ScreenSetup();
   MapSetup();

   player = PlayerSetup();

   while ((input = getch()) != 'q')     // game loop
   {
         
   }

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
   printw("Hello world!");    // prints text to screen
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
   player->health = 0;

   mvprintw(player->yPosition, player->xPosition, "@");  // Draw player
   move(player->yPosition, player->xPosition);  // Reset cursor

   return player;
}
