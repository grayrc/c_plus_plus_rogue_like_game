#pragma once

#include "ObjectSprite.h"

ref class ObjectSpriteList
{
private:
	ObjectSprite^ head;
	ObjectSprite^ tail;

public:
	ObjectSpriteList();
	void AddSprite(ObjectSprite^ newSprite);
	void DeleteSprite(ObjectSprite^ spriteToDelete);
	void DrawSprites(Rectangle viewportRect);
	void DeleteAllSprites();
	ObjectSprite^ CheckCollisions(NPCSprite^ player);
	void SetSpritesToVisible(NPCSprite^ player);

};
