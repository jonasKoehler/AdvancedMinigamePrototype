#pragma once

/// <summary>
/// 2d vector struct
/// </summary>
struct SVector2
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_x">x value</param>
	/// <param name="_y">y value</param>
	SVector2(float _x = 0.0f, float _y = 0.0f) : X(_x), Y(_y) {}
#pragma endregion

#pragma region operator
	/// <summary>
	/// vector2 + vector2
	/// </summary>
	/// <param name="_vec">vector2 to add</param>
	/// <returns>new vector2</returns>
	SVector2 operator + (SVector2 _vec)
	{
		// add other vector values to current and return
		return SVector2(X + _vec.X, Y + _vec.Y);
	}

	/// <summary>
	/// add another vector2 to this
	/// </summary>
	/// <param name="_vec">vector2 to add</param>
	void operator += (SVector2 _vec)
	{
		// subtract values from other vector2 to this
		X += _vec.X;
		Y += _vec.Y;
	}

	/// <summary>
	/// vector2 - vector2
	/// </summary>
	/// <param name="_vec">vector2 to subtract</param>
	/// <returns>new vector2</returns>
	SVector2 operator - (SVector2 _vec)
	{
		// subtract other vector values to current and return
		return SVector2(X - _vec.X, Y - _vec.Y);
	}

	/// <summary>
	/// subtract another vector2 to this
	/// </summary>
	/// <param name="_vec">vector2 to subtract</param>
	void operator -= (SVector2 _vec)
	{
		// subtract values from other vector2 to this
		X -= _vec.X;
		Y -= _vec.Y;
	}

	/// <summary>
	/// multiply this with float
	/// </summary>
	/// <param name="_value">float value</param>
	/// <returns>new vector2</returns>
	SVector2 operator * (float _value)
	{
		return SVector2(X * _value, Y * _value);
	}

	/// <summary>
	/// Square Magnitude
	/// </summary>
	/// <returns></returns>
	float SqrMagnitude()
	{
		return X * X + Y * Y;
	}
#pragma endregion

#pragma region public primitive variable
	/// <summary>
	/// x value
	/// </summary>
	float X = 0.0f;

	/// <summary>
	/// y value
	/// </summary>
	float Y = 0.0f;
#pragma endregion
};