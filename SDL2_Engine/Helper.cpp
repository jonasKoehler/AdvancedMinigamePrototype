#pragma region system include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Helper.h"
#pragma endregion

// get parent directory of path
string GetParentDirectory(string _path, int _depth)
{
	// if depth higher than one get parent directory
	if (_depth > 1)
		_path = GetParentDirectory(_path, _depth - 1);

	// get position of last folder
	size_t pos = _path.find_last_of("\\");

	// return sub string
	return (string::npos == pos)
		? ""
		: _path.substr(0, pos);
}

// get absolute asset path
string GetAssetPath(const char* _pPath, int _depth)
{
	// get parent directory by depth
	string path = GetParentDirectory(SDL_GetBasePath(), _depth);

	// return complete asset path
	return path.append("/Assets/").append(_pPath);
}