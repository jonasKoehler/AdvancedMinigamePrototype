#pragma region project include
#include "Font.h"
#include "Helper.h"
#pragma endregion

#pragma region constructor
// constructor
CFont::CFont(const char* _pFile, int _size)
{
	// create font
	m_pSdlFont = TTF_OpenFont(GetAssetPath(_pFile).c_str(), _size);
}
#pragma endregion

#pragma region destructor
// desructor
CFont::~CFont()
{
	// close font
	TTF_CloseFont(m_pSdlFont);
}
#pragma endregion