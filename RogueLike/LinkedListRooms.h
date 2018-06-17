#pragma once
#include "Room.h"
#include "EnumClass.h"
#include <math.h>


ref class LinkedListRooms
{
private:
	Random^ rGen;
	Room^ head;
	Room^ tail;
	

public:
	int listSize();
	LinkedListRooms(Random^ startRGen);
	Boolean CheckForOverLap(Room^ newRoom);
	void AddAtTail(Room^ newRoom);

	void DrawRoomsOnMap(array<int, 2>^ map);

	//Links all rooms together
	void LinkRooms(array<int, 2>^ map);
	void AddRemainingDoors(array<int, 2>^ map);

	//returns a random Room
	Room^ RandomRoom();
};

