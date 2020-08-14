#pragma once

/// <summary>
/// class with config variables
/// </summary>
class GConfig
{
public:
#pragma region public function
	/// <summary>
	/// load config variables from file
	/// </summary>
	static void LoadConfig();
#pragma endregion

#pragma region public primitive variable
	static int s_WorldBlockWidth;
	static int s_WorldBlockHeight;
	static int s_WorldBlockSourceWidth;
	static int s_WorldBlockSourceHeight;
	static int s_PlayerWidth;
	static int s_PlayerTotalHeight;
	static int s_PlayerTopHeight;
	static int s_PlayerBottomHeight;
	static int s_PlayerSrcWidth;
	static int s_PlayerTopSrcHeight;
	static int s_PlayerBottomSrcHeight;
	static int s_EnemyWidth;
	static int s_EnemyHeight;
#pragma endregion
};