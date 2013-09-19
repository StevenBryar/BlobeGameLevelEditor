#include "Vector3.h"
#include "Vector2.h"
#include "MyMath.h"

Vector3::Vector3(float x,float y,float z) :
X(x),Y(y),Z(z){}
Vector3::Vector3(float v):
X(v),Y(v),Z(v){}
Vector3::Vector3(Vector2 v,float z):
X(v.X),Y(v.Y),Z(z){}

const Vector3 Vector3::Zero()
{
	Vector3 tempVec;
	tempVec.X = 0;
	tempVec.Y = 0;
	tempVec.Z = 0;

	return tempVec;
}
const Vector3 Vector3::One()
{
	Vector3 tempVec;
	tempVec.X = 1;
	tempVec.Y = 1;
	tempVec.Z = 1;

	return tempVec;
}

const float Vector3::Distance(const Vector3& vec3One,const Vector3& vec3Two)
{
	return (sqrtf(
		pow((vec3One.X + vec3Two.X),2.0f) 
		+ pow((vec3One.Y + vec3Two.Y),2.0f)
		+ pow((vec3One.Z + vec3Two.Z),2.0f)
		));
}
const void Vector3::Distance(const Vector3& vec3One,const Vector3& vec3Two,float distance)
{
		distance = Distance(vec3One,vec3Two);
}
const float Vector3::DistanceSquared(const Vector3& vec3One,const Vector3& vec3Two)
{
	float tempDistance = (sqrtf(
		pow((vec3One.X + vec3Two.X),2.0f) 
		+ pow((vec3One.Y + vec3Two.Y),2.0f)
		+ pow((vec3One.Z + vec3Two.Z),2.0f)
		));
	return (tempDistance * tempDistance);
}
const void Vector3::DistanceSquared(const Vector3& vec3One,const Vector3& vec3Two,float distance)
{
		distance = DistanceSquared(vec3One,vec3Two);
}
const float Vector3::Dot(const Vector3& vec3One,const Vector3& vec3Two)
{
	return (
		(vec3One.X * vec3Two.X)
		+ (vec3One.Y * vec3Two.Y)
		+ (vec3One.Z * vec3Two.Z)
		);
}
const void Vector3::Dot(const Vector3& vec3One,const Vector3& vec3Two,float dot)
{
		dot = Dot(vec3One,vec3Two);
}

const Vector3 Vector3::Normailze() const
{
	Vector3 tempVec = (*this);
	tempVec.X = tempVec.X / tempVec.Length();
	tempVec.Y = tempVec.Y / tempVec.Length();
	tempVec.Z = tempVec.Z / tempVec.Length();

	return tempVec;
}
const float Vector3::Length() const
{
	return sqrtf(powf(this->X,2.0f) + 
			powf(this->Y,2.0f) +
			powf(this->Z,2.0f));
}
const float Vector3::LengthSquared() const
{
	return powf(this->Length(),2.0f);
}
const Vector3 Vector3::Cross(const Vector3& vec3One,const Vector3& vec3Two)
{
	Vector3 crossProduct = Zero();
	crossProduct.X = (vec3One.Y*vec3Two.Z) - (vec3One.Z*vec3Two.Y);
	crossProduct.Y = (vec3One.Z*vec3Two.X) - (vec3One.X*vec3Two.Z);
	crossProduct.Z = (vec3One.X*vec3Two.Y) - (vec3One.Y*vec3Two.X);

	return crossProduct;
}
const void Vector3::Cross(const Vector3& vec3One,const Vector3& vec3Two,Vector3 cross)
{
	cross = Cross(vec3One,vec3Two);
}

const float Vector3::Angle(const Vector3& vec3One,const Vector3& vec3Two)
{
	float angle = Dot(vec3One,vec3Two);

	angle /= vec3One.Length() * 
			vec3Two.Length();
	angle = acos(angle) * OneEightyOverPI;

	return angle;
}
const void Vector3::Angle(const Vector3& vec3One,const Vector3& vec3Two,float angle)
{
	angle = Angle(vec3One,vec3Two);
}

const float* Vector3::ToArray() const
{
	float* theArray = new float[3];
	theArray[0] = this->X;
	theArray[1] = this->Y;
	theArray[2] = this->Z;

	return theArray;
}
