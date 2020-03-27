#ifndef ROGUE_H
#define ROGUE_H

//#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "mainmenu.h"

#define NUM_OF_ROOMS 6
#define MAX_MONSTERS_PER_LEVEL 6
#define SCREEN_HEIGHT 24   /* Hardcoded for now. */
#define SCREEN_WIDTH 80    /* Hardcoded for now. */
#define MAX_ITEMS 25

/* See episode 25 for info on reorganizing this file. */

typedef struct Game
{
   struct Level *levels[10];   /* hardcoded level count for now */
   int currentLevel;
} Game;

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
   struct Door **doors;
   int numberOfDoors;
} Room;

typedef struct Door
{
   Coordinate location;
   int connected;
} Door;

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
   struct Item **items;
   int numberOfItems;
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

typedef enum 
{
   WEAPON_TYPE, 
   POTION_TYPE
} ItemType;

typedef struct Item
{
   ItemType type;
   Coordinate location;

   union
   {
      struct Weapon *weapon;
      //Potion *poition;
   } item;

   char string[256];
} Item;

typedef enum 
{
   SWORD_TYPE,
   SPEAR_TYPE
} WeaponType;

typedef struct Weapon
{
   WeaponType type;
   int attack;
   int durability;
} Weapon;

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
Room *CreateRoom(int grid, int numberOfDoors);
void DrawRoom(Room *room);
void DestroyRooms(Room **rooms);
void ConnectDoors(Level *level);
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
void DrawLevel(Level *level);
void DrawMonster(Monster *monster);
void DrawPlayer(Player *player);
int GameLoop(Game *game);
void Pathfind(Coordinate *end, Coordinate *start);
Item *CreateSword(int attack, int durability);
void PrintInventory(Player *player);

#endif /* ROGUE_H */
