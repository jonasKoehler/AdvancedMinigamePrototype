#pragma once

#pragma region system include
#include <string>
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// get parent directory of path
/// </summary>
/// <param name="_path">path to check</param>
/// <param name="_depth">depth to go back in directory</param>
/// <returns>parent directory of path</returns>
string GetParentDirectory(string _path, int _depth = 1);

/// <summary>
/// get absolute asset path
/// </summary>
/// <param name="_path">relative asset path</param>
/// <param name="_depth">directories to go back</param>
/// <returns>absolute asset path</returns>
string GetAssetPath(const char* _pPath, int _depth = 4);