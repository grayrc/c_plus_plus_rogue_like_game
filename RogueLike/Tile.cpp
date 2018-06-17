#include "Tile.h"



Tile::Tile(Graphics^ startCanvas, Bitmap ^ startTileBitmap, bool startWalkable)
{
	TileBitmap = startTileBitmap;
	canvas = startCanvas;
	Walkable = startWalkable;
	
	//each tile starts off invisible
	//Visible = false;
}

void Tile::Draw(Point pos)
{
	//draws tile image at given location
	Rectangle allOfTile = Rectangle(0, 0, TileBitmap->Width, TileBitmap->Height);
	Rectangle posSize = Rectangle(pos.X, pos.Y, TILESIZE, TILESIZE);
	canvas->DrawImage(TileBitmap, posSize, allOfTile, GraphicsUnit::Pixel);
}
