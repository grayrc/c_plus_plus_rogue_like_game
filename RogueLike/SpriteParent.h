#pragma once
#include "EnumClass.h"

//base class for all sprites
//contains methods all sprites (may) use:
//draw, move, update frame, set sprite sheet

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//public enum EDirection { EAST, SOUTH, WEST, NORTH };

ref class SpriteParent
{

protected:

	Graphics^ canvas;
	//array<String^>^ spriteSheets;
	Bitmap^ currentSpriteSheet;
	Random^ rGen;
	int currentFrame;
	int nFrames;
	Point vel;
	int worldWidth;
	int worldHeight;
	int displaySize;
	array<Point>^ velocityDirections;
	//int speed;
	bool canMove;


	array<Point>^ setVelocityDirections();
	Rectangle setCollisionRect();

public:
	array<String^>^ spriteSheets;
	int speed;
	property int FrameWidth;
	property int FrameHeight;
	property Point Pos;
	property Point Vel;
	property int Direction;
	property Rectangle CollisionRect;

public:

	SpriteParent(Graphics^ startCanvas, 
		array<String^>^ startSpriteArray, 
		int startNFrames, 
		int startWorldWidth, 
		int startWorldHeight, 
		Point startPos,
		int startSpeed,
		Random^ startRGen);

	void Draw(Point drawPos);
	void Move();
	void UpdateFrame();
	void SetSpriteSheet(int spriteDirection, int newNFrames);
	void ChangeDirection(int direction);

};