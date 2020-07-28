#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "TexturedObject.h"
#include "Animation.h"

class CTexture;
class CRenderer;

class GExitzone :	public CTexturedObject
{

public:

	GExitzone(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFile, _size, _pos)
	{};

	virtual ~GExitzone() {}

	virtual void Render() override;


};

