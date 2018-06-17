#include "SpriteParent.h"


array<Point>^ SpriteParent::setVelocityDirections()
{
	array<Point>^ vArray = gcnew array<Point>(NDIRECTIONS);
	vArray[0] = Point(1, 0); //East
	vArray[1] = Point(0, 1); //South
	vArray[2] = Point(-1, 0); //West
	vArray[3] = Point(0, -1); //North
	return vArray;
}

Rectangle SpriteParent::setCollisionRect()
{
	int offset = TILESIZE / 5;
	int x = offset;
	int y = (offset * 2);
	int w = TILESIZE - offset;
	int h = TILESIZE - offset;
	return Rectangle(x, y, w, h);
}

SpriteParent::SpriteParent(Graphics ^ startCanvas, 
	array<String^>^ startSpriteArray, 
	int startNFrames, 
	int startWorldWidth, 
	int startWorldHeight, 
	Point startPos,
	int startSpeed,
	Random^ startRGen)
{
	canvas = startCanvas;
	worldWidth = startWorldWidth;
	worldHeight = startWorldHeight;
	currentFrame = 0;
	nFrames = startNFrames;
	displaySize = SPRITESIZE;
	spriteSheets = startSpriteArray;
	Pos = startPos;
	velocityDirections = setVelocityDirections();
	speed = startSpeed;
	Direction = EAST;
	SetSpriteSheet(Direction, nFrames);
	canMove = true;
	CollisionRect = setCollisionRect();
	rGen = startRGen;
}


void SpriteParent::Draw(Point drawPos)
{
	//x and y position of top left of bitmap to be drawn
	int currFrameX = currentFrame * FrameWidth;
	int currFrameY = 0;
	//what portion of the sprite sheet is to be drawn
	Rectangle drawRect = Rectangle(currFrameX, currFrameY, FrameWidth, FrameHeight);
	//draw at given position with defined size
	Rectangle drawPosRect = Rectangle(drawPos.X, drawPos.Y, SPRITESIZE, SPRITESIZE);
	canvas->DrawImage(currentSpriteSheet, drawPosRect, drawRect, GraphicsUnit::Pixel);
}

void SpriteParent::Move()
{
	int newX = Pos.X + (speed * vel.X);
	int newY = Pos.Y + (speed * vel.Y);
	Pos = Point(newX, newY);
}

void SpriteParent::UpdateFrame()
{
	int startFrame = 2;
	//currentFrame = ((currentFrame + 1) % nFrames);

	//cycles through from starting frame of sprite sheet to end frame
	if (currentFrame == nFrames - 1)
	{
		currentFrame = startFrame;
	}
	else
	{
		currentFrame++;
	}
}

void SpriteParent::SetSpriteSheet(int spriteDirection, int newNFrames)
{
	currentSpriteSheet = gcnew Bitmap(spriteSheets[spriteDirection]);
	FrameWidth = currentSpriteSheet->Width / newNFrames;
	FrameHeight = currentSpriteSheet->Height;
	currentSpriteSheet->MakeTransparent(currentSpriteSheet->GetPixel(0, 0));
}

void SpriteParent::ChangeDirection(int direction)
{
	//sets direction property
	Direction = direction;
	//sets velocity
	vel = velocityDirections[Direction];
	//changes sprite sheet if changing to west or east, stays the same if moving north or south
	if (direction == WEST)
	{
		SetSpriteSheet(FACEWEST, nFrames);
	}
	if (direction == EAST)
	{
		SetSpriteSheet(FACEEAST, nFrames);
	}
}
