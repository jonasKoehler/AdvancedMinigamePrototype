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
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region function
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
		//Bottom
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
			text += 'D';
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

/// <summary>
/// load world from string
/// </summary>
void LoadWorldFromString()
{
	string world = "";
	world = LoadWorldStringFromImage(GetAssetPath("Config/World.png").c_str());

	// Keep for testing
	/*world += "#########################################################################\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#00000000000000000E00000000000000000000000000000000000000000000000000000#\n";
	world += "#000000000000000000000000000000000000000000000000E0000000000000000000000#\n";
	world += "#000000000000000000000000000000000000000000000000000000E0000000000000000#\n";
	world += "#0000000000000000000000000000000000S000000000000000000000000000000000000#\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#00000000000000E000000000000000000000000000000000000000000E0000000000000#\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#########################################################################";*/

	// width and height counter
	int width = -1, height = 0;

	// atlas texture of world
	CTexture* pGameTilemap = new CTexture("Texture/World/T_World.png");

	// check every char
	for (int i = 0; i < world.length(); i++)
	{
		// if current char is new line

		if (world[i] == '0')
		{
			width++;
			continue;
		}
		if (world[i] == '\n')
		{
			height++; // increase height
			width = -1; // reset width
			continue; // start new loop
		}

		// increase width
		width++;


		if (world[i] == 'S') // if char indicates the player
		{
			// create player
			GPlayer* pPlayer = new GPlayer
			(
				"Texture/Character/Player/T_Player.png",
				SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerTotalHeight),
				SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
			);
			CTM->AddSceneObject(pPlayer);
			continue; // check next char
		}

		if (world[i] == 'E') // if char indicates an enemy
		{
			// create enemy
			GEnemy* pEnemy = new GEnemy(
				"Texture/Character/Enemy/T_Enemy.png",
				SVector2(GConfig::s_EnemyWidth, GConfig::s_EnemyHeight),
				SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
			);
			CTM->AddSceneObject(pEnemy);
			continue; // check next char
		}

		if (world[i] == 'X') // if char indicates the exit
		{
			// create Exitzone
			GExitzone* pExitzone = new GExitzone(
				"Texture/Exit/T_Exit.png",
				SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
				SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
			);
			pExitzone->SetColType(ECollisionType::STATIC);
			pExitzone->SetTag("Exit");
			CTM->AddSceneObject(pExitzone);

			continue; // check next char
		}


		if (world[i] == 'V') // if char indicates an Upgradepoint
		{
			// create Exitzone
			GExitzone* pUpgradepoint = new GExitzone(
				"Texture/Exit/T_Exit.png",
				SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
				SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
			);
			pUpgradepoint->SetColType(ECollisionType::STATIC);
			pUpgradepoint->SetTag("Upgradpoint");
			CTM->AddSceneObject(pUpgradepoint);

			continue; // check next char
		}

		// when this is reached the char is meant to be a TexturedObject
		// create textured object
		CTexturedObject* pNewWorldTile = new CTexturedObject
		(
			"",
			SVector2(GConfig::s_WorldBlockWidth, GConfig::s_WorldBlockHeight),
			SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
		);

		pNewWorldTile->SetTexture(pGameTilemap); // set tilemap as texture
		pNewWorldTile->SetColType(ECollisionType::NONE); // world tiles have no collision by default

		SRect srcRect = SRect(GConfig::s_WorldBlockSourceWidth, GConfig::s_WorldBlockSourceHeight); // source rect by config values

		// switch current char
		switch (world[i])
		{
		case '#': //Bottom
		{
			pNewWorldTile->SetColType(ECollisionType::NONE); 
			srcRect.x = 0;
			srcRect.y = 4 * GConfig::s_WorldBlockSourceHeight;
			break;
		}
		case 'U': //Ceiling
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC); 
			srcRect.x = 0;
			srcRect.y = 0;
			break;
		}
		case 'D': //Bottom Wall
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
		case '1': // Left Up Corner
		{
			pNewWorldTile->SetColType(ECollisionType::STATIC);
			srcRect.x = 0;
			srcRect.y = 2*  GConfig::s_WorldBlockSourceHeight;
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
			srcRect.x =0;
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
			srcRect.x = GConfig::s_WorldBlockSourceWidth ;
			srcRect.y = 3* GConfig::s_WorldBlockSourceHeight;
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