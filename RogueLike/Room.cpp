#include "Room.h"
#include "EnumClass.h"


Room::Room(Point startLocation, Point startSizeInTiles)
{
	Location = startLocation;
	SizeInTiles = startSizeInTiles;
	CalculateBounds();
	CalculateCentre();
	CalculateWalkable();
}

void Room::CalculateBounds()
{
	LeftBound = Location.X + SizeInTiles.X - 1;
	BottomBound = Location.Y + SizeInTiles.Y - 1;
}

void Room::CalculateCentre()
{
	int centreCol = (SizeInTiles.X / 2);
	int centreRow = (SizeInTiles.Y / 2);
	int centreColPnt = Location.X + centreCol;
	int centreRowPnt = Location.Y + centreRow;
	Centre = Point(centreColPnt, centreRowPnt);
}

void Room::CalculateWalkable()
{
	LocationWalkable = Point(Location.X + 1, Location.Y + 1); // offset due to walls.
	SizeWalkable = Point(SizeInTiles.X - 2, SizeInTiles.Y - 2); // -2 due to walls around each edge, being 1 tile wide each.
}

Boolean Room::CanAddRoom(Room ^ newRoom)
{
	Boolean safeToAdd = true;
	// Check if new room overlaps, if so return false.
	if (Location.X < newRoom->LeftBound && LeftBound > newRoom->Location.X && Location.Y < newRoom->BottomBound && BottomBound > newRoom->Location.Y )
	{
		safeToAdd = false;

	}
	return safeToAdd;
}
