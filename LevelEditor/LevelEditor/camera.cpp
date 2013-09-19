#include "Camera.h"

Camera::Camera() :
m_View(NULL),m_Follow(NULL){}
Camera::Camera(sf::View* view) :
m_View(view),m_Follow(NULL){}
Camera::~Camera(){
	if(m_View != NULL){
		delete m_View;
		m_View = NULL;
	}
		m_Follow = NULL;
}

void Camera::moveTo(const float& x,const float& y){
	float r = m_View->getRotation();
	sf::Vector2f size = m_View->getSize();
	m_View->reset(sf::FloatRect(x,y,size.x,size.y));
	m_View->setRotation(r);
}

void Camera::rotate(const float& rotation){m_View->rotate(rotation);}
void Camera::centre(const float& x,const float& y){m_View->setCenter(x,y);}
void Camera::zoom(const float& z){m_View->zoom(z);}
void Camera::move(const float& x,const float& y){m_View->move(x,y);}

void Camera::setSize(const float& x,const float& y){m_View->setSize(x,y);}
void Camera::setView(sf::View* view){m_View = view;}
void Camera::setFollow(GameObject* thing){m_Follow = thing;}

float Camera::getRotation() const{return m_View->getRotation();}
GameObject* Camera::getFollow() const{return m_Follow;}
sf::View* Camera::getView() const{return m_View;}
float Camera::getWidth() const{return m_View->getSize().x;}
float Camera::getHeight() const{return m_View->getSize().y;}
float Camera::getCentreX() const{return m_View->getCenter().x;}
float Camera::getCentreY() const{return m_View->getCenter().y;}
float Camera::getWorldPosX() const{
	return m_View->getCenter().x - (m_View->getSize().x/2);
}
float Camera::getWorldPosY() const{
	return m_View->getCenter().y - (m_View->getSize().y/2);
}