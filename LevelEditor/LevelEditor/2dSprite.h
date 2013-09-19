#ifndef Sprite2d_H
#define Sprite2d_H

#include "SFML/Graphics.hpp"

class GameObject;
class Vector3;
#include <string>

class Sprite2d{
	friend class SpriteManager;
	friend class Renderer;
public:
	Sprite2d(GameObject* entity,sf::Texture* texture);
	~Sprite2d();
	void update();
	void scale(const float& x,const float& y);
	void setScale(const float& x,const float& y);
	void setRotation(const float& r);
	void setOrigin(const float& x,const float& y);
	void setPosition(const float& x,const float& y);
	void setWidth(const float& w);
	void setHeight(const float& h);
	void setColor(const Vector3& rgb,const int& a = 255);
	void setColor(const int& r,const int& g,const int& b,const int& a = 255);
	void setHiden(const bool& hidden);
	void setName(const std::string& name);
	Vector3 getColor() const;
	int getColorApha() const;
	float getRotation() const;
	float getOriginX() const;
	float getScaleX() const;
	float getPositionX() const;
	float getOriginY() const;
	float getScaleY() const;
	float getPositionY() const;
	float getWidth() const;
	float getHeight() const;
	std::string getName() const;
	bool getHidden() const;
	GameObject* getOwner() const;

	void move(const float& x,const float& y);
protected:
	sf::Sprite* m_Sprite;
	GameObject* m_Owner;
	int m_SpriteNumber;
	static int m_SpriteCount;
	bool m_Hidden;
	std::string m_Name;
};

#endif



