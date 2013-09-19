#include "uiTextTag.h"
#include "common.h"
#include "camera.h"
#include "Text.h"
#include "TextManager.h"

UiTextTag::UiTextTag(const int& x,const int& y,Camera* camera,Text* text) :
UiElement(x,y,camera),
m_Text(text){
	m_Text->setAttributes(0);
}
UiTextTag::~UiTextTag(){
	TextManager::instance()->deleteText(m_Text);
}

void UiTextTag::update(){
	if(m_Camera){
		setPositionX(m_Camera->getWorldPosX()+m_ScreenPosX);
		setPositionY(m_Camera->getWorldPosY()+m_ScreenPosY);
		if(m_Text){
			m_Text->setPosition(m_PositionX,m_PositionY);
		}
	}
}