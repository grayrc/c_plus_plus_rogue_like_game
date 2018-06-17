#pragma once
#include "EnumClass.h"
#include "LinkedListRooms.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class Dungeon
{
private:
	// random generator
	Random^ RGen;

	// Total number of cols and rows for Dungeon
	int totalCols;
	int totalRows;

	// Width and Height of viewport
	Point viewPortSize;

	// Total tiles available for dungeon to place rooms
	Point totalTiles;

	

	// Count number of rooms added to 'rooms' linkedlist
	int roomCount;
	int roomAttempts;

public:
	// Dunegon placement offset from corner of total world tiles
	property Point dungeonOffSet;

	// Holds info about all rooms
	property LinkedListRooms^ rooms;

	Dungeon(Random^ startRGen, Point startViewPortSize);
	Point CalculateUseableTiles();
	void MakeDungeonMesurementsOdd();
	Point CalculateDungeonPlacement();
	array<int, 2>^ CreateMap();
	void CreateRoom(array<int, 2>^ newMap);
	void WallOffCorridors(array<int, 2>^ newMap);
	
};

