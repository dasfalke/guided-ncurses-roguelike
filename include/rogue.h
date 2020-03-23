#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

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

   Coordinate doors[4];
} Room;

typedef struct Player
{
   Coordinate location;
   int health;
} Player;

void *SafeMalloc(size_t size);
void ScreenSetup(void);
Room **MapSetup(void);
char **SaveLevelPositions(void);
Player *PlayerSetup(void);
void DestryPlayer(Player *player);
void DestroyPlayer(Player *player);
Coordinate HandleInput(Player *player, int input);
void PlayerMove(Player *player, char **level, Coordinate destination);
void CheckDestination(Player *player, char **level, Coordinate destination);
Room *CreateRoom(int y, int x, int height, int width);
void DrawRoom(Room *room);
void DestroyRooms(Room **rooms);
void ConnectDoors(Coordinate *doorOne, Coordinate *doorTwo);

#endif /* ROGUE_H */
