#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Room
{
public:
	Room^ Next;
	property Point Location;
	property Point LocationWalkable;
	property Point SizeInTiles;
	property Point SizeWalkable;
	property Point Centre;
	property int LeftBound;
	property int BottomBound;
	Room(Point startLocation, Point startSizeInTiles);
	void CalculateBounds();
	void CalculateCentre();
	void CalculateWalkable();
	Boolean CanAddRoom(Room^ newRoom);
};

