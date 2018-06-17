#pragma once

#include "NPCSprite.h"
#include "FireballSprite.h"
#include "SpriteParent.h"

ref class NPCSpriteList
{
private:
	NPCSprite^ head; //first in list
	NPCSprite^ tail; //last in list
public:
	NPCSpriteList();
	void AddSprite(NPCSprite^ newSprite);
	void DeleteSprite(NPCSprite^ spriteToDelete);
	void DrawSprites(Rectangle viewportRect, NPCSprite^ plyayer);
	void DeleteAllSprites();
	NPCSprite^ findNearestSprite(NPCSprite^ player);
	NPCSprite^ CheckCollisions(NPCSprite^ player);

	NPCSprite^ CheckCollisionsFireball(FireballSprite^ fireball);

	void SetSpritesToVisible(NPCSprite^ player);

};
