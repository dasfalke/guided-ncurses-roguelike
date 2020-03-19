#include <stdlib.h>
#include <ncurses.h>

#define NUM_OF_ROOMS 3

typedef struct Room
{
   int yDimensionOrigin;
   int xDimensionOrigin;
   int heightDimension;
   int widthDimension;
   //Monster **monsters;
   //Item **items;
} Room;

typedef struct Player
{
   int xPosition;
   int yPosition;
   int health;
} Player;

void *SafeMalloc(size_t size);
void ScreenSetup(void);
Room **MapSetup(void);
Player *PlayerSetup(void);
void DestryPlayer(Player *player);
void DestroyPlayer(Player *player);
void HandleInput(int input, Player *player);
void PlayerMove(Player *player, int y, int x);
void CheckDestination(Player *player, int y, int x);

/* Room functions */
Room *CreateRoom(int y, int x, int height, int width);
void DrawRoom(Room *room);
void DestroyRooms(Room **rooms);

int main(void)
{
   Room **rooms;
   Player *player;
   int input;

   ScreenSetup();
   rooms = MapSetup();

   player = PlayerSetup();

   while ((input = getch()) != 'q')     // game loop
   {
      HandleInput(input, player); 
   }

   /* Free memory */
   DestroyRooms(rooms);
   DestroyPlayer(player);

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

Room **MapSetup(void)
{
   Room **rooms = (Room **)SafeMalloc(sizeof(Room) * NUM_OF_ROOMS);

   rooms[0] = CreateRoom(13, 13, 6, 8);
   rooms[1] = CreateRoom(2, 40, 6, 8);
   rooms[2] = CreateRoom(10, 40, 6, 12);

   DrawRoom(rooms[0]);
   DrawRoom(rooms[1]);
   DrawRoom(rooms[2]);

   return rooms;
}

Room *CreateRoom(int y, int x, int height, int width)
{
   Room *room = (Room *)SafeMalloc(sizeof(Room));

   room->yDimensionOrigin = y;
   room->xDimensionOrigin = x;
   room->heightDimension = height;
   room->widthDimension = width;

   return room;
}

void DrawRoom(Room *room)
{
   /* Draw top & bottom walls */
   for (int i = room->xDimensionOrigin; i < room->xDimensionOrigin + room->widthDimension; ++i)
   {
      mvprintw(room->yDimensionOrigin, i, "-");  // Top wall
      mvprintw(room->yDimensionOrigin + room->heightDimension - 1, i, "-"); //bottom wall
   }

   /* Draw side walls and floors */
   for (int i = room->yDimensionOrigin + 1; i < room->yDimensionOrigin + room->heightDimension - 1; ++i)
   {
      mvprintw(i, room->xDimensionOrigin, "|"); // Left wall
      mvprintw(i, room->xDimensionOrigin + room->widthDimension - 1, "|"); // right wall

      for (int j = room->xDimensionOrigin + 1; j < room->xDimensionOrigin + room->widthDimension - 1; ++j)
      {
         mvprintw(i, j, "."); // Floors
      }
   }

}

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

Player *PlayerSetup(void)
{
   Player *player = (Player *)SafeMalloc(sizeof(Player));

   player->xPosition = 14;
   player->yPosition = 14;
   player->health = 20;

   PlayerMove(player, player->yPosition, player->xPosition);

   return player;
}

void DestroyPlayer(Player *player)
{
   if (player)
   {
      free(player);
   }
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
