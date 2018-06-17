#include "LinkedListRooms.h"

int LinkedListRooms::listSize()
{
	int count = 0;
	Room^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		count++;
		nodeWalker = nodeWalker->Next;
	}
	return count;
}

LinkedListRooms::LinkedListRooms(Random^ startRGen)
{
	rGen = startRGen;
	head = nullptr;
	tail = nullptr;
}

Boolean LinkedListRooms::CheckForOverLap(Room ^ newRoom)
{
	Boolean safeToAdd = false;
	if (tail == nullptr)
	{
		safeToAdd = true;
	}
	if (safeToAdd == false)
	{
		safeToAdd = true;
		Room^ nodeWalker = head;
		while (nodeWalker != nullptr && safeToAdd == true)
		{
			safeToAdd = nodeWalker->CanAddRoom(newRoom);
			nodeWalker = nodeWalker->Next;
		}
	}
	return safeToAdd;
}

void LinkedListRooms::AddAtTail(Room ^ newRoom)
{
	if (tail == nullptr)
	{
		head = newRoom;
		tail = newRoom;
	}
	else
	{
		tail->Next = newRoom;
		tail = newRoom;
	}
}

void LinkedListRooms::DrawRoomsOnMap(array<int, 2>^ map)
{
	Room^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		int locR = nodeWalker->Location.Y;
		int locC = nodeWalker->Location.X;
		for (int r = locR; r <= nodeWalker->BottomBound; r++)
		{
			for (int c = locC; c <= nodeWalker->LeftBound; c++)
			{
				if (map[r, c] == CORRIDOR)
				{
					map[r, c] = DOOROPEN;
				}
				else
				{
					map[r, c] = WALL;
				}
				//System::Diagnostics::Debug::WriteLine("row: " + r + " col: " + c);
				
			}
		}
		for (int r = locR + 1; r <= (nodeWalker->BottomBound - 1); r++)
		{
			for (int c = locC + 1; c <= (nodeWalker->LeftBound -1); c++)
			{

				//System::Diagnostics::Debug::WriteLine("row: " + r + " col: " + c);
				map[r, c] = ROOM;
			}
		}
		
		nodeWalker = nodeWalker->Next;
	}
}

void LinkedListRooms::LinkRooms(array<int, 2>^ map)
{
	Room^ nodeWalker = head;
	while (nodeWalker != nullptr )
	{
		Room^ room1 = nodeWalker;
		Room^ room2 = nodeWalker->Next;
		if (room2 == nullptr)
		{
			room2 = head;
		}
		Point room1centre = room1->Centre;
		Point room2centre = room2->Centre;
		//System::Diagnostics::Debug::WriteLine("Room1 centre: " + room1centre.X + " " + room1centre.Y);
		//System::Diagnostics::Debug::WriteLine("Room2 centre: " + room2centre.X + " " + room2centre.Y);
		
		/*
		Corridor connecting rooms: X direction
		*/
		if (room1centre.X < room2centre.X) // Therefore room2 is on the right side of room1
		{
			for (int c = room1centre.X; c < room2centre.X ; c++)
			{
				map[room1centre.Y, c] = CORRIDOR;
				//System::Diagnostics::Debug::WriteLine("row: " + room1centre.Y + " col: " + c);
				/*
				if (c == (nodeWalker->LeftBound -1))
				{
					map[room1centre.Y, c] = DOOROPEN;
				}
				
				else if (c == (room2->Location.X - 1) && (room1centre.Y > room2->Location.Y && room1centre.Y < room2->BottomBound))
				{
					map[room1centre.Y, c] = DOOROPEN;
				}
				
				else
				{
					map[room1centre.Y, c] = CORRIDOR;
				}
				*/
			}
		}
		if (room1centre.X > room2centre.X) //Therefore room2 is on the left side of room1
		{
			for (int c = room2centre.X; c < room1centre.X; c++)
			{
				map[room1centre.Y, c] = CORRIDOR;
				//System::Diagnostics::Debug::WriteLine("row: " + room1centre.Y + " col: " + c);
				/*
				if (c == (nodeWalker->Location.X)) // Add door to tile on wall of room as corridor is being drawn towwards second room.
				{
					map[room1centre.Y, c] = DOOROPEN;
				}
				/*
				else if (c == (room2->LeftBound) && (room1centre.Y > room2->Location.Y && room1centre.Y < room2->BottomBound)) // Add door to second room if corridor hits room.
				{
					map[room1centre.Y, c] = DOOROPEN;
				}
				
				else // Add usual corridor tile.
				{
					map[room1centre.Y, c] = CORRIDOR;
				}
				*/
			}
		}

		/*
		Corridor connecting rooms : Y direction
		*/

		if (room1centre.Y < room2centre.Y) // When room 2 is below room one
		{
			for (int r = room1centre.Y; r <= room2centre.Y; r++)
			{
				map[r, room2centre.X] = CORRIDOR;
			}
		}
		if (room1centre.Y > room2centre.Y) // When room 2 is above room one.
		{
			for (int r = room2centre.Y; r <= room1centre.Y; r++)
			{
				map[r, room2centre.X] = CORRIDOR;
			}

		}

		
		
		nodeWalker = nodeWalker->Next;
	}

}

void LinkedListRooms::AddRemainingDoors(array<int, 2>^ map)
{
	Room^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		// Check top and bottom of room for door placement
		for (int c = nodeWalker->Location.X; c < (nodeWalker->Location.X + nodeWalker->SizeInTiles.X); c++)
		{
			// Top wall
			int topWall = nodeWalker->Location.Y;
			if (map[topWall, c] == CORRIDOR)
			{
				map[topWall, c] = DOOROPEN;
			}

			// Bottom Wall
			int bottomWall = nodeWalker->Location.Y + nodeWalker->SizeInTiles.Y;
			if (map[bottomWall, c] == CORRIDOR)
			{
				map[bottomWall, c] = DOOROPEN;
			}
			
		}

		// Check for left and right of room door placement
		for (int r = nodeWalker->Location.Y; r < (nodeWalker->SizeInTiles.Y); r++)
		{
			// Left Wall
			int leftWall = nodeWalker->Location.X;
			if (map[r, leftWall] == CORRIDOR)
			{
				map[r, leftWall] = DOOROPEN;
			}

			// Left Wall
			int rightWall = nodeWalker->Location.X + nodeWalker->SizeInTiles.X;
			if (map[r, rightWall] == CORRIDOR)
			{
				map[r, rightWall] = DOOROPEN;
			}
		}
		nodeWalker = nodeWalker->Next;
	}
}

Room ^ LinkedListRooms::RandomRoom()
{
	//get random room position
	int returnRoom = rGen->Next(1,listSize());
	System::Diagnostics::Debug::WriteLine("number of rooms = " + listSize());
	Room^ toReturn = nullptr;
	int count = 1;
	Room^ nodeWalker = head;
	while (nodeWalker != tail)
	{
		if (count == returnRoom)
		{
			toReturn = nodeWalker;
			break;
		}
		count++;
		nodeWalker = nodeWalker->Next;
	}
	return toReturn;
}
