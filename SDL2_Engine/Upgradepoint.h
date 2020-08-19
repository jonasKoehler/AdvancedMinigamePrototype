#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "TexturedObject.h"
#include "Animation.h"

class CTexture;
class CRenderer;

class GUpgradepoint : public CTexturedObject
{

public:

	GUpgradepoint(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFile, _size, _pos)
	{};

	virtual ~GUpgradepoint() {}

	virtual void Render() override;


};

