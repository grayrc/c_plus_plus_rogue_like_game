#include "NPCSprite.h"



NPCSprite::NPCSprite(Graphics ^ startCanvas, 
	array<String^>^ startSpriteSheets, 
	int startNFrames, 
	int startWorldWidth, 
	int startWorldHeight, 
	Point startPos, 
	int startSpeed,
	Random^ startRGen,
	TileMap^ startMap,
	int startHealth,
	int startAttack,
	int type) :
	SpriteParent::SpriteParent(startCanvas, startSpriteSheets, startNFrames, startWorldWidth, startWorldHeight, startPos, startSpeed, startRGen)
{
	//rGen = startRGen;
	int Direction = rGen->Next(4);
	ChangeDirection(Direction);
	Health = startHealth;
	MaxHealth = startHealth;
	currentMap = startMap;
	Attack = startAttack;
	Alive = true;
	Visible = false;
	Type = type;
}

void NPCSprite::Move()
{
	{
		if (canMove())
		{
			int newX = Pos.X + (speed * vel.X);
			int newY = Pos.Y + (speed * vel.Y);
			Pos = Point(newX, newY);
		}
		else
		{
			//System::Diagnostics::Debug::WriteLine("bouncing");
			bounce();
		}
	}
}

/*void NPCSprite::Draw(Point drawPos)
{

		//x and y position of top left of bitmap to be drawn
		int currFrameX = currentFrame * FrameWidth;
		int currFrameY = 0;
		//what portion of the sprite sheet is to be drawn
		Rectangle drawRect = Rectangle(currFrameX, currFrameY, FrameWidth, FrameHeight);
		//draw at given position with defined size
		Rectangle drawPosRect = Rectangle(drawPos.X, drawPos.Y, SPRITESIZE, SPRITESIZE);
		canvas->DrawImage(currentSpriteSheet, drawPosRect, drawRect, GraphicsUnit::Pixel);
	
}*/

//method for drawing player
void NPCSprite::Draw()
{
	//where on screen (center) and size sprite is to be drawn
	int centerX = (worldWidth / 2) + (TILESIZE / 2);
	int centerY = (worldHeight / 2) + (TILESIZE / 2);
	Rectangle drawPos = Rectangle(centerX, centerY, SPRITESIZE, SPRITESIZE);
	int currFrameX = currentFrame * FrameWidth;
	int currFrameY = 0;
	//what portion of the sprite sheet is to be drawn
	Rectangle drawRect = Rectangle(currFrameX, currFrameY, FrameWidth, FrameHeight);
	canvas->DrawImage(currentSpriteSheet, drawPos, drawRect, GraphicsUnit::Pixel);
	//canvas->DrawImage(currentSpriteSheet, Pos.X, Pos.Y);
}

bool NPCSprite::Collided(NPCSprite ^ player)
{
	//start assuming has collided
	bool collided = true;

	//if my top edge is below his bottom edge, no collision possible
	int myTopEdge = Pos.X;// +CollisionRect.Top;
	int hisBottomEdge = player->Pos.X + player->CollisionRect.Bottom;
	if (myTopEdge > hisBottomEdge) { collided = false; }

	//if my bottom is above his top, no collision
	int myBottomEdge = Pos.X; // +CollisionRect.Bottom;
	int hisTopEdge = player->Pos.X + player->CollisionRect.Top;
	if (myBottomEdge < hisTopEdge) { collided = false; }

	//if my left is to the right of his right, no collision
	int myLeft = Pos.Y;// +CollisionRect.Left;
	int hisRight = player->Pos.Y + player->CollisionRect.Right;
	if (myLeft > hisRight) { collided = false; }

	//if my right is to the left of his left, no collision
	int myRight = Pos.Y;// +CollisionRect.Right;
	int hisLeft = player->Pos.Y + player->CollisionRect.Left;
	if (myRight < hisLeft) { collided = false; }

	//if none of the no collision conditions are met, they must have collided.
	return collided;
}

bool NPCSprite::CollidedFireball(FireballSprite ^ fireball)
{
	//start assuming has collided
	bool collided = true;

	//if my top edge is below his bottom edge, no collision possible
	int myTopEdge = Pos.X + CollisionRect.Top;
	int hisBottomEdge = fireball->Pos.X + fireball->CollisionRect.Bottom;
	if (myTopEdge > hisBottomEdge) { collided = false; }

	//if my bottom is above his top, no collision
	int myBottomEdge = Pos.X + CollisionRect.Bottom;
	int hisTopEdge = fireball->Pos.X + fireball->CollisionRect.Top;
	if (myBottomEdge < hisTopEdge) { collided = false; }

	//if my left is to the right of his right, no collision
	int myLeft = Pos.Y + CollisionRect.Left;
	int hisRight = fireball->Pos.Y + fireball->CollisionRect.Right;
	if (myLeft > hisRight) { collided = false; }

	//if my right is to the left of his left, no collision
	int myRight = Pos.Y + CollisionRect.Right;
	int hisLeft = fireball->Pos.Y + fireball->CollisionRect.Left;
	if (myRight < hisLeft) { collided = false; }

	//if none of the no collision conditions are met, they must have collided.
	return collided;
}

void NPCSprite::Chase(NPCSprite ^ player)
{

	//x and y positions of player
	int x1 = player->Pos.X;
	int y1 = player->Pos.Y;

	//x and y positions of each other sprite
	int x2 = Pos.X;
	int y2 = Pos.Y;
	//distance between player and sprite using a^2 + b^2 = c^2
	int a1 = x2 - x1;
	int a2 = y2 - y1;
	int s1 = Math::Pow(a1, 2);
	int s2 = Math::Pow(a2, 2);
	double dist = Math::Sqrt(s1 + s2);

	if (dist < CHASINGDIST)
	{

	}

}



void NPCSprite::Orient(Point targetPos)
{
	int velX = 0;
	int velY = 0;
	double angle = computeAngleToTarget(targetPos);
	velX = Math::Cos(angle) * speed;
	velY = Math::Sin(angle) * speed;
	vel = Point(velX, velY);
}

double NPCSprite::computeAngleToTarget(Point targetPos)
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

bool NPCSprite::canMove()
{
	//where sprite will be next
	int newX = Pos.X + (speed * vel.X);
	int newY = Pos.Y + (speed * vel.Y);

	//which part of sprite to check for collision
	int cornerX;
	int cornerY;
	switch (Direction)
	{
	case (NORTH):
		//top left corner
		cornerX = newX + SPRITESIZE;
		cornerY = newY + SPRITESIZE;
		break;
	case (EAST):
		//bottom right
		cornerX = newX +TILESIZE;
		cornerY = newY + SPRITESIZE;
		break;
	case (SOUTH):
		//bottom right
		cornerX = newX + SPRITESIZE;
		cornerY = newY + TILESIZE;
		break;
	case (WEST):
		//bottom left
		cornerX = newX + SPRITESIZE;
		cornerY = newY + SPRITESIZE;
	default:
		break;
	}
	int tileColumn = (cornerX / TILESIZE);
	int tileRow = (cornerY / TILESIZE);
	bool walkable = currentMap->isTileWalkable(tileRow, tileColumn);
	return walkable;
}

void NPCSprite::bounce()
{
	switch (Direction)
	{
	case (EAST):
		ChangeDirection(WEST);
		Pos = Point(Pos.X - (speed * 2), Pos.Y);
		break;
	case (WEST):
		ChangeDirection(EAST);
		Pos = Point(Pos.X + (speed * 2), Pos.Y);
		break;
	case (NORTH):
		ChangeDirection(SOUTH);
		Pos = Point(Pos.X, Pos.Y + (speed * 2));
		break;
	case (SOUTH):
		ChangeDirection(NORTH);
		Pos = Point(Pos.X, Pos.Y - (speed * 2));
		break;
	default:
		break;
	}
}
