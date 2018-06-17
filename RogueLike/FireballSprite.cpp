#include "FireballSprite.h"



FireballSprite::FireballSprite(Graphics ^ startCanvas, 
	array<String^>^ startSpriteSheets, 
	int startNFrames, 
	int startWorldWidth, 
	int startWorldHeight, 
	Point startPos, 
	int startSpeed, 
	Random ^ startRGen, 
	TileMap ^ startMap
	) :
	SpriteParent::SpriteParent(startCanvas, startSpriteSheets, startNFrames, startWorldWidth, startWorldHeight, startPos, startSpeed, startRGen)
{
	currentMap = startMap;
	HasTarget = false;
	HitSomething = false;
	
}

bool FireballSprite::CanMove()
{
	bool walkable = true;
	// centre of sprite
	int centreX = Pos.X + vel.X + (SPRITESIZE/2);
	int centreY = Pos.Y + vel.Y + (SPRITESIZE/2);
	int tileColumn = (centreX / TILESIZE);
	int tileRow = (centreY / TILESIZE);
	walkable = currentMap->isTileWalkable(tileRow, tileColumn);

	return walkable;
}

void FireballSprite::Move()
{
	if (CanMove())
	{
		int posx = Pos.X + vel.X;
		int posy = Pos.Y + vel.Y;
		Pos = Point(posx, posy);
	}
	else
	{
		HitSomething = true;
	}
	
}

void FireballSprite::Draw(Rectangle viewPortRec)
{
	//x and y position of top left of bitmap to be drawn
	int currFrameX = currentFrame * FrameWidth;
	int currFrameY = 0;
	//what portion of the sprite sheet is to be drawn
	Rectangle drawRect = Rectangle(currFrameX, currFrameY, FrameWidth, FrameHeight);
	//draw at given position with defined size
	int drawPosX = Pos.X - viewPortRec.Left;
	int drawPosY = Pos.Y - viewPortRec.Top;
	Rectangle drawPosRect = Rectangle(drawPosX,drawPosY, SPRITESIZE, SPRITESIZE);
	canvas->DrawImage(currentSpriteSheet, drawPosRect, drawRect, GraphicsUnit::Pixel);
}




void FireballSprite::Orient(Point targetPos)
{
	int velX = 0;
	int velY = 0;
	double angle = ComputeAngleToTarget(targetPos);
	velX = Math::Cos(angle) * speed;
	velY = Math::Sin(angle) * speed;
	vel = Point(velX, velY);
}

double FireballSprite::ComputeAngleToTarget(Point targetPos)
{
	double angle;

	int xDelta = targetPos.X - Pos.X;
	int yDelta = targetPos.Y - Pos.Y;

	if ((xDelta != 0) && (yDelta != 0))
	{
		// atan2 returns the angle of rotation between two points with vertical distance arg1 and horizontal distance arg2
		angle = Math::Atan2(yDelta, xDelta);	// result is in radians
	}
	else
	{
		angle = 0.0;	// instance and target share an x or y axis location. This works as a heuristic
	}
	return angle;
}
