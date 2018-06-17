#pragma once
#include "SpriteParent.h"
#include "TileMap.h"

ref class FireballSprite :
	public SpriteParent
{
public:
	FireballSprite(Graphics ^ startCanvas,
		array<String^>^ startSpriteSheets,
		int startNFrames,
		int startWorldWidth,
		int startWorldHeight,
		Point startPos,
		int startSpeed,
		Random^ startRGen,
		TileMap^ startMap
	);
	property bool HasTarget;
	property bool HitSomething;
	//NPCSprite^ Target;
	TileMap^ currentMap;
	bool CanMove();
	void Move();
	void Draw(Rectangle viewPortRec);
	void Orient(Point targetPos);
	double ComputeAngleToTarget(Point targetPos);
};

