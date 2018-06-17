#include "ObjectSpriteList.h"



ObjectSpriteList::ObjectSpriteList()
{
	head = nullptr;
	tail = nullptr;
}

void ObjectSpriteList::AddSprite(ObjectSprite ^ newSprite)
{
	//if it's the first one, sets it as both head and tail
	if (tail == nullptr)
	{
		head = newSprite;
		tail = newSprite;
	}
	//otherwise sets the current tail to point at new one sets it as tail
	//ie. adds it to the end
	else
	{
		tail->Next = newSprite;
		tail = newSprite;
	}
}

void ObjectSpriteList::DeleteSprite(ObjectSprite ^ spriteToDelete)
{
	//If node is first in list
	if (spriteToDelete == head)
	{
		//and if it's also tail - it's the only one
		if (spriteToDelete == tail)
		{
			// head and tail become null pointers
			head = nullptr;
			tail = nullptr;
		}
		//if it's head and not tail, the one after it becomes head.
		else
		{
			head = spriteToDelete->Next;
		}
	}
	//if it is not head
	else
	{
		//loops through list
		ObjectSprite^ nodeWalker = head;
		//until it reaches the one before the one to delete
		while (nodeWalker != spriteToDelete)
		{
			nodeWalker = nodeWalker->Next;
		}
		//if spriteToDelete is the tail
		if (spriteToDelete == tail)
		{
			//then sets last one before it to be tail
			nodeWalker = tail;
		}
		//if spriteToDelete is neither head nor tail
		else
		{
			//sets node before toDelete to point to node after
			nodeWalker->Next = spriteToDelete->Next;
		}

		nodeWalker = nodeWalker->Next;



	}
}

void ObjectSpriteList::DrawSprites(Rectangle viewportRect)
{
	ObjectSprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		if (viewportRect.Contains(nodeWalker->Pos))
		{
			if (nodeWalker->Alive && nodeWalker->Visible)
			{
				int drawX = nodeWalker->Pos.X - viewportRect.Left;
				int drawY = nodeWalker->Pos.Y - viewportRect.Top;
				nodeWalker->Draw(Point(drawX, drawY));
			}

		}
		nodeWalker = nodeWalker->Next;
	}
}

void ObjectSpriteList::DeleteAllSprites()
{
	ObjectSprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		DeleteSprite(nodeWalker);
		nodeWalker = nodeWalker->Next;
	}
}

ObjectSprite ^ ObjectSpriteList::CheckCollisions(NPCSprite ^ player)
{
	ObjectSprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		if (nodeWalker->Collided(player))
		{
			return nodeWalker;
		}
		nodeWalker = nodeWalker->Next;
	}
}

void ObjectSpriteList::SetSpritesToVisible(NPCSprite ^ player)
{
	int visibleDistance = (VISIBLETILES * TILESIZE) / 2;
	//x and y positions of player
	int x1 = player->Pos.X;
	int y1 = player->Pos.Y;
	ObjectSprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		//x and y positions of each other sprite
		int x2 = nodeWalker->Pos.X;
		int y2 = nodeWalker->Pos.Y;
		//distance between player and sprite using a^2 + b^2 = c^2
		int a1 = x2 - x1;
		int a2 = y2 - y1;
		int s1 = Math::Pow(a1, 2);
		int s2 = Math::Pow(a2, 2);
		double dist = Math::Sqrt(s1 + s2);
		if (dist < visibleDistance)
		{
			nodeWalker->Visible = true;
		}
		nodeWalker = nodeWalker->Next;
	}
}
