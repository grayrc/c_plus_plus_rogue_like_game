#pragma once

#include "Dungeon.h"
#include "ViewPort.h"
#include "SpriteParent.h"
#include "NPCSpriteList.h"
#include "ObjectSpriteList.h"
#include "ObjectSprite.h"
#include "FireballSprite.h"
#include "EnumClass.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

ref class GameEngine
{

private:

	Graphics^ canvas;
	Bitmap^ offScreenBitmap;
	Graphics^ offScreenCanvas;
	Random^ RGen;
	Dungeon^ dungeon;
	TileSet^ tileSet;
	TileMap^ tileMap;
	ViewPort^ viewPort;
	array<String^>^ tileArray;
	int width;
	int height;
	//current map, created by dungeon
	array<int, 2>^ map;
	int cols = WORLDCOL; //map width in tiles
	int rows = WORLDROW; //map height in tiles
	int nTiles = 7; //number of tiles
	int tileSize; //size of tiles
	NPCSprite^ player;
	NPCSpriteList^ rats;
	FireballSprite^ fireball;
	NPCSprite^ target;
	NPCSprite^ fireballedSprite;
	int level;
	int gold;
	int nRats;

	array<bool, 2>^ visibleTiles;

public:
	GameEngine(Graphics^ startCanvas, Random^ startRGen, int startWidth, int startHeight);

	void Run();
	void UpdateDirection(int direction);
	void NewLevel();
	String^ GetHealth();
	String^ GetEvent();
	String^ GetEvent2();
	String^ GetLevel();
	String^ GetGold();
	bool PlayerAlive();
	bool rangeAttackMode;


private:

	bool fighting;
	int fightCounter;
	bool playersTurn;
	array<String^>^ createTileArray();

	//creates player sprite with given number of sprite sheets with given frames per sheet
	NPCSprite^ createPlayer();

	FireballSprite^ createFireball();

	NPCSpriteList^ createEnemies();

	Point getPositionInRoom(Room^ room);

	array<String^>^ createRatSpriteArray();

	array<String^>^ createCrabSpriteArray();

	array<String^>^ createGnollSpriteArray();

	void fightMode(NPCSprite^ enemy);

	String^ whatsHappening;

	String^ fightEvent;

	ObjectSprite^ stairs;

	ObjectSprite^ createStairs();

	Room^ playerRoom;

	ObjectSpriteList^ objects;

	ObjectSpriteList^ createObjects();



};

