#include "uiElement.h"
#include "camera.h"

UiElement::UiElement(const int& posX,const int& posY,Camera* camera) :
GameObject(),
m_ScreenPosX(posX),
m_ScreenPosY(posY),
m_Camera(camera){
	m_PositionX = m_ScreenPosX;
	m_PositionY = m_ScreenPosY;
}
UiElement::~UiElement(){

}

void UiElement::update(){
	if(m_Camera){
		setPositionX(m_Camera->getWorldPosX()+m_ScreenPosX);
		setPositionY(m_Camera->getWorldPosY()+m_ScreenPosY);
	}
}

void UiElement::setCamera(Camera* camera){m_Camera = camera;}
void UiElement::setScreenPos(const int& screenPosX,const int& screenPosY){
	m_ScreenPosX = screenPosX;
	m_ScreenPosY = screenPosY;
}

Camera* UiElement::getCamera() const{return m_Camera;}
int UiElement::getScreenPosX() const{return m_ScreenPosX;}
int UiElement::getScreenPosY() const{return m_ScreenPosY;}