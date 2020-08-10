#pragma region project include
#include "TextureManagement.h"
#include "Texture.h"
#pragma endregion

#pragma region destructor
// destructor
CTextureManagement::~CTextureManagement()
{
	// while textures left
	while (m_textures.size())
	{
		// get first texture and delete it
		CTexture* pTexture = m_textures.begin()->second;
		delete pTexture;

		// remove first texture file name pair
		m_textures.erase(m_textures.begin()->first);
	}
}
#pragma endregion

#pragma region public function
// get textures from file
CTexture* CTextureManagement::GetTexture(const char* _pFileName)
{
	// if no file name of empty return nullptr
	if (!_pFileName || _pFileName == "")
		return nullptr;

	// try to find texture by file name key
	map<const char*, CTexture*>::iterator it = m_textures.find(_pFileName);

	// if texture found return it
	if (it != m_textures.end())
		return it->second;

	// create new texture
	CTexture* pTexture = new CTexture(_pFileName);

	// instert texture file name pair at begin
	m_textures.insert(m_textures.begin(), pair<const char*, CTexture*>(_pFileName, pTexture));

	// return texture
	return pTexture;
}
#pragma endregion