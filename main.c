#include <stdlib.h>
#include <ncurses.h>

#define NUM_OF_ROOMS 3

typedef struct Coordinate
{
   int y;
   int x;
} Coordinate;

typedef struct Room
{
   Coordinate origin;
   int height;
   int width;
} Room;

typedef struct Player
{
   Coordinate location;
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

   /* *** Main Game Loop *** */
   while ((input = getch()) != 'q')
   {
      HandleInput(input, player); 
   }

   /* Free memory */
   DestroyRooms(rooms);
   DestroyPlayer(player);

   endwin();                  // terminate ncurses

   return 0;
}

/* Utility function for allocating memory on the heap. */
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

/* Prepares the ncurses screen. */
void ScreenSetup(void)
{
   initscr();                 // initializes screen
   noecho();                  // Prevents keystrokes from displaying
   refresh();                 // Draw to screen
}

/* Creates the map. */
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

/* Creates a single room. */
Room *CreateRoom(int y, int x, int height, int width)
{
   Room *room = (Room *)SafeMalloc(sizeof(Room));

   room->origin.y = y;
   room->origin.x = x;
   room->height = height;
   room->width = width;

   return room;
}

/* Draws the rooms on the screen. */
void DrawRoom(Room *room)
{
   /* Draw top & bottom walls */
   for (int i = room->origin.x; i < room->origin.x + room->width; ++i)
   {
      mvprintw(room->origin.y, i, "-");  // Top wall
      mvprintw(room->origin.y + room->height - 1, i, "-"); //bottom wall
   }

   /* Draw side walls and floors */
   for (int i = room->origin.y + 1; i < room->origin.y + room->height - 1; ++i)
   {
      mvprintw(i, room->origin.x, "|"); // Left wall
      mvprintw(i, room->origin.x + room->width - 1, "|"); // right wall

      for (int j = room->origin.x + 1; j < room->origin.x + room->width - 1; ++j)
      {
         mvprintw(i, j, "."); // Floors
      }
   }

}

/* Frees memory used by room structs. */
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

/* Creates a new player. */
Player *PlayerSetup(void)
{
   Player *player = (Player *)SafeMalloc(sizeof(Player));

   player->location.y = 14;
   player->location.x = 14;
   player->health = 20;

   PlayerMove(player, player->location.y, player->location.x);

   return player;
}

/* Frees player memory. */
void DestroyPlayer(Player *player)
{
   if (player)
   {
      free(player);
   }
}

/* Handles user input. */
void HandleInput(int input, Player *player)
{
   int yDestination;
   int xDestination;

   switch (input)
   {
      case 'w':
      case 'W':
         yDestination = player->location.y - 1;
         xDestination = player->location.x;
         break;
      case 'a':
      case 'A':
         yDestination = player->location.y;
         xDestination = player->location.x - 1;
         break;
      case 's':
      case 'S':
         yDestination = player->location.y + 1;
         xDestination = player->location.x;
         break;
      case 'd':
      case 'D':
         yDestination = player->location.y;
         xDestination = player->location.x + 1;
         break;
      default:
         yDestination = player->location.y;
         xDestination = player->location.x;
         break;
   }

   CheckDestination(player, yDestination, xDestination);
}

/* Moves player character. */
void PlayerMove(Player *player, int y, int x)
{
   mvprintw(player->location.y, player->location.x, ".");  // Redraw floor

   player->location.y = y;  // update player's internal position state
   player->location.x = x;

   mvprintw(player->location.y, player->location.x, "@"); // Redraw player
   move(player->location.y, player->location.x); // Fix cursor
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
         move(player->location.y, player->location.x);  // Fix cursor
         break;
   }
}
