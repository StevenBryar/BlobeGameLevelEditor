#include "2dSprite.h"
#include "GameObject.h"
#include "MyMath.h"
#include <stdlib.h>
#include "Vector3.h"

int Sprite2d::m_SpriteCount = 0;

Sprite2d::Sprite2d(GameObject* entity,
					sf::Texture* texture) :
	m_Owner(entity){
		m_Sprite = new sf::Sprite(*texture);
		m_SpriteNumber = ++m_SpriteCount;
		m_Hidden = false;
		update();
}
Sprite2d::~Sprite2d(){
	m_Owner = NULL;
	if(m_Sprite != NULL){
		delete m_Sprite;
		m_Sprite = NULL;
	}
}
void Sprite2d::update(){
	if(m_Owner != NULL){
		setOrigin(m_Owner->getOriginX(),m_Owner->getOriginY());
		setPosition(m_Owner->getPositionX() + m_Owner->getOriginX(),
					m_Owner->getPositionY() + m_Owner->getOriginY());
		setRotation(m_Owner->getRotation());
		setScale(m_Owner->getWidth()/m_Sprite->getLocalBounds().width,
			m_Owner->getHeight()/m_Sprite->getLocalBounds().height);
	}
}
void Sprite2d::move(const float& x,const float& y){
	setPosition(m_Sprite->getPosition().x + x,
				m_Sprite->getPosition().y + y);
}

void Sprite2d::scale(const float& x,const float& y){m_Sprite->scale(x,y);}
void Sprite2d::setRotation(const float& r){m_Sprite->setRotation(r);}
void Sprite2d::setOrigin(const float& x,const float& y){m_Sprite->setOrigin(x,y);}
void Sprite2d::setScale(const float& x,const float& y){m_Sprite->setScale(x,y);}
void Sprite2d::setPosition(const float& x,const float& y){m_Sprite->setPosition(x,y);}
void Sprite2d::setColor(const Vector3& rgb,const int& a){m_Sprite->setColor(sf::Color(rgb.X,rgb.Y,rgb.Z,a));}
void Sprite2d::setColor(const int& r,const int& g,const int& b,const int& a){m_Sprite->setColor(sf::Color(r,g,b,a));}
void Sprite2d::setHiden(const bool& hidden){m_Hidden = hidden;}
void Sprite2d::setName(const std::string& name){m_Name = name;}
void Sprite2d::setWidth(const float& w){
	setScale(w/m_Sprite->getLocalBounds().width , getScaleY());
}
void Sprite2d::setHeight(const float& h){
	setScale(getScaleX() , h/m_Sprite->getLocalBounds().height);
}
bool Sprite2d::getHidden() const{return m_Hidden;}
float Sprite2d::getRotation() const{return m_Sprite->getRotation();}
float Sprite2d::getOriginX() const{return m_Sprite->getOrigin().x;}
float Sprite2d::getScaleX() const{return m_Sprite->getScale().x;}
float Sprite2d::getPositionX() const{return m_Sprite->getPosition().x;}
float Sprite2d::getOriginY() const{return m_Sprite->getOrigin().y;}
float Sprite2d::getScaleY() const{return m_Sprite->getScale().y;}
float Sprite2d::getPositionY()const{return m_Sprite->getPosition().y;}
float Sprite2d::getWidth() const{return (m_Sprite->getLocalBounds().width*getScaleX());}
float Sprite2d::getHeight() const{return (m_Sprite->getLocalBounds().height*getScaleY());}
Vector3 Sprite2d::getColor() const{return Vector3(m_Sprite->getColor().r,m_Sprite->getColor().g,m_Sprite->getColor().b);}
int Sprite2d::getColorApha() const{return m_Sprite->getColor().a;}
std::string Sprite2d::getName() const{return m_Name;}
GameObject* Sprite2d::getOwner() const{return m_Owner;}