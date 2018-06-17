#include "NPCSpriteList.h"




NPCSpriteList::NPCSpriteList()
{
	head = nullptr;
	tail = nullptr;
}

void NPCSpriteList::AddSprite(NPCSprite ^ newSprite)
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

void NPCSpriteList::DrawSprites(Rectangle viewportRect, NPCSprite^ player)
{
	NPCSprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		if (viewportRect.Contains(nodeWalker->Pos))
		{
			if (nodeWalker->Alive)
			{
				nodeWalker->UpdateFrame();
				//crabs and gnolls chase the player
				if (nodeWalker->Type == CRAB || nodeWalker->Type == GNOLL)
				{
					nodeWalker->Orient(player->Pos);
				}
				nodeWalker->Move();
				int drawX = nodeWalker->Pos.X - viewportRect.Left;
				int drawY = nodeWalker->Pos.Y - viewportRect.Top;
				if (nodeWalker->Visible)
				{
					nodeWalker->Draw(Point(drawX, drawY));
				}

			}
			//System::Diagnostics::Debug::WriteLine("enemyX = " + nodeWalker->Pos.X);

		}
		nodeWalker = nodeWalker->Next;
	}
}

void NPCSpriteList::DeleteAllSprites()
{
	NPCSprite^ nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		DeleteSprite(nodeWalker);
		nodeWalker = nodeWalker->Next;
	}
}



NPCSprite ^ NPCSpriteList::findNearestSprite(NPCSprite ^ player)
{
	// TODO: ADD CHECK IF EMEMY IS IN SAME ROOM


	//calculate sprite closest to player for fireball action
	int x1 = player->Pos.X;
	int y1 = player->Pos.Y;
	double shortestDist = -1;

	NPCSprite^ nodeWalker = head;
	NPCSprite^ nearest = nullptr;
	while (nodeWalker != nullptr)
	{
		int x2 = nodeWalker->Pos.X;
		int y2 = nodeWalker->Pos.Y;
		int a1 = x2 - x1;
		int a2 = y2 - y1;
		int s1 = Math::Pow(a1, 2);
		int s2 = Math::Pow(a2, 2);
		double dist = Math::Sqrt(s1 + s2);
		if (shortestDist  < 0)
		{
			shortestDist = dist;
			nearest = nodeWalker;
		}
		if (dist < shortestDist)
		{
			shortestDist = dist;
			nearest = nodeWalker;
		}
		nodeWalker = nodeWalker->Next;
	}
	return nearest;
}

NPCSprite ^ NPCSpriteList::CheckCollisions(NPCSprite ^ player)
{
	NPCSprite^ nodeWalker = head;
	NPCSprite^ found = nullptr;
	while (nodeWalker != nullptr && found == nullptr)
	{
		if (nodeWalker->Collided(player))
		{
			found = nodeWalker;
		}
		nodeWalker = nodeWalker->Next;
	}
	return found;
}


NPCSprite ^ NPCSpriteList::CheckCollisionsFireball(FireballSprite ^ fireball)
{
	NPCSprite^ nodeWalker = head;
	NPCSprite^ found = nullptr;
	while (nodeWalker != nullptr && found == nullptr)
	{
		if (nodeWalker->CollidedFireball(fireball))
		{
			found = nodeWalker;
		}
		nodeWalker = nodeWalker->Next;
	}
	return found;
}

void NPCSpriteList::SetSpritesToVisible(NPCSprite ^ player)
{
	int visibleDistance = (VISIBLETILES * TILESIZE) / 2;
	//x and y positions of player
	int x1 = player->Pos.X;
	int y1 = player->Pos.Y;
	NPCSprite^ nodeWalker = head;
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

void NPCSpriteList::DeleteSprite(NPCSprite ^ spriteToDelete)
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
			head = head->Next;
		}
	}
	//if it is not head
	else
	{
		//loops through list
		NPCSprite^ nodeWalker = head;
		//until it reaches the one before the one to delete
		while (nodeWalker->Next != spriteToDelete)
		{
			nodeWalker = nodeWalker->Next;
		}
		nodeWalker->Next = spriteToDelete->Next;
		if (nodeWalker->Next == nullptr)
		{
			//then sets last one before it to be tail
			tail = nodeWalker;	
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
