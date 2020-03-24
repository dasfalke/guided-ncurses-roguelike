#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define NUM_OF_ROOMS 3
#define MAX_MONSTERS_PER_LEVEL 6

typedef struct Level
{
   int id;
   char **tiles;
   int numberOfRooms;
   struct Room **rooms;
   struct Monster **monsters;
   int numberOfMonsters;
} Level;

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

typedef struct Monster
{
   char symbol;
   int health;
   int attack;
   int speed;
   int defense;
   int pathfinding;
   Coordinate location;
} Monster;

typedef enum Bestiary {
   SPIDER,
   GOBLIN,
   TROLL
} Bestiary;

void *SafeMalloc(size_t size);
void ScreenSetup(void);
Level *CreateLevel(int id);
Room **RoomSetup(void);
char **SaveLevelPositions(void);
Player *PlayerSetup(void);
void DestryPlayer(Player *player);
void DestroyPlayer(Player *player);
Coordinate HandleInput(Player *player, int input);
void PlayerMove(Player *player, char **tiles, Coordinate destination);
void CheckDestination(Player *player, char **tiles, Coordinate destination);
Room *CreateRoom(int y, int x, int height, int width);
void DrawRoom(Room *room);
void DestroyRooms(Room **rooms);
void ConnectDoors(Coordinate *doorOne, Coordinate *doorTwo);
void AddMonster(Level *level);
Monster *SelectMonster(int levelId);
Monster *CreateMonster(char symbol, int health, int attack, int speed, int defense, int pathfinding);
void SetStartingPosition(Monster *monster, Room *room);


#endif /* ROGUE_H */
