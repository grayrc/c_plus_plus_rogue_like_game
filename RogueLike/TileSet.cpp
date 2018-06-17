#include "TileSet.h"



//takes an string array of bitmap image file names and returns an array of bitmaps
array<Bitmap^>^ TileSet::populateBitmapArray(array<String^>^ stringArray)
{
	array<Bitmap^>^ newBitmapArray = gcnew array<Bitmap^>(nTiles);
	for (int i = 0; i < nTiles; i++)
	{
		Bitmap^ tileBitmap = gcnew Bitmap(stringArray[i]);
		newBitmapArray[i] = tileBitmap;
	}
	return newBitmapArray;
}

//Creates an array of tiles using the bitmapArray images
array<Tile^>^ TileSet::populateTileArray()
{
	array<Tile^>^ newTileArray = gcnew array<Tile^>(nTiles);
	for (int i = 0; i < nTiles; i++)
	{
		//walkable false by default
		bool walkable = false;
		//walkable true if is the grass tile
		if (i == ROOM || i == CORRIDOR || i == DOOROPEN || i == DOOROPENTOP) { walkable = true; }
		Tile^ newTile = gcnew Tile(canvas, bitmapArray[i], walkable);
		newTileArray[i] = newTile;
	}
	return newTileArray;
}

TileSet::TileSet(Graphics^ startCanvas, array<String^>^ tileStringArray)
{
	canvas = startCanvas;
	nTiles = tileStringArray->Length;
	bitmapArray = populateBitmapArray(tileStringArray);
	TileArray = populateTileArray();
}

//Returns the bitmap (TileBitmap Property) of the tile at postion tileIndex int the TileList's array of Tile^
Bitmap ^ TileSet::GetTileBitmap(int tileIndex)
{
	return bitmapArray[tileIndex];
}

//used to load up the array of tile^
//places tileToEnter and location tileIndex of the array
void TileSet::SetTileArrayEntry(int tileIndex, Tile ^ tileToEnter)
{
	TileArray[tileIndex] = tileToEnter;
}

//ask a tile if it's walkable
bool TileSet::IsTileWalkable(int tileIndex)
{
	bool walkable = TileArray[tileIndex]->Walkable;
	return walkable;
}

/*
bool TileSet::IsTileVisible(int tileIndex)
{
	bool visible = TileArray[tileIndex]->Visible;
	return visible;
}

void TileSet::SetVisible(int tileIndex)
{
	TileArray[tileIndex]->Visible = true;
}
*/
