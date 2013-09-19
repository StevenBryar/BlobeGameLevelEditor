#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "inputListener.h"
#include <string>

class Sprite2d;

class GameObject{
public:
float getRotation() const;
float getPositionX() const;
float getOriginX() const;
float getPositionY() const;
float getOriginY() const;
float getHeight() const;
float getWidth() const;
virtual std::string getType();
std::string getName() const;
Sprite2d* getSprite() const;

void setRotation(const float& r);
void setPositionX(const float& x);
void setOriginX(const float& x);
void setPositionY(const float& y);
void setOriginY(const float& y);
void setHeight(const float& h);
void setWidth(const float& w);
void setSprite(Sprite2d* sprite);

void setPosition(const float& x,const float& y);
void setOrigin(const float& x,const float& y);
void setSize(const float& height,const float& width);

	GameObject();
	virtual ~GameObject();

	virtual void update();

protected:
	float m_Rotation;
	float m_PositionX;
	float m_PositionY;
	float m_OriginX;
	float m_OriginY;
	float m_Height;
	float m_Width;
	std::string m_Name;
	Sprite2d* m_Sprite;
};

#endif