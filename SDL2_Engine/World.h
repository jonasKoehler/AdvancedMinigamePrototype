#pragma once

#pragma region system include
#include <string>
#include <fstream>
#include <SDL_image.h>
#pragma endregion

#pragma region engine include
#include "Texture.h"
#include "TextureManagement.h"
#include "ContentManagement.h"
#include "Macro.h"
#pragma endregion

#pragma region game include
#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Exitzone.h"
#include "WorldTile.h"
#include "Upgradepoint.h"
#pragma endregion

#pragma region using
#include <random>
using namespace std;
#pragma endregion

#pragma region functions
/// <summary>
/// load world string from txt file
/// </summary>
/// <param name="_pFile">file to load from</param>
/// <returns>world as string</returns>
string LoadWorldStringFromFile(const char* _pFile)
{
	// open file and if not opened return empty string
	ifstream file;
	file.open(_pFile);
	if (!file.is_open())
	{
		file.close();
		return "";
	}

	// text to return
	string text = "";

	// single line of file
	string line;

	// get every line from file and append to text
	while (getline(file, line))
	{
		text.append(line);
		text.append("\n");
	}

	// close file and return text
	file.close();
	return text;
}

/// <summary>
/// load world string from image file
/// </summary>
/// <param name="_pFile">image file to load from</param>
/// <returns>world as string</returns>
string LoadWorldStringFromImage(const char* _pFile) // by Lukas
{
	// text to return
	string text;

	// load surface from file
	SDL_Surface* pWorld = IMG_Load(_pFile);

	// get first pixel pointer
	char* pPixel = (char*)pWorld->pixels;

	// check every pixel
	for (int i = 0; i < pWorld->w * pWorld->h; i++)
	{
		// get rgb values from pixel
		uint8_t r = pPixel[0];
		uint8_t g = pPixel[1];
		uint8_t b = pPixel[2];

		// check values and add depending char
		//Void
		if (r == 255 && g == 255 && b == 255)
			text += '0';
		//Player
		else if (r == 255 && g == 255 && b == 0)
			text += 'S';
		//Exitzone
		else if (r == 255 && g == 0 && b == 255)
			text += 'X';
		//Enemy
		else if (r == 255 && g == 0 && b == 0)
			text += 'E';
		//Left Wall
		else if (r == 100 && g == 255 && b == 140)
			text += 'L';
		//Right Wall
		else if (r == 0 && g == 50 && b == 20)
			text += 'R';
		//Ceiling
		else if (r == 150 && g == 0 && b == 150)
			text += 'U';
		//Upgradpoint
		else if (r == 150 && g == 100 && b == 50)
			text += 'V';
		//Bottom Wall
		else if (r == 255 && g == 150 && b == 255)
			text += 'B';
		//Left Up Corner Inside
		else if (r == 0 && g == 250 && b == 250)
			text += '1';
		//Left Bottom Corner Inside
		else if (r == 10 && g == 50 && b == 100)
			text += '2';
		//Right Up Corner Inside
		else if (r == 0 && g == 0 && b == 255)
			text += '3';
		//Right Bottom Corner Inside
		else if (r == 130 && g == 130 && b == 170)
			text += '4';
		//Left Up Corner Outside
		else if (r == 80 && g == 70 && b == 240)
			text += '5';
		//Left Bottom Corner Outside
		else if (r == 0 && g == 0 && b == 70)
			text += '6';
		//Right Up Corner Outside
		else if (r == 0 && g == 125 && b == 125)
			text += '7';
		//Right Bottom Corner Outside
		else if (r == 50 && g == 50 && b == 80)
			text += '8';
		//Floor
		else if (r == 0 && g == 0 && b == 0)
			text += '#';

		// increase pixel by format
		pPixel += pWorld->format->BytesPerPixel;

		// if end of line add new line char
		if ((i + 1) % pWorld->w == 0)
			text += '\n';
	}

	// free surface and return text
	SDL_FreeSurface(pWorld);
	return text;
}

void GenerateFloorDetail(GWorldTile* _pWorldTile, CTexture* _pWorldTexture) // by Jonas
{
	int rnd = rand() % 1001; // random number between 0 and 1000

	int detailVariants = 4; // number of detail object variants
	int baseChance = 20; // 2% to place a detail object
	int chancePerDetail = baseChance / detailVariants;

	if (rnd >= baseChance) // return when base chance is exceeded
		return;

	CTexturedObject* pDetailTile = new CTexturedObject
	(
		"",
		SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
		SVector2()
	);
	pDetailTile->SetTexture(_pWorldTexture); // set tilemap as texture
	pDetailTile->SetColType(ECollisionType::NONE); // set col type of floor
	pDetailTile->SetLayer(1); // set layer one higher than regular floor

	SRect srcRect = SRect(GConfig::s_WorldBlockSourceWidth, GConfig::s_WorldBlockSourceHeight); // source rect by config values
	srcRect.x = GConfig::s_WorldBlockSourceWidth; // x of first floor detail frame in texture
	srcRect.y = 4 * GConfig::s_WorldBlockSourceHeight; // y of first floor detail frame in texture

	if (rnd >= chancePerDetail * 3)
	{
		srcRect.x += GConfig::s_WorldBlockSourceWidth;
	}
	else if (rnd >= chancePerDetail * 2)
	{
		srcRect.x += GConfig::s_WorldBlockSourceWidth * 2;
	}
	else if (rnd >= chancePerDetail * 1)
	{
		srcRect.y += GConfig::s_WorldBlockSourceHeight; // this is why a for loop couldnt work, the detail frames are not in one line in the tilemap
	}
	// else if (rnd >= 0) is unnecessary

	pDetailTile->SetSrcRect(srcRect); // set srcRect
	_pWorldTile->SetDetailObject(pDetailTile);
}

/// <summary>
/// load world from string
/// </summary>
void LoadWorldFromString()
{
	string world = "";
	world = LoadWorldStringFromImage(GetAssetPath("Config/World.png").c_str());

	// Keep for testing
	//world += "1UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU3\n";
	//world += "L######################################################E################R\n";
	//world += "L###########E###########################################################R\n";
	//world += "L##########################E########E###################################R\n";
	//world += "L###########################################E###########################R\n";
	//world += "L#S##################################E#####E############E###########X###R\n";
	//world += "L#######################################################################R\n";
	//world += "L##############################################E########################R\n";
	//world += "L############E#####################E########################E###########R\n";
	//world += "L##########E############################################################R\n";
	//world += "2BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB4";

	// width and height counter
	int width = -1, height = 0;

	// atlas texture of world
	CTexture* pGameTilemap = new CTexture("Texture/World/T_World.png");

	// check every char
	for (int i = 0; i < world.length(); i++)
	{
		if (world[i] == '0') // skip empty space
		{
			width++;
			continue;
		}

		if (world[i] == '\n')
		{
			height++; // increase height on new line
			width = -1; // reset width
			continue;
		}

		// increase width
		width++;
		// calculate world position of new objects
		SVector2 worldPos = SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight);

		// create tile and set it to floor srcRect as base
		GWorldTile* pNewWorldTile = new GWorldTile
		(
			"",
			SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
			worldPos
		);
		pNewWorldTile->SetTexture(pGameTilemap); // set tilemap as texture
		pNewWorldTile->SetColType(ECollisionType::NONE); // set col type of floor

		SRect srcRect = SRect(GConfig::s_WorldBlockSourceWidth, GConfig::s_WorldBlockSourceHeight); // source rect by config values
		srcRect.x = 0; // x of floor frame in texture
		srcRect.y = 4 * GConfig::s_WorldBlockSourceHeight; // y of floor frame in texture

		pNewWorldTile->SetSrcRect(srcRect); // set srcRect
		CTM->AddSceneObject(pNewWorldTile); // add to CTM

		// switch current char
		switch (world[i])
		{
		case '#': // Floor
		{
			GenerateFloorDetail(pNewWorldTile, pGameTilemap);
			break;
		}
		case 'E': //Enemy
		{
			// create enemy
			GEnemy* pEnemy = new GEnemy(
				"Texture/Character/Enemy/T_Enemy.png",
				SVector2(GConfig::s_EnemyWidth, GConfig::s_EnemyHeight),
				worldPos
			);
			CTM->AddPersistentObject(pEnemy);
			break;
		}
		case 'S': //Player
		{
			// create player
			GPlayer* pPlayer = new GPlayer
			(
				"Texture/Character/Player/T_Player.png",
				SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerTotalHeight),
				worldPos
			);
			CTM->AddPersistentObject(pPlayer);
			break;
		}
		case 'X': //Exit
		{
			// create Exitzone
			GExitzone* pExitzone = new GExitzone(
				"Texture/Exit/T_Exit.png",
				SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
				worldPos
			);
			pExitzone->SetColType(ECollisionType::NONE);
			pExitzone->SetTag("Exit");
			CTM->AddPersistentObject(pExitzone);
			break;
		}
		case 'V': //UpgradePoint
		{
			// create UpgradePoint
			GUpgradepoint* pUpgradepoint = new GUpgradepoint(
				"Texture/Upgrade/T_Upgradepoint.png",
				SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
				worldPos
			);
			pUpgradepoint->SetColType(ECollisionType::NONE);
			pUpgradepoint->SetTag("Upgradepoint");
			CTM->AddPersistentObject(pUpgradepoint);
			break;
		}
		case 'U': //Top Wall
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 0;
			srcRect.y = 0;
			break;
		}
		case 'B': //Bottom Wall
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 0;
			break;

		}
		case 'L': //Left Wall
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 2 * GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 0;
			break;
		}
		case 'R': //Right Wall
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 3 * GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 0;
			break;
		}
		case '1': //Left Up Corner
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 0;
			srcRect.y = 2 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '2': //Left Down Corner
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 2 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '3': //Right Up Corner
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 2 * GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 2 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '4': //Right Down Corner
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 3 * GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 2 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '5':
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 3 * GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 3 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '6':
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 0;
			srcRect.y = 3 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '7':
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 2 * GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 3 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case '8':
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = GConfig::s_WorldBlockSourceWidth;
			srcRect.y = 3 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		default:
			break;
		}

		pNewWorldTile->SetSrcRect(srcRect); // set srcRect
	}
}
#pragma endregion