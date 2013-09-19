#include "Vector2.h"
#include "MyMath.h"

Vector2::Vector2(float x,float y) :
X(x),Y(y){}

Vector2::Vector2(float v) :
X(v),Y(v){}

const Vector2 Vector2::Zero()
{
	Vector2 tempVec;
	tempVec.X = 0;
	tempVec.Y = 0;

	return tempVec;
}
const Vector2 Vector2::One()
{
	Vector2 tempVec;
	tempVec.X = 1;
	tempVec.Y = 1;

	return tempVec;
}

const float Vector2::Distance(const Vector2& vec2One,const Vector2& vec2Two)
{
	return (sqrtf(
		pow((vec2One.X + vec2Two.X),2.0f) 
		+ pow((vec2One.Y + vec2Two.Y),2.0f)
		));
}
const void Vector2::Distance(const Vector2& vec2One,const Vector2& vec2Two,float distance)
{
		distance = Distance(vec2One,vec2Two);
}
const float Vector2::DistanceSquared(const Vector2& vec2One,const Vector2& vec2Two)
{
	float tempDistance = (sqrtf(
		pow((vec2One.X + vec2Two.X),2.0f) 
		+ pow((vec2One.Y + vec2Two.Y),2.0f)
		));
	return (tempDistance * tempDistance);
}
const void Vector2::DistanceSquared(const Vector2& vec2One,const Vector2& vec2Two,float distance)
{
		distance = DistanceSquared(vec2One,vec2Two);
}
const float Vector2::Dot(const Vector2& vec2One,const Vector2& vec2Two)
{
	return (
		(vec2One.X * vec2Two.X)
		+ (vec2One.Y * vec2Two.Y)
		);
}
const void Vector2::Dot(const Vector2& vec2One,const Vector2& vec2Two,float dot)
{
		dot = Dot(vec2One,vec2Two);
}

const float Vector2::Angle(const Vector2& vec2One,const Vector2& vec2Two)
{
	float angle = Dot(vec2One,vec2Two);

	angle /= vec2One.Length() * 
			vec2Two.Length();
	angle = acos(angle) * OneEightyOverPI;

	return angle;
}
const void Vector2::Angle(const Vector2& vec2One,const Vector2& vec2Two,float angle)
{
	angle = Angle(vec2One,vec2Two);
}

const Vector2 Vector2::Normailze() const
{
	Vector2 tempVec = (*this);
	tempVec = tempVec / tempVec.Length();

	return tempVec;
}
const float Vector2::Length() const
{
	return sqrtf(powf(this->X,2.0f) + 
			powf(this->Y,2.0f));
}
const float Vector2::LengthSquared() const
{
	return powf(this->Length(),2.0f);
}


