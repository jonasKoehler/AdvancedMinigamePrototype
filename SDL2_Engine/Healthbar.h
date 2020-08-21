#pragma once
#include "TexturedObject.h"

class GPlayer;

class GHealthbar : public CObject
{
#pragma region constructor / destructor
public:
	GHealthbar(SVector2 _size, SVector2 _pos)
	{
		m_Frame = CTexturedObject("Texture/UI/IngameHUD/T_Healthbar.png", _size, _pos);
		m_Frame.SetSrcRect(SRect(600, 80, 0, 80));
		m_Frame.SetInWorld(false);

		m_Bar = CTexturedObject("Texture/UI/IngameHUD/T_Healthbar.png", _size, _pos);
		m_Bar.SetSrcRect(SRect(600, 80, 0, 0));
		m_Bar.SetInWorld(false);

		m_BaseWidth = _size.X;
		m_position = _pos;
	}

	~GHealthbar()
	{

	}
#pragma endregion

#pragma region public member functions
public:
	void Render() override;

	void Update(float _deltaSeconds) override;
#pragma endregion

#pragma region private member variables
	CTexturedObject m_Frame;
	CTexturedObject m_Bar;
	int m_BaseWidth = 0; // base width of the bar
	GPlayer* m_pPlayer = nullptr; // player reference
	float m_PrevPlayerHealth = 0; // playerhealth the last time he took dmg
	float m_MaxPlayerHealth = 0; // player health at start
#pragma endregion
};

