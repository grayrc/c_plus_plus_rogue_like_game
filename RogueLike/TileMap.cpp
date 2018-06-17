#include "TileMap.h"

TileMap::TileMap(TileSet^ startTileSet, Graphics^ startCanvas, Random^ startRGen, int startNCols, int startNRows)
{
	tileSet = startTileSet;
	canvas = startCanvas;
	rGen = startRGen;
	nCols = startNCols;
	nRows = startNRows;
	map = gcnew array<int, 2>(nRows, nCols);
	TileSize = tileSet->TileArray[0]->TileBitmap->Width;

	//array mirroring tile map array with booleans indicating wether tile is visible
	//they all start off as false
	VisibleTiles = gcnew array<bool, 2>(nRows, nCols);
	ResetVisibleTiles();
}

//sets tileIndex to map entry at index [row, column]
void TileMap::SetMapEntry(int row, int col, int tileIndex)
{
	map[row, col] = tileIndex;
}

//returns int at map index [row, col]
int TileMap::GetMapEntry(int row, int col)
{
	return map[row, col];
}

void TileMap::DrawMap()
{
	//iterate through rows
	for (int r = 0; r < nRows; r++)
	{
		//iterate through columns
		for (int c = 0; c < nCols; c++)
		{
			//set x coordinate at column number * size of tile + a constant.
			int x = c * TileSize;
			//set y coordinate at row number * size of tile + a constant.
			int y = r * TileSize;
			int tileToDraw = map[r, c];
			tileSet->TileArray[tileToDraw]->Draw(Point(x, y));

		}
	}
}

//generate a random map
void TileMap::GenerateRandomMap()
{
	//iterate through rows
	for (int r = 0; r < nRows; r++)
	{
		//iterate through columns
		for (int c = 0; c < nCols; c++)
		{
			//pick random tile index
			int nTile = rGen->Next(tileSet->TileArray->Length);
			//set map index random value
			SetMapEntry(r, c, nTile);
		}
	}
}


void TileMap::LoadMapFromFile(String ^ mapFileName)
{
	StreamReader^ sr = File::OpenText(mapFileName);

	//String to hold each line from file
	String^ currentLine;

	//array of strings created by splitting each line on comma. ie. each tile number
	array<String^>^ indexHolder = gcnew array<String^>(nCols);

	//which row of map currently on
	int rowCounter = 0;

	//loop through each line in file
	while (currentLine = sr->ReadLine())
	{
		indexHolder = currentLine->Split(',');

		//loop through each number in a line
		for(int c = 0; c < indexHolder->Length; c++)
		{
			//convert string to integer
			int tileIndex = Convert::ToInt16(indexHolder[c]);
			//set map at index, to number from file
			SetMapEntry(rowCounter, c, tileIndex);

		}
		//increment row counter
		rowCounter++;
	}
}

//sets map from given 2d array of ints
void TileMap::SetMapFromArray(array<int, 2>^ mapArray)
{
	//iterate through rows
	for (int r = 0; r < nRows; r++)
	{
		//iterate through columns
		for (int c = 0; c < nCols; c++)
		{
			int nTile = mapArray[r, c];
			//set map index random value
			SetMapEntry(r, c, nTile);
		}
	}
}

//The viewport calls this method to get the Bitmap it needs to draw itself
Bitmap ^ TileMap::GetMapCellBitmap(int worldRow, int worldColumn)
{
	//Tile to draw
	int mapValue = map[worldRow, worldColumn];

	//get tile from tileset
	Bitmap^ tileImage = tileSet->GetTileBitmap(mapValue);

	return tileImage;
}

bool TileMap::isTileWalkable(int row, int col)
{
	{
		//get tile index of row/column
		int tileIndex = GetMapEntry(row, col);
		//check if it's walkable.
		bool isWalkable = tileSet->IsTileWalkable(tileIndex);
		return isWalkable;
	}
}

void TileMap::ResetVisibleTiles()
{
	for (int r = 0; r < nRows; r++)
	{
		for (int c = 0; c < nCols; c++)
		{
			VisibleTiles[r, c] = false;
		}
	}
}
