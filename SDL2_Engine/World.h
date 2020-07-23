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
	// \n = delimiter
	world += "#######################################\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#0000000000000000000000000000000000000#\n";
	world += "#######################################";

	// width and height counter
	int width = 0, height = 0;

	// atlas texture of world
	CTexture* pTexture = new CTexture("Texture/World/T_World.png");

	// create textured object
	CTexturedObject* pObj = new CTexturedObject(
		"",
		SVector2()
	);

	// create background and render on screen
	pObj->SetSrcRect(SRect(WORLD_BLOCK_SOURCE_WIDTH, WORLD_BLOCK_SOURCE_HEIGHT, 0, 3 * WORLD_BLOCK_SOURCE_HEIGHT));
	pObj->SetInWorld(false);
	pObj->SetTexture(pTexture);
	CTM->AddSceneObject(pObj);

	// check every char
	for (int i = 0; i < world.length(); i++)
	{
		// if current char not new line, player and enemy start
		if (world[i] != '\n' && world[i] != '0' && world[i] != 'S' && world[i] != 'E')
		{
			// create textured object
			CTexturedObject* pObj = new CTexturedObject(
				"",
				SVector2(WORLD_BLOCK_WIDTH, WORLD_BLOCK_HEIGHT),
				SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
			);

			// set atlas texture to textured object texture
			pObj->SetTexture(pTexture);

			// theme height position in texture
			int theme = 2;

			// source rect by config values
			SRect srcRect = SRect(WORLD_BLOCK_SOURCE_WIDTH, WORLD_BLOCK_SOURCE_HEIGHT);
			srcRect.y = theme * WORLD_BLOCK_SOURCE_HEIGHT;

			// switch current char
			switch (world[i])
			{
			// if V (way) set position x to way rect in atlas texture and collision type static
			case 'V':
			{
				srcRect.x = WORLD_BLOCK_SOURCE_WIDTH;
				pObj->SetColType(ECollisionType::STATIC);
				break;
			}

			// if I (dirt) set position x to dirt rect in atlas texture and collision type static
			case 'I':
			{
				srcRect.x = 5 * WORLD_BLOCK_SOURCE_WIDTH;
				pObj->SetColType(ECollisionType::STATIC);
				break;
			}

			// if X (cloud) set position y and x to cloud rect in atlas texture
			case 'X':
			{
				srcRect.y = 3 * WORLD_BLOCK_SOURCE_HEIGHT;
				srcRect.x = 9 * WORLD_BLOCK_SOURCE_WIDTH;
				break;
			}

			default:
				break;
			}

			// set source rect and add textured object to content
			pObj->SetSrcRect(srcRect);
			CTM->AddSceneObject(pObj);
		}

		// if current char is player start
		else if (world[i] == 'S')
		{
			// create player
			GPlayer* pPlayer = new GPlayer(
				"Texture/Character/Mario/T_Mario.png",
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT),
				SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
			);

			// set speed, collision type, activate gravity and add to content
			pPlayer->SetSpeed(500.0f);
			pPlayer->SetColType(ECollisionType::DYNAMIC);
			pPlayer->ActivateGravity();
			CTM->AddPersistentObject(pPlayer);
		}

		// if current char is enemy
		else if (world[i] == 'E')
		{
			// create enemy
			GEnemy* pEnemy = new GEnemy(
				"Texture/Character/Mario/T_Mario.png",
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT),
				SVector2(width * WORLD_BLOCK_WIDTH, height * WORLD_BLOCK_HEIGHT)
			);

			// set speed, collision type, activate gravity, add to content and set tag
			pEnemy->SetSpeed(250.0f);
			pEnemy->SetColType(ECollisionType::DYNAMIC);
			pEnemy->ActivateGravity();
			CTM->AddPersistentObject(pEnemy);
			pEnemy->SetTag("Enemy");
		}

		// increase width
		width++;

		// if current char is new line
		if (world[i] == '\n')
		{
			// increase height and reset width
			height++;
			width = 0;
		}
	}
}
#pragma endregion