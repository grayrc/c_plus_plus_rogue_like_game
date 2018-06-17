#pragma once
#include "Tile.h"
#include "EnumClass.h"



using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class TileSet
{
private:
	Graphics^ canvas;
	array<Bitmap^>^ bitmapArray;

	int nTiles;

	//takes an string array of bitmap image file names and returns an array of bitmaps
	array<Bitmap^>^ populateBitmapArray(array<String^>^ stringArray);

	//creates array of Tile^
	array<Tile^>^ populateTileArray();

public:
	property array<Tile^>^ TileArray;

	TileSet(Graphics^ startCanvas, array<String^>^ tileStringArray);

	//Returns the bitmap (TileBitmap Property) of the tile at postion tileIndex int the TileList's array of Tile^
	Bitmap^ GetTileBitmap(int tileIndex);

	//used to load up the array of tile^
	//places tileToEnter and location tileIndex of the array
	void SetTileArrayEntry(int tileIndex, Tile^ tileToEnter);

	//ask a tile if it's walkable
	bool IsTileWalkable(int tileIndex);

	//bool IsTileVisible(int tileIndex);

	//void SetVisible(int tileIndex);


};

