#include "GameEngine.h"



GameEngine::GameEngine(Graphics ^ startCanvas, Random ^ startRGen, int startWidth, int startHeight)
{
	canvas = startCanvas;
	RGen = startRGen;
	width = startWidth;
	height = startHeight;
	offScreenBitmap = gcnew Bitmap(width, height);
	offScreenCanvas = Graphics::FromImage(offScreenBitmap);

	tileArray = createTileArray();
	tileSet = gcnew TileSet(offScreenCanvas, tileArray);
	tileMap = gcnew TileMap(tileSet, offScreenCanvas, RGen, cols, rows);
	
	//start at level 1 with no money
	level = 0;
	gold = 0;

	nRats = STARTNRATS;

	//creates new map, enemies and objects
	NewLevel();	

	tileSize = TILESIZE;// tileMap->GetMapCellBitmap(0, 0)->Height; //size in pixels of each tile
	int tilesHigh = (height / tileSize) + 1; //number of tile rows in viewport
	int tilesWide = (width / tileSize) + 1; //number of tile columns

	viewPort = gcnew ViewPort(offScreenCanvas, tileMap, Point(0, 0), tilesWide, tilesHigh, width, height);
	player = createPlayer(); //player controlled sprite
	fireball = createFireball(); //players projectile
	target = nullptr; //NPCSprite projectile is aimed at
	fireballedSprite = nullptr; //Sprite fireball hits
	viewPort->CentreOnSprite(player);

	//starts off not fighting
	fighting = false;

	//String with events to be displayed
	whatsHappening = "Exploring";

	//set fightcounter to 0;
	fightCounter = 0;

	//player gets to start fighting
	playersTurn = true;


	//range attack mode enabled
	rangeAttackMode = false;

}


void GameEngine::Run()
{
	//regular movement except when fighting
	if (!fighting)
	{
	player->Move();
	viewPort->CentreOnSprite(player);
	viewPort->ViewportDraw();
	player->Draw();
	player->UpdateFrame();
	Rectangle viewportRect = Rectangle(viewPort->ViewportWorld.X, viewPort->ViewportWorld.Y, width, height);
	if (rangeAttackMode)
	{
		if (fireball->HasTarget == false)
		{
			fireball->Pos = player->Pos;
			target = rats->findNearestSprite(player);
			fireball->HasTarget = true;
		}
		else if (fireball->HasTarget && !fireball->HitSomething)
		{
			fireball->Orient(target->Pos);
			fireball->Move();
			fireball->Draw(viewportRect);
		}
	}

	//range of columns / rows to set visible
	int leftMostTile = (player->Pos.X / TILESIZE) - VISIBLETILES / 2;
	int topMostTile = (player->Pos.Y / TILESIZE) - VISIBLETILES / 2;

	for (int r = 0; r < VISIBLETILES; r++)
	{
		int row = r + topMostTile;
		for (int c = 0; c < VISIBLETILES; c++)
		{
			int col = c + leftMostTile;
			tileMap->VisibleTiles[row, col] = true;

		}
	}

	//set sprites to be drawn when in range of the player
	objects->SetSpritesToVisible(player);
	rats->SetSpritesToVisible(player);

	//draw enemies and objects
	objects->DrawSprites(viewportRect);
	rats->DrawSprites(viewportRect, player);



	}
	//if fighting
	else
	{
		fightCounter++;
	}

	canvas->DrawImage(offScreenBitmap, 0, 0);

	//checks if player has collided with an object
	ObjectSprite^ hitObject = objects->CheckCollisions(player);
	if (hitObject != nullptr)
	{
		if (hitObject->ObjectType == POTIONS && hitObject->Alive == true)
		{
			
			player->Health += POTIONVALUE;
			if (player->Health > player->MaxHealth) { player->Health = player->MaxHealth; }
			objects->DeleteSprite(hitObject);
			hitObject->Alive = false;

		}
		if (hitObject->ObjectType == STAIRS)
		{
			rats->DeleteAllSprites();
			objects->DeleteAllSprites();
			NewLevel();
			Room^ newRoom = dungeon->rooms->RandomRoom();
			Point startPos = getPositionInRoom(newRoom);
			player->Pos = startPos;

			//get some gold for completing level
			gold += 10;
		}
		if (hitObject->ObjectType == COINS && hitObject->Alive == true)
		{
			gold += COINVALUE;
			objects->DeleteSprite(hitObject);
			hitObject->Alive = false;
		}
		if (hitObject->ObjectType == CHESTS && hitObject->Alive == true)
		{
			gold += CHESTVALUE;
			objects->DeleteSprite(hitObject);
			hitObject->Alive = false;
		}
		if (hitObject->ObjectType == CAPE && hitObject->Alive == true)
		{
			// Picking up item increases maxhealth, speed, and changes spritesheets for player to show magic cape.
			player->MaxHealth = CAPEINCMAXHEALTH;
			player->speed += 2;
			player->spriteSheets[0] = "assets\\rangerCapeE.bmp";
			player->spriteSheets[1] = "assets\\rangerCapeW.bmp";
			objects->DeleteSprite(hitObject);
			hitObject->Alive = false;

		}
	}

	//checks for collisions with enemies and enters fight mode
	NPCSprite^ hitSprite = rats->CheckCollisions(player);
	if (hitSprite != nullptr)
	{
		//System::Diagnostics::Debug::WriteLine("hitSprite");
		fightMode(hitSprite);
	}


	//
	//Check for fireball collisions
	//
	if (target != nullptr) // Only if fireball exsists check for collisions
	{
		fireballedSprite = rats->CheckCollisionsFireball(fireball);
	}
	
	if (fireballedSprite != nullptr)
	{
		int dmg = RGen->Next(FIREBALLMINDAMAGE, FIREBALLMAXDAMAGE);
		fireballedSprite->Health -= dmg;
		
		if (target->Health < 0)
		{
			rats->DeleteSprite(target);
			fightEvent = "You killed an enemy with a fireball!";
		}
		else
		{
			fightEvent = "You hit an enemy with a fireball!";
		}
		fireball->HitSomething = true;
		rangeAttackMode = false;
		
	}
	if (fireball->HitSomething)
	{
		fireball->HasTarget = false;
		target = nullptr;
		fireballedSprite = nullptr;
		rangeAttackMode = false;
		fireball->HitSomething = false;
	}

}

void GameEngine::UpdateDirection(int direction)
{
	player->ChangeDirection(direction);
}

void GameEngine::NewLevel()
{
	dungeon = gcnew Dungeon(RGen, Point(width, height));
	map = dungeon->CreateMap(); //dungeon createMap method returns a 2d array of map rows and columns
	tileMap->SetMapFromArray(map); //sets tilemap to map created by dungeon
	tileMap->ResetVisibleTiles(); //sets all the new tiles to invisible


	rats = createEnemies();

	objects = createObjects();
	level++;
	//rats increase as levels increase
	nRats += level;

}

String ^ GameEngine::GetHealth()
{
	int playerHealth = player->Health;

	return 	playerHealth.ToString();
}

String ^ GameEngine::GetEvent()
{
	return whatsHappening;
}

String ^ GameEngine::GetEvent2()
{
	return fightEvent;
}

String ^ GameEngine::GetLevel()
{
	return "Level: " + level.ToString();
}

String ^ GameEngine::GetGold()
{
	return "Gold: " + gold.ToString();
}

bool GameEngine::PlayerAlive()
{
	
	return player->Alive;
}


//return array of filenames of tiles to be given to tileSet.
array<String^>^ GameEngine::createTileArray()
{
	array<String^>^ tileStringArray = gcnew array<String^>(nTiles);
	tileStringArray[0] = "assets\\blank.bmp";
	tileStringArray[1] = "assets\\roomTile.bmp";
	tileStringArray[2] = "assets\\wallTile.bmp";
	tileStringArray[3] = "assets\\tileDoorOpen.bmp";
	tileStringArray[4] = "assets\\tileDoorClosed.bmp";
	tileStringArray[5] = "assets\\corridorTile.bmp";
	tileStringArray[6] = "assets\\tileDoorOpenTop.bmp";

	return tileStringArray;
}

NPCSprite ^ GameEngine::createPlayer()
{
	int playerSpeed = PLAYERSPEED;
	Room^ newRoom = dungeon->rooms->RandomRoom();
	Point startPos = getPositionInRoom(newRoom);
	array<String^>^ playerArray = gcnew array<String^>(PLAYERIMAGES);

	playerRoom = newRoom;
	playerArray[0] = "assets\\rangerArmourE.bmp";
	playerArray[1] = "assets\\rangerArmourW.bmp";
	NPCSprite^ newPlayer = gcnew NPCSprite(
		offScreenCanvas, 
		playerArray, 
		PLAYERFRAMES, 
		width, 
		height, 
		startPos, 
		playerSpeed, 
		RGen, 
		tileMap, 
		PLAYERSTARTHEALTH, 
		PLAYERSTARTATTACK,
		PLAYER);
	return newPlayer;
}

FireballSprite ^ GameEngine::createFireball()
{
	int nImages = 1;
	int nFrames = 4;
	int playerSpeed = 10;
	Point startPos = Point(player->Pos.X, player->Pos.Y);
	array<String^>^ playerArray = gcnew array<String^>(nImages);
	playerArray[0] = "assets\\fireball.bmp";

	FireballSprite^ newFireball = gcnew FireballSprite(
		offScreenCanvas,
		playerArray,
		nFrames,
		width,
		height,
		startPos,
		playerSpeed,
		RGen,
		tileMap);
	return newFireball;
}



NPCSpriteList ^ GameEngine::createEnemies()
{
	NPCSpriteList^ newSpriteList = gcnew NPCSpriteList();
	for (int i = 0; i < nRats; i++)
	{
		//get random room
		Room^ toPlaceEnemy = dungeon->rooms->RandomRoom();
		//get random postion in room
		Point posOfEnemy = getPositionInRoom(toPlaceEnemy);
		//create new enemy sprite

		NPCSprite^ newSprite = gcnew NPCSprite(
			offScreenCanvas, 
			createRatSpriteArray(), 
			ENEMYFRAMES, 
			width, 
			height, 
			posOfEnemy, 
			RATSPEED, 
			RGen, 
			tileMap, 
			RATHEALTH,
			RATATTACK,
			RAT);
		//add to list
		newSpriteList->AddSprite(newSprite);
	}
	//number of crabs increases with level
	int nCrabs = level * 2;
	for (int i = 0; i < nCrabs ; i++)
	{
		//get random room
		Room^ toPlaceEnemy = dungeon->rooms->RandomRoom();
		//get random postion in room
		Point posOfEnemy = getPositionInRoom(toPlaceEnemy);
		//create new enemy sprite
		NPCSprite^ newSprite = gcnew NPCSprite(
			offScreenCanvas,
			createCrabSpriteArray(),
			ENEMYFRAMES,
			width,
			height,
			posOfEnemy,
			CRABSPEED,
			RGen,
			tileMap,
			CRABHEALTH,
			CRABATTACK,
			CRAB);
		//add to list
		newSpriteList->AddSprite(newSprite);
	}
	int nGnolls = level;
	for (int i = 0; i < nGnolls; i++)
	{
		//get random room
		Room^ toPlaceEnemy = dungeon->rooms->RandomRoom();
		//get random postion in room
		Point posOfEnemy = getPositionInRoom(toPlaceEnemy);
		//create new enemy sprite
		NPCSprite^ newSprite = gcnew NPCSprite(
			offScreenCanvas,
			createGnollSpriteArray(),
			ENEMYFRAMES,
			width,
			height,
			posOfEnemy,
			GNOLLSPEED,
			RGen,
			tileMap,
			GNOLLHEALTH,
			GNOLLATTACK,
			GNOLL);
		//add to list
		newSpriteList->AddSprite(newSprite);
	}
	return newSpriteList;
}
//gets a random world map position within a given room
Point GameEngine::getPositionInRoom(Room ^ room)
{
	//get location of room
	//Point roomPos = room->Location;

	int posOnMapX = room->LocationWalkable.X * TILESIZE;
	int posOnMapY = room->LocationWalkable.Y * TILESIZE;

	//get x and y coordinates of a random point in room
	int posInRoomX = (RGen->Next(room->SizeWalkable.X) * TILESIZE);
	int posInRoomY = (RGen->Next(room->SizeWalkable.Y) * TILESIZE);

	//translate point in room to point on world map
	int pointOnMapX = posOnMapX + posInRoomX + (dungeon->dungeonOffSet.X *TILESIZE);
	int pointOnMapY = posOnMapY + posInRoomY + (dungeon->dungeonOffSet.Y *TILESIZE);

	return Point(pointOnMapX, pointOnMapY);
}

array<String^>^ GameEngine::createRatSpriteArray()
{
	array<String^>^ enemyArray = gcnew array<String^>(2);
	enemyArray[0] = "assets\\ratE.bmp";
	enemyArray[1] = "assets\\ratW.bmp";
	return enemyArray;
}

array<String^>^ GameEngine::createCrabSpriteArray()
{
	array<String^>^ enemyArray = gcnew array<String^>(2);
	enemyArray[0] = "assets\\crabE.bmp";
	enemyArray[1] = "assets\\crabW.bmp";
	return enemyArray;
}

array<String^>^ GameEngine::createGnollSpriteArray()
{
	array<String^>^ enemyArray = gcnew array<String^>(2);
	enemyArray[0] = "assets\\gnollE.bmp";
	enemyArray[1] = "assets\\gnollW.bmp";
	return enemyArray;
}

//When player collides with sprite
void GameEngine::fightMode(NPCSprite ^ enemy)
{
	fighting = true;

	//fight action lasts 20 timer ticks
	if (fightCounter < BATTLEEVENTTIME)
	{
		if (playersTurn)
		{
			whatsHappening = "Player Attacking";
		}
		else
		{
			whatsHappening = "Enemy Attacking";
		}
	}
	//actions occur at timer tick 20 (BATTLEEVENTTIME)
	else
	{
		if (playersTurn)
		{
			//damage inflicted is random up to Attack value
			int damage = (RGen->Next(10) * player->Attack) / 10;
			enemy->Health -= damage;
			//variable for myform feedback
			fightEvent = "You hit enemy for " + damage + " damage";
		}
		else
		{
			int damage = (RGen->Next(10) * enemy->Attack) / 10;
			/********************************************************************************************************


			     __      _____  ____  _____     __  __  ____  _____  ______    _    _ ______ _____  ______     __
			     \ \    / ____|/ __ \|  __ \   |  \/  |/ __ \|  __ \|  ____|  | |  | |  ____|  __ \|  ____|   / /
			 _____\ \  | |  __| |  | | |  | |  | \  / | |  | | |  | | |__     | |__| | |__  | |__) | |__     / /_____
			|______> > | | |_ | |  | | |  | |  | |\/| | |  | | |  | |  __|    |  __  |  __| |  _  /|  __|   < <______|
			      / /  | |__| | |__| | |__| |  | |  | | |__| | |__| | |____   | |  | | |____| | \ \| |____   \ \
			     /_/    \_____|\____/|_____/   |_|  |_|\____/|_____/|______|  |_|  |_|______|_|  \_\______|   \_\




			PATRICIA  COMMENT OUT THE FOLLOWING LINE HERE TO GET "GOD MODE" :)
			*/
			player->Health -= damage;
			fightEvent = "Enemy hit you for " + damage + " damage";
			if (player->Health < 0)
			{
				player->Alive = false;
			}
		}
		playersTurn = !playersTurn;
		fightCounter = 0;

	}
	//when enemy health is below 0, enemy is deleted and fighting ceases
	if (enemy->Health < 0)
	{
		fightEvent = "You killed the enemy";
		enemy->Alive = false;
		rats->DeleteSprite(enemy);
		fighting = false;
	}

}
ObjectSpriteList ^ GameEngine::createObjects()
{
	ObjectSpriteList^ newObjectList = gcnew ObjectSpriteList();
	ObjectSprite^ stairs = createStairs();
	newObjectList->AddSprite(stairs);

	//create potions
	for (int i = 0; i < NPOTIONS; i++)
	{
		array<String^>^ potionArray = gcnew array<String^>(1);
		potionArray[0] = "assets\\healthPotion.bmp";
		Room^ newRoom = dungeon->rooms->RandomRoom();
		Point startPos = getPositionInRoom(newRoom);
		ObjectSprite^ potion = gcnew ObjectSprite(offScreenCanvas, potionArray, 1, width, height, startPos, 0, RGen, POTIONS);
		newObjectList->AddSprite(potion);
	}

	//creeate gold
	for (int i = 0; i < NCOINS; i++)
	{
		array<String^>^ coinsArray = gcnew array<String^>(1);
		coinsArray[0] = "assets\\coin.bmp";
		Room^ newRoom = dungeon->rooms->RandomRoom();
		Point startPos = getPositionInRoom(newRoom);
		ObjectSprite^ coin = gcnew ObjectSprite(offScreenCanvas, coinsArray, 1, width, height, startPos, 0, RGen, COINS);
		newObjectList->AddSprite(coin);
	}

	//creeate chests
	for (int i = 0; i < NCHESTS; i++)
	{
		array<String^>^ chestArray = gcnew array<String^>(1);
		chestArray[0] = "assets\\chest.bmp";
		Room^ newRoom = dungeon->rooms->RandomRoom();
		Point startPos = getPositionInRoom(newRoom);
		ObjectSprite^ chest = gcnew ObjectSprite(offScreenCanvas, chestArray, 1, width, height, startPos, 0, RGen, CHESTS);
		newObjectList->AddSprite(chest);
	}

	//create Magic Cape
	if (level == 2) // On add on the 3rd level (zero start)
	{
		for (int i = 0; i < NUMCAPE; i++)
		{
			array<String^>^ capeArray = gcnew array<String^>(1);
			capeArray[0] = "assets\\cape.bmp";
			Room^ newRoom = dungeon->rooms->RandomRoom();
			Point startPos = getPositionInRoom(newRoom);
			ObjectSprite^ cape = gcnew ObjectSprite(offScreenCanvas, capeArray, 1, width, height, startPos, 0, RGen, CAPE);
			newObjectList->AddSprite(cape);
			fightEvent = "You picked up a Magic Cape!";
		}
	}
	
	
	

	return newObjectList;
}

//create stairs to next level
ObjectSprite^ GameEngine::createStairs()
{
	array<String^>^ stairArray = gcnew array<String^>(1);
	stairArray[0] = "assets\\stairs.bmp";
	Room^ newRoom = dungeon->rooms->RandomRoom();
	Point startPos = getPositionInRoom(newRoom);
	ObjectSprite^ stairs = gcnew ObjectSprite(offScreenCanvas, stairArray, 1, width, height, startPos, 0, RGen, STAIRS);
	return stairs;
}



