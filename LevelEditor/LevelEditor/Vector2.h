#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>

class Matrix;
class Quaternion;


/*****VECTOR2*********/
class Vector2
{
	friend std::ostream& operator
		<<(std::ostream& output, const Vector2& v);

public:
	//members
	float X;
	float Y;
	//constructors
	Vector2(){};
	Vector2(float x,float y);
	Vector2(float v);
	//methods
	const Vector2 Normailze() const;
	const float Length() const;
	const float LengthSquared() const;
	//static methods
	static const Vector2 Zero();
	static const Vector2 One();
	static const float Distance(const Vector2& vec2One,const Vector2& vec2Two);
	static const void Distance(const Vector2& vec2One,const Vector2& vec2Two,float distance);
	static const float DistanceSquared(const Vector2& vec2One,const Vector2& vec2Two);
	static const void DistanceSquared(const Vector2& vec2One,const Vector2& vec2Two,float distance);
	static const float Dot(const Vector2& vec2One,const Vector2& vec2Two);
	static const void Dot(const Vector2& vec2One,const Vector2& vec2Two,float dot);
	static const float Angle(const Vector2& vec2One,const Vector2& vec2Two);
	static const void Angle(const Vector2& vec2One,const Vector2& vec2Two,float angle);

Vector2 operator =  (const Vector2& vecB);
Vector2 operator =  (const float& floatB);
};

Vector2 operator +  (const Vector2& vecA, const Vector2& vecB);
Vector2 operator +  (const Vector2& vecA, const float& floatB);
Vector2 operator +  (const float& floatA, const Vector2& vecB);
Vector2 operator += (Vector2& vecA,	const Vector2& vecB);
Vector2 operator += (Vector2& vecA,	const float& floatB);
Vector2 operator -  (const Vector2& vecA, const Vector2& vecB);
Vector2 operator -  (const Vector2& vecA, const float& floatB);
Vector2 operator -  (const float& floatA, const Vector2& vecB);
Vector2 operator -= (Vector2& vecA, const Vector2& vecB);
Vector2 operator -= (Vector2& vecA, const float& floatB);
Vector2 operator *  (const Vector2& vecA, const Vector2& vecB);
Vector2 operator *  (const Vector2& vecA, const float& floatB);
Vector2 operator *  (const float& floatA, const Vector2& vecB);
Vector2 operator *= (Vector2& vecA, const Vector2& vecB);
Vector2 operator *= (Vector2& vecA, const float& floatB);
Vector2 operator /  (const Vector2& vecA, const Vector2& vecB);
Vector2 operator /  (const Vector2& vecA, const float& floatB);
Vector2 operator /= (Vector2& vecA, const Vector2& vecB);
Vector2 operator /= (Vector2& vecA, const float& floatB);
bool	operator == (const Vector2& vecA, const Vector2& vecB);
bool	operator == (const Vector2& vecA, const float& floatB);
bool	operator != (const Vector2& vecA, const Vector2& vecB);
bool	operator != (const Vector2& vecA, const float& floatB);
bool	operator <	(const Vector2& vecA, const Vector2& vecB);
bool	operator <	(const Vector2& vecA, const float& floatB);
bool	operator >	(const Vector2& vecA, const Vector2& vecB);
bool	operator >	(const Vector2& vecA, const float& floatB);
bool	operator <=	(const Vector2& vecA, const Vector2& vecB);
bool	operator <=	(const Vector2& vecA, const float& floatB);
bool	operator >=	(const Vector2& vecA, const Vector2& vecB);
bool	operator >=	(const Vector2& vecA, const float& floatB);

inline Vector2 operator+(const Vector2& vecA, const Vector2& vecB)
{
	Vector2 tempVec = vecA;
	return tempVec+= vecB;
}

inline Vector2 operator+(const Vector2& vecA, const float& floatB)
{
	Vector2 tempVec = vecA;
	return tempVec+= floatB;
}

inline Vector2 operator+(const float& floatA, const Vector2& vecB)
{
	Vector2 tempVec = vecB;
	return tempVec+= floatA;
}

inline Vector2 operator+=(Vector2& vecA, const Vector2& vecB)
{
	vecA.X += vecB.X;
	vecA.Y += vecB.Y;
	return vecA;
}
inline Vector2 operator+=(Vector2& vecA, const float& floatB)
{
	vecA.X += floatB;
	vecA.Y += floatB;
	return vecA;
}

inline Vector2 operator-(const Vector2& vecA, const Vector2& vecB)
{
	Vector2 tempVec = vecA;
	return tempVec-= vecB;
}
inline Vector2 operator-(const Vector2& vecA, const float& floatB)
{
	Vector2 tempVec = vecA;
	return tempVec-= floatB;
}
inline Vector2 operator-(const float& floatA, const Vector2& vecB)
{
	Vector2 tempVec = vecB;
	return tempVec-= floatA;
}

inline Vector2 operator-=(Vector2& vecA, const Vector2& vecB)
{
	vecA.X -= vecB.X;
	vecA.Y -= vecB.Y;
	return vecA;
}
inline Vector2 operator-=(Vector2& vecA, const float& floatB)
{
	vecA.X -= floatB;
	vecA.Y -= floatB;
	return vecA;
}

inline Vector2 operator*(const Vector2& vecA, const Vector2& vecB)
{
	Vector2 tempVec = vecA;
	return tempVec*= vecB;
}
inline Vector2 operator*(const Vector2& vecA, const float& floatB)
{
	Vector2 tempVec = vecA;
	return tempVec*= floatB;
}
inline Vector2 operator*(const float& floatA, const Vector2& vecB)
{
	Vector2 tempVec = vecB;
	return tempVec*= floatA;
}

inline Vector2 operator*=(Vector2& vecA, const Vector2& vecB)
{
	vecA.X *= vecB.X;
	vecA.Y *= vecB.Y;
	return vecA;
}
inline Vector2 operator*=(Vector2& vecA, const float& floatB)
{
	vecA.X *= floatB;
	vecA.Y *= floatB;
	return vecA;
}

inline Vector2 operator/(const Vector2& vecA, const Vector2& vecB)
{
	Vector2 tempVec = vecA;
	return tempVec/= vecB;
}
inline Vector2 operator/(const Vector2& vecA, const float& floatB)
{
	Vector2 tempVec = vecA;
	return tempVec/= floatB;
}

inline Vector2 operator/=(Vector2& vecA, const Vector2& vecB)
{
	vecA.X /= vecB.X;
	vecA.Y /= vecB.Y;
	return vecA;
}
inline Vector2 operator/=(Vector2& vecA, const float& floatB)
{
	vecA.X /= floatB;
	vecA.Y /= floatB;
	return vecA;
}

inline Vector2 Vector2::operator=(const Vector2& vecB)
{
	this->X = vecB.X;
	this->Y = vecB.Y;
	return (*this);
}
inline Vector2 Vector2::operator=(const float& floatB)
{
	this->X = floatB;
	this->Y = floatB;
	return (*this);
}

inline bool operator==(const Vector2& vecA, const Vector2& vecB)
{
	if(vecA.X != vecB.X ||
		vecA.Y != vecB.Y)
		return false;

	return true;
}
inline bool operator==(const Vector2& vecA, const float& floatB)
{
	if(vecA.X != floatB ||
		vecA.Y != floatB)
		return false;

	return true;
}

inline bool operator!=(const Vector2& vecA, const Vector2& vecB)
{
	if(vecA.X == vecB.X &&
		vecA.Y == vecB.Y)
		return false;

	return true;
}
inline bool operator!=(const Vector2& vecA, const float& floatB)
{
	if(vecA.X == floatB &&
		vecA.Y == floatB)
		return false;

	return true;
}

inline bool operator<(const Vector2& vecA, const Vector2& vecB)
{
	return vecA.Length() < 
		vecB.Length();
}
inline bool operator<(const Vector2& vecA, const float& floatB)
{
	return vecA.Length() < 
		floatB;
}

inline bool operator>(const Vector2& vecA, const Vector2& vecB)
{
	return vecA.Length() > 
		vecB.Length();
}
inline bool operator>(const Vector2& vecA, const float& floatB)
{
	return vecA.Length() > 
		floatB;
}

inline bool operator<=(const Vector2& vecA, const Vector2& vecB)
{
	return (vecA < vecB ? true : vecA == vecB);
}
inline bool operator<=(const Vector2& vecA, const float& floatB)
{
	return (vecA < floatB ? true : vecA == floatB);
}

inline bool operator>=(const Vector2& vecA, const Vector2& vecB)
{
	return (vecA > vecB ? true : vecA == vecB);
}
inline bool operator>=(const Vector2& vecA, const float& floatB)
{
	return (vecA > floatB ? true : vecA == floatB);
}
inline std::ostream& operator
		<<(std::ostream& output, const Vector2& v)
{
	output << "(" << v.X << "," << v.Y << ")";
	return output;
}
#endif