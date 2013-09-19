#include "Util.h"
#include "common.h"
#include "camera.h"

Util* Util::m_Instance = NULL;
Util* Util::instance(){
	if(m_Instance == NULL){
		m_Instance = new Util();
	}
	return m_Instance;
}
void Util::cleanUpInstance(){
	SafePtrRelease(m_Instance);
}

Util::Util() :
m_Delta(0.0f){
	sf::Clock clock;
	m_TimeSinceUpdate = clock.getElapsedTime().asSeconds();
}
Util::~Util(){}

void Util::update(){
	m_Delta = m_Clock.getElapsedTime().asSeconds() - m_TimeSinceUpdate;
	m_TimeSinceUpdate = m_Clock.getElapsedTime().asSeconds();
}
double Util::getDelta() const{
	return m_Delta;
}
int Util::getElapsedTime() const{
	return m_Clock.getElapsedTime().asMilliseconds();
}

bool Util::isKeyDown(const keyType& key) const{
	if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)){
		return true;
	}
	return false;
}
bool Util::isKeyUp(const keyType& key) const{
	return !isKeyDown(key);
}

float Util::screenToWorldCoordX(const int& pointScreenPosX,Camera* camera){
	return camera->getWorldPosX() + pointScreenPosX;
}
float Util::screenToWorldCoordY(const int& pointScreenPosY,Camera* camera){
	return camera->getWorldPosY() + pointScreenPosY;
}
float Util::worldToScreenCoordX(const int& pointWorldPosX,Camera* camera){
	return pointWorldPosX - camera->getWorldPosX();
}
float Util::worldToScreenCoordY(const int& pointWorldPosY,Camera* camera){
	return pointWorldPosY - camera->getWorldPosY();
}

bool Util::rectIntersection(const float& x1,const float& y1,const float& w1,const float& h1,
							const float& x2,const float& y2,const float& w2,const float& h2){
	return   (x1 < (x2+w2) &&
			 (x1+w1) > x2  &&
			  y1 < (y2+h2) &&
			 (y1+h1) > y2);
}

int Util::getCursorX() const{
	return sf::Mouse::getPosition().x;
}
int Util::getCursorY() const{
	return sf::Mouse::getPosition().y;
}