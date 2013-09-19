#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Matrix;
class Quaternion;
class Vector2;

/*****Vector3*********/
class Vector3
{
	friend std::ostream& operator
		<<(std::ostream& output, const Vector3& v);

public:
	//members
	float X;
	float Y;
	float Z;
	//constructors
	Vector3(){};
	Vector3(float x,float y,float z);
	Vector3(float v);
	Vector3(Vector2 v,float z);

	//methods
	const Vector3 Normailze() const;
	const float Length() const;
	const float LengthSquared() const;
	const float* ToArray() const;
	//static methods
	static const Vector3 Zero();
	static const Vector3 One();
	static const float Distance(const Vector3& vec3One,const Vector3& vec3Two);
	static const void Distance(const Vector3& vec3One,const Vector3& vec3Two,float distance);
	static const float DistanceSquared(const Vector3& vec3One,const Vector3& vec3Two);
	static const void DistanceSquared(const Vector3& vec3One,const Vector3& vec3Two,float distance);
	static const float Dot(const Vector3& vec3One,const Vector3& vec3Two);
	static const void Dot(const Vector3& vec3One,const Vector3& vec3Two,float dot);
	static const Vector3 Cross(const Vector3& vec3One,const Vector3& vec3Two);
	static const void Cross(const Vector3& vec3One,const Vector3& vec3Two,Vector3 cross);
	static const float Angle(const Vector3& vec3One,const Vector3& vec3Two);
	static const void Angle(const Vector3& vec3One,const Vector3& vec3Two,float angle);

	Vector3 operator =  (const Vector3& vecB);
	Vector3 operator =  (const float& floatB);
};

Vector3 operator +  (const Vector3& vecA, const Vector3& vecB);
Vector3 operator +  (const Vector3& vecA, const float& floatB);
Vector3 operator +  (const float& floatA, const Vector3& vecB);
Vector3 operator += (Vector3& vecA,	const Vector3& vecB);
Vector3 operator += (Vector3& vecA,	const float& floatB);
Vector3 operator -  (const Vector3& vecA, const Vector3& vecB);
Vector3 operator -  (const Vector3& vecA, const float& floatB);
Vector3 operator -  (const float& floatA, const Vector3& vecB);
Vector3 operator -= (Vector3& vecA, const Vector3& vecB);
Vector3 operator -= (Vector3& vecA, const float& floatB);
Vector3 operator *  (const Vector3& vecA, const Vector3& vecB);
Vector3 operator *  (const Vector3& vecA, const float& floatB);
Vector3 operator *  (const float& floatA, const Vector3& vecB);
Vector3 operator *= (Vector3& vecA, const Vector3& vecB);
Vector3 operator *= (Vector3& vecA, const float& floatB);
Vector3 operator /  (const Vector3& vecA, const Vector3& vecB);
Vector3 operator /  (const Vector3& vecA, const float& floatB);
Vector3 operator /= (Vector3& vecA, const Vector3& vecB);
Vector3 operator /= (Vector3& vecA, const float& floatB);
bool	operator == (const Vector3& vecA, const Vector3& vecB);
bool	operator == (const Vector3& vecA, const float& floatB);
bool	operator != (const Vector3& vecA, const Vector3& vecB);
bool	operator != (const Vector3& vecA, const float& floatB);
bool	operator <	(const Vector3& vecA, const Vector3& vecB);
bool	operator <	(const Vector3& vecA, const float& floatB);
bool	operator >	(const Vector3& vecA, const Vector3& vecB);
bool	operator >	(const Vector3& vecA, const float& floatB);
bool	operator <=	(const Vector3& vecA, const Vector3& vecB);
bool	operator <=	(const Vector3& vecA, const float& floatB);
bool	operator >=	(const Vector3& vecA, const Vector3& vecB);
bool	operator >=	(const Vector3& vecA, const float& floatB);

inline Vector3 operator+(const Vector3& vecA, const Vector3& vecB)
{
	Vector3 tempVec = vecA;
	return tempVec+= vecB;
}

inline Vector3 operator+(const Vector3& vecA, const float& floatB)
{
	Vector3 tempVec = vecA;
	return tempVec+= floatB;
}

inline Vector3 operator+(const float& floatA, const Vector3& vecB)
{
	Vector3 tempVec = vecB;
	return tempVec+= floatA;
}

inline Vector3 operator+=(Vector3& vecA, const Vector3& vecB)
{
	vecA.X += vecB.X;
	vecA.Y += vecB.Y;
	vecA.Z += vecB.Z;
	return vecA;
}
inline Vector3 operator+=(Vector3& vecA, const float& floatB)
{
	vecA.X += floatB;
	vecA.Y += floatB;
	vecA.Z += floatB;
	return vecA;
}

inline Vector3 operator-(const Vector3& vecA, const Vector3& vecB)
{
	Vector3 tempVec = vecA;
	return tempVec-= vecB;
}
inline Vector3 operator-(const Vector3& vecA, const float& floatB)
{
	Vector3 tempVec = vecA;
	return tempVec-= floatB;
}
inline Vector3 operator-(const float& floatA, const Vector3& vecB)
{
	Vector3 tempVec = vecB;
	return tempVec-= floatA;
}

inline Vector3 operator-=(Vector3& vecA, const Vector3& vecB)
{
	vecA.X -= vecB.X;
	vecA.Y -= vecB.Y;
	vecA.Z -= vecB.Z;
	return vecA;
}
inline Vector3 operator-=(Vector3& vecA, const float& floatB)
{
	vecA.X -= floatB;
	vecA.Y -= floatB;
	vecA.Z -= floatB;
	return vecA;
}

inline Vector3 operator*(const Vector3& vecA, const Vector3& vecB)
{
	Vector3 tempVec = vecA;
	return tempVec*= vecB;
}
inline Vector3 operator*(const Vector3& vecA, const float& floatB)
{
	Vector3 tempVec = vecA;
	return tempVec*= floatB;
}
inline Vector3 operator*(const float& floatA, const Vector3& vecB)
{
	Vector3 tempVec = vecB;
	return tempVec*= floatA;
}

inline Vector3 operator*=(Vector3& vecA, const Vector3& vecB)
{
	vecA.X *= vecB.X;
	vecA.Y *= vecB.Y;
	vecA.Z *= vecB.Z;
	return vecA;
}
inline Vector3 operator*=(Vector3& vecA, const float& floatB)
{
	vecA.X *= floatB;
	vecA.Y *= floatB;
	vecA.Z *= floatB;
	return vecA;
}

inline Vector3 operator/(const Vector3& vecA, const Vector3& vecB)
{
	Vector3 tempVec = vecA;
	return tempVec/= vecB;
}
inline Vector3 operator/(const Vector3& vecA, const float& floatB)
{
	Vector3 tempVec = vecA;
	return tempVec/= floatB;
}

inline Vector3 operator/=(Vector3& vecA, const Vector3& vecB)
{
	vecA.X /= vecB.X;
	vecA.Y /= vecB.Y;
	vecA.Z /= vecB.Z;
	return vecA;
}
inline Vector3 operator/=(Vector3& vecA, const float& floatB)
{
	vecA.X /= floatB;
	vecA.Y /= floatB;
	vecA.Z /= floatB;
	return vecA;
}

inline Vector3 Vector3::operator=(const Vector3& vecB)
{
	this->X = vecB.X;
	this->Y = vecB.Y;
	this->Z = vecB.Z;
	return (*this);
}
inline Vector3 Vector3::operator=(const float& floatB)
{
	this->X = floatB;
	this->Y = floatB;
	this->Z = floatB;
	return (*this);
}

inline bool operator==(const Vector3& vecA, const Vector3& vecB)
{
	if(vecA.X != vecB.X ||
		vecA.Y != vecB.Y ||
		vecA.Z != vecB.Z)
		return false;

	return true;
}
inline bool operator==(const Vector3& vecA, const float& floatB)
{
	if(vecA.X != floatB ||
		vecA.Y != floatB ||
		vecA.Z != floatB)
		return false;

	return true;
}

inline bool operator!=(const Vector3& vecA, const Vector3& vecB)
{
	if(vecA == vecB)
		return false;

	return true;
}
inline bool operator!=(const Vector3& vecA, const float& floatB)
{
	if(vecA == floatB)
		return false;

	return true;
}

inline bool operator<(const Vector3& vecA, const Vector3& vecB)
{
	return vecA.Length() < 
		vecB.Length();
}
inline bool operator<(const Vector3& vecA, const float& floatB)
{
	return vecA.Length() < 
		floatB;
}

inline bool operator>(const Vector3& vecA, const Vector3& vecB)
{
	return vecA.Length() > 
		vecB.Length();
}
inline bool operator>(const Vector3& vecA, const float& floatB)
{
	return vecA.Length() > 
		floatB;
}

inline bool operator<=(const Vector3& vecA, const Vector3& vecB)
{
	return (vecA < vecB ? true : vecA == vecB);
}
inline bool operator<=(const Vector3& vecA, const float& floatB)
{
	return (vecA < floatB ? true : vecA == floatB);
}

inline bool operator>=(const Vector3& vecA, const Vector3& vecB)
{
	return (vecA > vecB ? true : vecA == vecB);
}
inline bool operator>=(const Vector3& vecA, const float& floatB)
{
	return (vecA > floatB ? true : vecA == floatB);
}

inline std::ostream& operator
		<<(std::ostream& output, const Vector3& v)
{
	output << "(" << v.X << "," << v.Y << "," << v.Z << ")";
	return output;
}
#endif