#pragma once

public enum EDirection { EAST, SOUTH, WEST, NORTH };

public enum ESpriteDirection {FACEEAST, FACEWEST};

public enum ETile { BLANK, ROOM, WALL, DOOROPEN, DOORCLOSED, CORRIDOR, DOOROPENTOP };

public enum EObjectTypes {STAIRS, POTIONS, COINS, CHESTS, CAPE};

public enum EEnemyTypes {PLAYER, RAT, CRAB, GNOLL};

//size of world in tiles
const int WORLDROW = 100;
const int WORLDCOL = 150;
//size of each tile in pixels
const int TILESIZE = 32;
const int STOPFALLOFFARRAY = 2; // Just to make sure

//size of sprites
const int SPRITESIZE = 25;

//players starting stats
const int PLAYERIMAGES = 2;
const int PLAYERFRAMES = 8;
const int PLAYERSPEED = 10;
const int PLAYERSTARTHEALTH = 100;
const int PLAYERSTARTATTACK = 20;

//projectile stats
const int FIREBALLMAXDAMAGE = 10;
const int FIREBALLMINDAMAGE = 5;

//number of frames in enemy spritesheet
const int ENEMYFRAMES = 7;

//number of rats on level 1
const int STARTNRATS = 10;
//rats stats
const int RATSPEED = 3;
const int RATHEALTH = 20;
const int RATATTACK = 10;

//crabs stats
const int CRABSPEED = 4;
const int CRABHEALTH = 30;
const int CRABATTACK = 20;

//gnoll stats
const int GNOLLSPEED = 3;
const int GNOLLHEALTH = 40;
const int GNOLLATTACK = 50;

//time in timer ticks a single turn in battle takes
const int BATTLEEVENTTIME = 20;

//number of potions on each level
const int NPOTIONS = 10;
const int POTIONVALUE = 10;

const int NCOINS = 10;
const int COINVALUE = 3;

//number of coins/chests on each level
const int NCHESTS = 2;
const int CHESTVALUE = 10;

const int NUMCAPE = 1;
const int CAPEINCMAXHEALTH = 120;

// Room with and height random number limits for later factoring.
const int MINTILESFAC = 3;
const int MAXTILESFAC = 11;

// Room size in tiles min and max.

const int MINACTUALROOMTILES = 5;
const int MAXACTUALROOMTILES = 21;

// Number of rooms to attempt to create
const int MAXNUMROOMS = 10;
// Number of attempts to place rooms
const int MAXROOMATTEMPTS = 50;

const int NDIRECTIONS = 4;

//how many from the player ( /2 ) the player can see
const int VISIBLETILES = 20;

//distance at which enemies will start chasing the player
const int CHASINGDIST = 400;