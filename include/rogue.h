#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "utils.h"

#define NUM_OF_ROOMS 6
#define MAX_MONSTERS_PER_LEVEL 6
#define SCREEN_HEIGHT 24   /* Hardcoded for now. */
#define SCREEN_WIDTH 80    /* Hardcoded for now. */

typedef struct Level
{
   int id;
   char **tiles;
   int numberOfRooms;
   struct Room **rooms;
   struct Monster **monsters;
   int numberOfMonsters;
   struct Player *player;
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

typedef enum Pathing 
{
   RANDOM,
   SEEKING
} Pathing;

typedef struct Player
{
   Coordinate location;
   int health;
   int maxHealth;
   int attack;
   int gold;
   int xp;
} Player;

typedef struct Monster
{
   char string[2];
   char symbol;
   int health;
   int alive;
   int attack;
   int speed;
   int defense;
   Pathing pathfinding;
   Coordinate location;
} Monster;

typedef enum Bestiary 
{
   SPIDER,
   GOBLIN,
   TROLL
} Bestiary;

typedef enum Direction 
{
   NORTH,
   WEST,
   SOUTH,
   EAST
} Direction;

typedef enum AttackOrder 
{
   MONSTER,
   PLAYER
} AttackOrder;



void *SafeMalloc(size_t size);
void ScreenSetup(void);
Level *CreateLevel(int id);
Room **RoomSetup(void);
char **SaveLevelPositions(void);
Player *PlayerSetup(void);
void PlacePlayer(Room **rooms, Player *player);
void DestryPlayer(Player *player);
void DestroyPlayer(Player *player);
Coordinate HandleInput(Player *player, int input);
void PlayerMove(Player *player, char **tiles, Coordinate destination);
void CheckDestination(Level *level, Coordinate destination);
Room *CreateRoom(int grid);
void DrawRoom(Room *room);
void DestroyRooms(Room **rooms);
void ConnectDoors(Coordinate *doorOne, Coordinate *doorTwo);
void AddMonster(Level *level);
Monster *SelectMonster(int levelId);
Monster *CreateMonster(char symbol, int health, int attack, int speed, int defense, Pathing pathfinding);
void SetStartingPosition(Monster *monster, Room *room);
void PathingRandom(Coordinate *start);
void PathingSeek(Coordinate *destination, Coordinate *start);
void MoveMonsters(Level *level);
void Combat(Player *player, Monster *monster, AttackOrder order);
Monster *GetMonsterAt(Coordinate *location, Monster **monsters);
void KillMonster(Monster *monster);
void PrintGameHUD(Level *level);

void Pathfind(Coordinate *end, Coordinate *start);

#endif /* ROGUE_H */
