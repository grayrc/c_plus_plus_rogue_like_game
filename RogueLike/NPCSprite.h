#pragma once
#include "SpriteParent.h"
#include "TileMap.h"
#include "FireballSprite.h"

ref class NPCSprite :
	public SpriteParent
{
public:
	NPCSprite(Graphics ^ startCanvas,
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
		int type
	);
	NPCSprite^ Next; //next sprite in the list
	TileMap^ currentMap; //

	void Move();
	//void Draw(Point drawPos);
	void Draw();
	bool Collided(NPCSprite^ player);
	bool CollidedFireball(FireballSprite^ fireball);
	void Orient(Point targetPos);

	void Chase(NPCSprite^ player);
	property int Health;
	property int MaxHealth;
	property int Attack;
	property bool Alive;
	property bool Visible;
	property int Type;
	


private:

	
	double computeAngleToTarget(Point targetPos);
	bool canMove();
	void bounce();
	//how much damage an attack does



};

