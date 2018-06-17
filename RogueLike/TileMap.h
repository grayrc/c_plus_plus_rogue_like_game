#pragma once
#include "TileSet.h"
//#define offset Point(10, 40)

using namespace System::IO;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class TileMap
{
private:
	TileSet^ tileSet;
	array<int, 2>^ map;
	Graphics^ canvas;
	Random^ rGen;
	int nCols;
	int nRows;

public:

	property int TileSize;
	property array<bool, 2>^ VisibleTiles;

	TileMap(TileSet^ startTileSet, Graphics^ startCanvas, Random^ startRGen, int startNCols, int startNRows);

	//Place value tileIndex at location row, col of the 2D map
	void SetMapEntry(int row, int col, int tileIndex);

	//Return the integer value (a tile index) at location row, col of the map
	int GetMapEntry(int row, int col);

	//Draw the map to canvas
	void DrawMap();

	//generate a random map
	void GenerateRandomMap();

	//Load the contents of the map array from a file
	void LoadMapFromFile(String^ mapFileName);

	//sets map from given 2d array of ints
	void SetMapFromArray(array<int, 2>^ mapArray);

	//The viewport calls this method to get the Bitmap it needs to draw itself
	Bitmap^ GetMapCellBitmap(int worldRow, int worldColumn);

	//returns whether tile at given column/row is walkable
	bool isTileWalkable(int row, int col);

	//set all visibleTiles values to false
	void ResetVisibleTiles();

};

