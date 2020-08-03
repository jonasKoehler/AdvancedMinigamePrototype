#pragma once

#pragma region system include
#include <string>
#pragma endregion

#pragma region engine include
#include "Texture.h"
#include "ContentManagement.h"
#include "Macro.h"
#pragma endregion

#pragma region game include
#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Exitzone.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region function
/// <summary>
/// load world from string
/// </summary>
void LoadWorldFromString()
{
	string world = "";

	// 0 = air
	// # = wall
	// I = collectible
	// S = player start
	// E = enemy
	// X = exitzone by Lukas
	// \n = delimiter
	world += "#########################################################################\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#000E00000000000000000000000000000000000000000000000000E0000000000000000#\n";
	world += "#00000000000000000000000000000E00000000000000000000000000000000E00000000#\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#00000000000000000S00000000000000000000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000000000000E00000000000E00000000000X#\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#00000000000000000000000000000000000000000000000000000E00000000000000000#\n";
	world += "#000E0000000000000000000E00000000000000000000000000000000000000000000000#\n";
	world += "#########################################################################";

	// width and height counter
	int width = -1, height = 0;

	// atlas texture of world
	CTexture* pGameTilemap = new CTexture("Texture/World/T_World.png");

	// create textured object
	CTexturedObject* pWorldObject = new CTexturedObject("", SVector2());

	// create background and render on screen
	pWorldObject->SetSrcRect(SRect(WORLD_BLOCK_SOURCE_WIDTH, WORLD_BLOCK_SOURCE_HEIGHT, WORLD_BLOCK_SOURCE_WIDTH, 0));
	pWorldObject->SetInWorld(false);
	pWorldObject->SetTexture(pGameTilemap);
	CTM->AddSceneObject(pWorldObject);

	// check every char
	for (int i = 0; i < world.length(); i++)
	{
		// if current char is new line
		if (world[i] == '\n')
		{
			height++; // increase height
			width = -1; // reset width
			continue; // start new loop
		}

		// increase width
		width++;

		if (world[i] == '0')
			continue; // skip air

		if (world[i] == 'S') // if char indicates the player
		{
			// create player
			GPlayer* pPlayer = new GPlayer
			(
				"Texture/Character/Player/T_Player.png",
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT),
				SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
			);

			pPlayer->SetSpeed(500.0f);
			pPlayer->SetColType(ECollisionType::DYNAMIC);
			pPlayer->SetTag("Player");

			CTM->AddPersistentObject(pPlayer);
			continue; // check next char
		}

		if (world[i] == 'E') // if char indicates an enemy
		{
			// create enemy

			GEnemy* pEnemy = new GEnemy(
				"Texture/Character/Enemy/T_Enemy.png",
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT),
				SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
			);

			// set speed, collision type, activate gravity, add to content and set tag
			pEnemy->SetSpeed(50.0f);
			pEnemy->SetColType(ECollisionType::DYNAMIC);
			pEnemy->SetTag("Enemy");

			CTM->AddSceneObject(pEnemy);
			continue; // check next char
		}

		if (world[i] == 'X') // if char indicates the exit
		{
			// create Exitzone
			GExitzone* pExitzone = new GExitzone(
				"Texture/Exit/T_Exit.png",
				SVector2(WORLD_BLOCK_SOURCE_WIDTH, WORLD_BLOCK_SOURCE_HEIGHT),
				SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
			);
			pExitzone->SetColType(ECollisionType::STATIC);
			pExitzone->SetTag("Exit");
			CTM->AddSceneObject(pExitzone);

			continue; // check next char
		}

		// when this is reached the char is meant to be a TexturedObject
		// create textured object
		CTexturedObject* pNewWorldTile = new CTexturedObject
		(
			"",
			SVector2(WORLD_BLOCK_WIDTH, WORLD_BLOCK_HEIGHT),
			SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
		);

		pNewWorldTile->SetTexture(pGameTilemap); // set tilemap as texture
		pNewWorldTile->SetColType(ECollisionType::NONE); // world tiles have no collision by default

		SRect srcRect = SRect(WORLD_BLOCK_SOURCE_WIDTH, WORLD_BLOCK_SOURCE_HEIGHT); // source rect by config values

		// switch current char
		switch (world[i])
		{
		case '#':
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC); // walls have static collision
			srcRect.x = 0;
			srcRect.y = 0;
			break;
		}
		default:
			break;
		}

		pNewWorldTile->SetSrcRect(srcRect); // set sec rect

		CTM->AddSceneObject(pNewWorldTile); // add to CTM
	}
}
#pragma endregion