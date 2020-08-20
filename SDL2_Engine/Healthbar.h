#pragma once
#include "TexturedObject.h"
#include "Vector2.h"
#include "Rect.h"
#include "TexturedObject.h"
#include "Animation.h"

class GHealthbar : public CTexturedObject
{
	class CTexture;
	class CRenderer;

public:

	GHealthbar(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFile, _size, _pos)
	{};

	virtual ~GHealthbar() {}

	virtual void Render() override;
};

