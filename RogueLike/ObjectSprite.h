#pragma once
#include "NPCSprite.h"

ref class ObjectSprite :
	public SpriteParent
{
public:
	ObjectSprite(Graphics ^ startCanvas,
		array<String^>^ startSpriteSheets,
		int startNFrames,
		int startWorldWidth,
		int startWorldHeight,
		Point startPos,
		int startSpeed,
		Random^ startRGen,
		int startObjectType);

	ObjectSprite^ Next; //next sprite in list
	bool Alive;
	bool Collided(NPCSprite^ player);
	int ObjectType;

	property bool Visible;
};

