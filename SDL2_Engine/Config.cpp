#pragma region system include
#include <string>
#include <fstream>
#pragma endregion

#pragma region engine include
#include "Helper.h"
#pragma endregion

#pragma region game include
#include "Config.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region variable
int GConfig::s_WorldBlockWidth = 0;
int GConfig::s_WorldBlockHeight = 0;
int GConfig::s_WorldBlockSourceWidth = 0;
int GConfig::s_WorldBlockSourceHeight = 0;
int GConfig::s_PlayerWidth = 0;
int GConfig::s_PlayerHeight = 0;
int GConfig::s_PlayerSrcWalkWidth = 0;
int GConfig::s_PlayerSrcWalkHeight = 0;
#pragma endregion

#pragma region public function
// load config variables from file
void GConfig::LoadConfig()
{
	// string for ever line in file
	string line = "";

	// open file and if not opened return
	ifstream file;
	file.open(GetAssetPath("Config/Config.txt").c_str());
	if (!file.is_open())
		return;

	// get every line from file
	while (getline(file, line))
	{
		// flow variables
		string name = "";
		string value = "";
		bool getName = true;

		// check every char
		for (int i = 0; i < line.length(); i++)
		{
			// if seperator set get name false and continue to next char
			if (line[i] == ':')
			{
				getName = false;
				continue;
			}

			// add current char depending on get name
			if (getName)
				name += line[i];
			else
				value += line[i];
		}

		// check every variable name and set depending variable by value
		if (name == "WorldBlockWidth")
			s_WorldBlockWidth = atoi(value.c_str());
		else if (name == "WorldBlockHeight")
			s_WorldBlockHeight = atoi(value.c_str());
		else if (name == "WorldBlockSourceWidth")
			s_WorldBlockSourceWidth = atoi(value.c_str());
		else if (name == "WorldBlockSourceHeight")
			s_WorldBlockSourceHeight = atoi(value.c_str());
		else if (name == "PlayerWidth")
			s_PlayerWidth = atoi(value.c_str());
		else if (name == "PlayerHeight")
			s_PlayerHeight = atoi(value.c_str());
		else if (name == "PlayerSrcWalkWidth")
			s_PlayerSrcWalkWidth = atoi(value.c_str());
		else if (name == "PlayerSrcWalkHeight")
			s_PlayerSrcWalkHeight = atoi(value.c_str());
	}
}
#pragma endregion