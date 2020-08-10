#pragma region system include
#include <map>
#pragma endregion

#pragma region project include
#include "Engine.h"
#pragma endregion

#pragma region forward decleration
class CTexture;
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region value macro
#define TTM CEngine::Get()->GetTTM()
#pragma endregion

/// <summary>
/// class to store all textures
/// </summary>
class CTextureManagement
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CTextureManagement() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CTextureManagement();
#pragma endregion

#pragma region public function
	/// <summary>
	/// get textures from file
	/// </summary>
	/// <param name="_pFileName">file name</param>
	/// <returns>texture reference</returns>
	CTexture* GetTexture(const char* _pFileName);
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// map with all textures
	/// </summary>
	map<const char*, CTexture*> m_textures;
#pragma endregion
};