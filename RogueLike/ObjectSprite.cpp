#include "ObjectSprite.h"




ObjectSprite::ObjectSprite(Graphics ^ startCanvas, 
	array<String^>^ startSpriteSheets, 
	int startNFrames, 
	int startWorldWidth, 
	int startWorldHeight, 
	Point startPos, 
	int startSpeed, 
	Random ^ startRGen,
	int startObjectType):
	SpriteParent::SpriteParent(startCanvas, startSpriteSheets, startNFrames, startWorldWidth, startWorldHeight, startPos, startSpeed, startRGen)
{
	Alive = true;
	ObjectType = startObjectType;
	Visible = false;
}

bool ObjectSprite::Collided(NPCSprite ^ player)
{
	//start assuming has collided
	bool collided = true;

	//if my top edge is below his bottom edge, no collision possible
	int myTopEdge = Pos.X + CollisionRect.Top;
	int hisBottomEdge = player->Pos.X + player->CollisionRect.Bottom;
	if (myTopEdge > hisBottomEdge) { collided = false; }

	//if my bottom is above his top, no collision
	int myBottomEdge = Pos.X + CollisionRect.Bottom;
	int hisTopEdge = player->Pos.X + player->CollisionRect.Top;
	if (myBottomEdge < hisTopEdge) { collided = false; }

	//if my left is to the right of his right, no collision
	int myLeft = Pos.Y + CollisionRect.Left;
	int hisRight = player->Pos.Y + player->CollisionRect.Right;
	if (myLeft > hisRight) { collided = false; }

	//if my right is to the left of his left, no collision
	int myRight = Pos.Y + CollisionRect.Right;
	int hisLeft = player->Pos.Y + player->CollisionRect.Left;
	if (myRight < hisLeft) { collided = false; }

	//if none of the no collision conditions are met, they must have collided.
	return collided;
}
