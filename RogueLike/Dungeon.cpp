#include "Dungeon.h"
#include "EnumClass.h"


Dungeon::Dungeon(Random^ startRGen, Point startViewPortSize)
{
	RGen = startRGen;
	viewPortSize = startViewPortSize;
	totalTiles = CalculateUseableTiles();
	MakeDungeonMesurementsOdd();
	dungeonOffSet = CalculateDungeonPlacement();
	rooms = gcnew LinkedListRooms(RGen);
	roomCount = 0;
	roomAttempts = 0;
}

Point Dungeon::CalculateUseableTiles()
{
	
	// Work out the number of tiles shown within the viewport, plus 1 to stop array overflow when here is near edge of map.
	int col = (viewPortSize.X / TILESIZE) + 1;
	int row = (viewPortSize.Y / TILESIZE) + 1;
	int colMax = WORLDCOL - col - STOPFALLOFFARRAY;
	System::Diagnostics::Debug::WriteLine("UseableTiles Col: " + colMax);
	int rowMax = WORLDROW - row - STOPFALLOFFARRAY;
	System::Diagnostics::Debug::WriteLine("UseableTiles Row: " + rowMax);
	Point tiles = Point(colMax, rowMax);
	return tiles;
}

void Dungeon::MakeDungeonMesurementsOdd()
{
	if (totalTiles.X % 2 == 0)
	{
		totalTiles.X = totalTiles.X - 1;
		System::Diagnostics::Debug::WriteLine("X changed to: " + totalTiles.X);
	}

	if (totalTiles.Y % 2 == 0)
	{
		totalTiles.Y = totalTiles.Y - 1;
		System::Diagnostics::Debug::WriteLine("Y changed to: " + totalTiles.Y);
	}


}

Point Dungeon::CalculateDungeonPlacement()
{
	// Places dungeon so that there is blank space around it to stop viewport array overflow.
	int offSetX = (viewPortSize.X / TILESIZE) + 1;
	int offSetY = (viewPortSize.Y / TILESIZE) + 1;
	int col = (offSetX / 2);
	int row = (offSetY / 2);
	Point offSet = Point(col, row);
	return offSet;
}

array<int, 2>^ Dungeon::CreateMap()
{
	array<int, 2>^ fullMap = gcnew array<int, 2>(WORLDROW, WORLDCOL);
	array<int, 2>^ newMap = gcnew array<int, 2>(totalTiles.Y, totalTiles.X);

	// Fill newMap (map area) with wall tiles tiles as a base.
	for (int r = 0; r < totalTiles.Y; r++)
	{
		for (int c = 0; c < totalTiles.X; c++)
		{
			newMap[r, c] = BLANK;
		}
	}

	// Fill fullMap with black (blank) tiles so that the edges are black when the viewport is near the edge.
	for (int r = 0; r < WORLDROW; r++)
	{
		for (int c = 0; c < WORLDCOL; c++)
		{
			fullMap[r, c] = BLANK;
		}
	}
	while ((roomCount < 10) &&(roomAttempts <= MAXROOMATTEMPTS))
	{
		CreateRoom(newMap);
		roomAttempts = roomAttempts + 1;
	}

	
	rooms->LinkRooms(newMap); 
	WallOffCorridors(newMap);
	rooms->DrawRoomsOnMap(newMap);
	//rooms->AddRemainingDoors(newMap);
	
	

	// Place newMap on full map at dungeon offset to allow black (blank) space around tiles for viewport overflow
	for (int r = 0; r < totalTiles.Y; r++)
	{
		for (int c = 0; c < totalTiles.X; c++)
		{
			int row = r + dungeonOffSet.Y;
			int col = c + dungeonOffSet.X;
			fullMap[row, col] = newMap[r, c];
		}
	}
	return fullMap;
}

void Dungeon::CreateRoom(array<int, 2>^ newMap)
{
	// Always get a random odd number
	int rmCol = (2 * (RGen->Next(MINTILESFAC, MAXTILESFAC))) + 1;
	int rmRow = (2 * (RGen->Next(MINTILESFAC, MAXTILESFAC))) + 1;
	Point roomSize = Point(rmCol, rmRow);

	// maxRGenCol is the maximum column location for the minimum sized room so that it will still fit. 
	int maxRGenCol = 1 + ((totalTiles.X - MINACTUALROOMTILES) / 2);
	int maxRGenRow = 1 + ((totalTiles.Y - MINACTUALROOMTILES) / 2);

	// find a random place to pu the room
	int col = (2 * RGen->Next(0, maxRGenCol)) + 1;
	int row = (2 * RGen->Next(0, maxRGenRow)) + 1;
	Point roomLoc = Point(row, col);
	Room^ newRoom = gcnew Room(roomLoc, roomSize);

	Boolean safeToAdd = false;
	// Check if room fails array bounds check
	if (newRoom->BottomBound < totalTiles.Y && newRoom->LeftBound < totalTiles.X)
	{
		safeToAdd = true;
	}

	// If new room passes bounds check and falls within array, check if overlapping with exsisiting rooms.
	if (safeToAdd)
	{
		safeToAdd = rooms->CheckForOverLap(newRoom);
	}
	
	if (safeToAdd)
	{
		rooms->AddAtTail(newRoom);
		roomCount = roomCount + 1;

	}

}

void Dungeon::WallOffCorridors(array<int, 2>^ newMap)
{
	// Puts walls around all tiles that are of CORRIDOOR type.
	for (int r = 0; r < totalTiles.Y; r++)
	{
		for (int c = 0; c < totalTiles.X; c++)
		{
			if (newMap[r,c] == CORRIDOR)
			{
				// If a tile is a CORRIDOOR, check the spaces around, if they are blank, draw walls there.
				for (int rr = (r - 1); rr <= (r + 1); rr++)
				{
					for (int cc = (c - 1); cc <= (c + 1); cc++)
					{
						if (newMap[rr, cc] == BLANK)
						{
							newMap[rr, cc] = WALL;
						}
					}
				}
			}
		}
	}
}







