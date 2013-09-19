#include "GameObject.h"
#include "spriteManager.h"
#include "2dSprite.h"

GameObject::GameObject() :
m_PositionX(0),m_PositionY(0),
m_Rotation(0),
m_OriginX(0),m_OriginY(0),
m_Height(64),m_Width(64),m_Name(""),
m_Sprite(NULL){}

GameObject::~GameObject(){
	SpriteManager::instance()->deleteSprite(m_Sprite);
}
void GameObject::update(){}

std::string GameObject::getType(){
	return "GameObject";
}
std::string GameObject::getName() const{return m_Name;}
float GameObject::getRotation() const{return m_Rotation;}
float GameObject::getPositionX() const{return m_PositionX;}
float GameObject::getOriginX() const{return m_OriginX;}
float GameObject::getPositionY() const{return m_PositionY;}
float GameObject::getOriginY() const{return m_OriginY;}
float GameObject::getHeight() const{return m_Height;}
float GameObject::getWidth() const{return m_Width;}
Sprite2d* GameObject::getSprite() const{return m_Sprite;}

void GameObject::setRotation(const float& r){m_Rotation = r;}
void GameObject::setPositionX(const float& x){m_PositionX = x;}
void GameObject::setOriginX(const float& x){m_OriginX = x;}
void GameObject::setPositionY(const float& y){m_PositionY = y;}
void GameObject::setOriginY(const float& y){m_OriginY = y;}
void GameObject::setHeight(const float& h){m_Height = h;}
void GameObject::setWidth(const float& w){m_Width = w;}
void GameObject::setSprite(Sprite2d* sprite){
	if(m_Sprite){
	SpriteManager::instance()->deleteSprite(m_Sprite);
	}
	m_Sprite = sprite;
	
}

void GameObject::setPosition(const float& x,const float& y){
	setPositionX(x);
	setPositionY(y);
}
void GameObject::setOrigin(const float& x,const float& y){
	setOriginX(x);
	setOriginY(y);
}
void GameObject::setSize(const float& height,const float& width){
	setHeight(height);
	setWidth(width);
}