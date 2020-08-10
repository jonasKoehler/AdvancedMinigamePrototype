#pragma once

#pragma region system include
#include <string>
#include <fstream>
#include <SDL_image.h>
#pragma endregion

#pragma region engine include
#include "Texture.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
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
string LoadWorldStringFromImage(const char* _pFile)
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
		if (r == 0 && g == 0 && b == 0)
			text += '0';
		else if (r == 255 && g == 255 && b == 255)
			text += 'X';
		else if (r == 0 && g == 0 && b == 255)
			text += 'V';
		else if (r == 0 && g == 255 && b == 0)
			text += 'I';
		else if (r == 255 && g == 255 && b == 0)
			text += 'S';
		else if (r == 255 && g == 0 && b == 0)
			text += 'E';

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

	// 0 = air
	// # = wall
	// I = collectible
	// S = player start
	// E = enemy
	// X = exitzone by Lukas
	// \n = delimiter
	world += "#########################################################################\n";
	world += "#00000000000000000000000000000000000000000000000000000000000000000000000#\n";
	world += "#000E0000000000000000000000000000000000E000000000000000E0000000000E00000#\n";
	world += "#00000000000000000000000000000E000000000000000000000000E0000000E00000000#\n";
	world += "#000000000E0000000000000000000000000000000000000E000EE000000000E00000000#\n";
	world += "#0S000000000000000000000000000000000000000000000000000000000E000000000X0#\n";
	world += "#000000000000000000000000000000E0000000000000E0E00000E00000E000000000000#\n";
	world += "#000000000000000000000000000000000000000000000000000000000000000E000EE00#\n";
	world += "#00000000000000000000000000000000000000000000000EE0000E0000000E000000000#\n";
	world += "#00000000000000000000000E00000000000000E0000000000000000000000000000E000#\n";
	world += "#########################################################################";

	// width and height counter
	int width = -1, height = 0;

	// atlas texture of world
	CTexture* pGameTilemap = TTM->GetTexture("Texture/World/T_World.png");

	// create textured object
	CTexturedObject* pWorldObject = new CTexturedObject("", SVector2());

	// create background and render on screen
	pWorldObject->SetSrcRect(SRect(GConfig::s_WorldBlockSourceWidth, GConfig::s_WorldBlockSourceHeight, GConfig::s_WorldBlockSourceWidth, 0));
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
				SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerHeight),
				SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
			);

			pPlayer->SetSpeed(150.0f);
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
				SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerHeight),
				SVector2(width * GConfig::s_WorldBlockWidth, height * GConfig::s_WorldBlockHeight)
			);

			// set speed, collision type, activate gravity, add to content and set tag
			pEnemy->SetSpeed(100.0f);
			pEnemy->SetColType(ECollisionType::DYNAMIC);
			pEnemy->SetTag("Enemy");
			pEnemy->SetLayer(5);

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