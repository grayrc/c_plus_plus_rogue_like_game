#include "ViewPort.h"


ViewPort::ViewPort(Graphics ^ startCanvas, 
	TileMap ^ startBackgroundMap, 
	Point startPoint, 
	int startTilesWide, 
	int startTilesHigh, 
	int startScreenWidth, 
	int startScreenHeight)
{
	canvas = startCanvas;
	backgroundMap = startBackgroundMap; //entire map
	//ViewportWorld = startPoint; //point 0, 0 of viewpoint
	//tilesWide = startTilesWide; //number of tiles in width of viewport
	//tilesHigh = startTilesHigh; //n tiles in height of viewport
	tileSize = TILESIZE;// 
	//tileSize = backgroundMap->GetMapCellBitmap(0, 0)->Height; // size of each tile
	screenHeight = startScreenHeight;
	screenWidth = startScreenWidth;
	tilesWide = screenWidth / tileSize + 1;
	tilesHigh = screenHeight / tileSize + 1;

	blank = gcnew Bitmap("assets\\blank.bmp");
}

//sets the top left corner of the viewport to be half the screen width and height up and left of given sprite.
void ViewPort::CentreOnSprite(NPCSprite ^ centerSprite)
{

	int posX = centerSprite->Pos.X - (screenWidth / 2);
	int posY = centerSprite->Pos.Y - (screenHeight / 2);


	ViewportWorld = Point(posX, posY);
}


//draws the tiles in the viewport
void ViewPort::ViewportDraw()
{
	int viewportTileX = ViewportWorld.X / tileSize; //which tile column is at 0, 0 in viewport
	int viewportTileY = ViewportWorld.Y / tileSize; //which tile row is at 0, 0 in viewport
	int offsetX = ViewportWorld.X % tileSize; //how many pixels past the viewport are the leftmost tiles
	int offsetY = ViewportWorld.Y % tileSize; //how many pixels past the viewport are the topmost tiles
	//for each column of tiles in viewport
	for (int c = viewportTileX; c <= (viewportTileX + tilesWide); c++)
	{
		//for each row of tiles in viewpoint
		for (int r = viewportTileY; r <= (viewportTileY + tilesHigh); r++)
		{
			//x and y coordinates of tile to draw are row or column in viewport minus distance from top and left of
			//map in columns times tilesize to get pixel value, then subtract the offset
			int screenX = (((c - viewportTileX) * tileSize) - offsetX);
			int screenY = (((r - viewportTileY) * tileSize) - offsetY);
			Bitmap^ toDraw = backgroundMap->GetMapCellBitmap(r, c); //get image from TileMap who gets it from TileSet
			Rectangle drawRect = Rectangle(screenX, screenY, tileSize, tileSize); //position and size to draw
			//System::Diagnostics::Debug::WriteLine(backgroundMap->VisibleTiles[r, c]);
			if (backgroundMap->VisibleTiles[r, c])
			{
				canvas->DrawImage(toDraw, drawRect);
			}
			else
			{
				canvas->DrawImage(blank, drawRect);
			}


		}
	}
}
