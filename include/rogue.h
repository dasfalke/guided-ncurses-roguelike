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
Player *PlayerSetup(void);
void DestryPlayer(Player *player);
void DestroyPlayer(Player *player);
void HandleInput(int input, Player *player);
void PlayerMove(Player *player, int y, int x);
void CheckDestination(Player *player, int y, int x);
Room *CreateRoom(int y, int x, int height, int width);
void DrawRoom(Room *room);
void DestroyRooms(Room **rooms);
void ConnectDoors(Coordinate *doorOne, Coordinate *doorTwo);

#endif /* ROGUE_H */
