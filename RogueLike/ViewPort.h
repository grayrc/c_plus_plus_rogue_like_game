#pragma once
#include "TileMap.h"
#include "NPCSprite.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class ViewPort
{
private:
	int tilesWide; //how many tiles wide the viewport is
	int tilesHigh;  //how many tiles high the viewport is
	int tileSize; //pixels of tile
	//width and height of screen in pixels
	int screenHeight;
	int screenWidth;


	TileMap^ backgroundMap;
	Graphics^ canvas;
	Bitmap^ blank;


public:
	property Point ViewportWorld; //where on map viewport is


public:
	ViewPort(Graphics^ startCanvas, 
		TileMap^ startBackgroundMap, 
		Point startPoint, 
		int startTilesWide, 
		int startTilesHigh, 
		int startScreenWidth, 
		int startScreenHeight);

	void CentreOnSprite(NPCSprite^ centerSprite);
	void ViewportDraw();
};

