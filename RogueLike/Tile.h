#pragma once
#include "EnumClass.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class Tile
{
	Graphics^ canvas;
public:
	Tile(Graphics^ startCanvas, Bitmap^ startTileBitmap, bool startWalkable);

	//draws TileBitmap at Point Pos on canvas.
	void Draw(Point pos);

	//image of Tile
	property Bitmap^ TileBitmap;
	property bool Walkable;
	//property bool Visible;
};

