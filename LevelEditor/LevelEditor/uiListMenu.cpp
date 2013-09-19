#include "uiListMenu.h"
#include "uiButton.h"
#include "Text.h"
#include "inputManager.h"
#include "constants.h"
#include "common.h"
#include "camera.h"
#include "TextManager.h"

UiListMenu::UiListMenu(const int& screenPosX,const int& screenPosY,Camera* camera,
						UiButton* scrollUp,UiButton* scrollDown,std::string font,
						const int& textOffsetX,const int& maxVisibleEntries,int entryHeight) :
m_Up(scrollUp),
m_Down(scrollDown),
m_TextOffsetX(textOffsetX),
m_MaxEntriesVisible(maxVisibleEntries),
m_EntryHeight(entryHeight),
m_Font(font),
UiElement(screenPosX,screenPosY,camera){
	m_Entries = new std::map<int,Text*>();
	InputManager::instance()->registerMouseInput(this,MOUSE_LB_RELEASED);
	if(m_Up){
		m_Up->setCallBackParam(this);
	}
	if(m_Down){
		m_Down->setCallBackParam(this);
	}
	m_StartOfVisibles = 1;
	m_Selected = 1;
	m_DefaultColor = Vector3(200,50,80);
	m_SelectedColor = Vector3(100,130,40);
}

UiListMenu::~UiListMenu(){
	SafePtrRelease(m_Up);
	SafePtrRelease(m_Down);
	if(m_Entries){
		clearEntries();
	}
	SafePtrRelease(m_Entries);
}
void UiListMenu::addEntry(std::string entry){
	Text* text = TextManager::instance()->createText(entry,m_Font,m_EntryHeight,m_DefaultColor,255,0,0,0,false,0);
	m_Entries->insert(std::pair<int,Text*>(m_Entries->size()+1,text));
	updateMenu();
}
bool UiListMenu::deleteEntry(std::string entry){
	std::map<int,Text*>::iterator i;
	for(i = m_Entries->begin();i != m_Entries->end();i++){
		if(i->second->getText() == entry){
			TextManager::instance()->deleteText(i->second);
			m_Entries->erase(i);
			return true;
		}
	}
	return false;
}
void UiListMenu::clearEntries(){
	std::map<int,Text*>::iterator i;
	for(i = m_Entries->begin();i != m_Entries->end();i++){
		TextManager::instance()->deleteText(i->second);
	}
	m_Entries->clear();
}

void UiListMenu::scrollUp(){
	if(m_StartOfVisibles > 1){
		m_StartOfVisibles--;
	}
	updateMenu();
}
void UiListMenu::scrollDown(){
	if((m_Entries->size()-m_MaxEntriesVisible) >= m_StartOfVisibles){
		m_StartOfVisibles++;
	}
	updateMenu();
}
void UiListMenu::setDefaultTextColor(const Vector3& color){m_DefaultColor = color;}
void UiListMenu::setSelectedTextColor(const Vector3& color){m_SelectedColor = color;}
void UiListMenu::setOffsetX(const int& x){m_TextOffsetX = x; updateMenu();}
void UiListMenu::setUpButton(UiButton* up){m_Up = up;}
void UiListMenu::setDownButton(UiButton* down){m_Down = down;}
void UiListMenu::setMaxVisibleEntries(const int& max){m_MaxEntriesVisible = max; updateMenu();}
void UiListMenu::setFont(const std::string& font){m_Font = font;}
void UiListMenu::setSelectedEntry(const int& selected){
	if(selected > 0 && selected <= m_Entries->size()){
		m_Selected = selected;updateMenu();
	}
}

UiButton* UiListMenu::getUpButton() const{return m_Up;}
UiButton* UiListMenu::getDownButton() const{return m_Down;}	
int UiListMenu::getTextOffsetX() const{return m_TextOffsetX;}
int UiListMenu::getMaxVisibleEntries() const{return m_MaxEntriesVisible;}
std::map<int,Text*>* UiListMenu::getEntries() const{return m_Entries;}
std::string UiListMenu::getSelectedEntry() const{return m_Entries->at(m_Selected)->getText();}
int UiListMenu::getSelecedEntryNumber() const{return m_Selected;}
std::string UiListMenu::getEntry(const int& p) const{return m_Entries->at(p)->getText();}
Vector3 UiListMenu::getDefaultTextColor() const{return m_DefaultColor;}
Vector3 UiListMenu::getSelectedTextColor() const{return m_SelectedColor;}
std::string UiListMenu::getFont() const{return m_Font;}

void UiListMenu::update(){
	if(m_Camera){
		setPositionX(m_Camera->getWorldPosX()+m_ScreenPosX);
		setPositionY(m_Camera->getWorldPosY()+m_ScreenPosY);
	}
	if(m_Up){
		m_Up->update();
	}
	if(m_Down){
		m_Down->update();
	}
	Text* text = NULL;
	for(int i = m_StartOfVisibles;
		i < (m_StartOfVisibles+m_MaxEntriesVisible) && (i-1) < m_Entries->size();
		i++){
		text = m_Entries->at(i);
		text->setPosition(
			getPositionX()+m_TextOffsetX,
			getPositionY()+(m_EntryHeight*(i-m_StartOfVisibles)));
	}
}
void UiListMenu::updateMenu(){
	std::map<int,Text*>::iterator iterator;
	for(iterator = m_Entries->begin();iterator != m_Entries->end();iterator++){
		iterator->second->setVisible(false);
		iterator->second->setColor(m_DefaultColor,iterator->second->getAlpha());
	}
	Text* text = NULL;
	for(int i = m_StartOfVisibles;
		i < (m_StartOfVisibles+m_MaxEntriesVisible) && (i-1) < m_Entries->size();
		i++){
		text = m_Entries->at(i);
		text->setVisible(true);
		text->setPosition(
			getScreenPosX()+m_TextOffsetX,
			getScreenPosY()+(m_EntryHeight*(i-m_StartOfVisibles)));
		if(text->getText() == getSelectedEntry()){
			text->setColor(m_SelectedColor,text->getAlpha());
		}
	}
}

void UiListMenu::mouseInputCalback(const inputEvent& event,const int& x,const int& y){
switch(event){
	case MOUSE_LB_RELEASED:
		if(x > getScreenPosX() && x < (getScreenPosX()+getWidth()) &&
		   y > getScreenPosY() && y < (getScreenPosY()+getHeight())){
			Text* text = NULL;
		   	for(int i = m_StartOfVisibles;
			i < (m_StartOfVisibles+m_MaxEntriesVisible) && (i-1) < m_Entries->size();
			i++){
				text = m_Entries->at(i);
				if(y > getScreenPosY()+(m_EntryHeight*(i-m_StartOfVisibles)) && 
				   y < getScreenPosY()+(m_EntryHeight*((i+1)-m_StartOfVisibles))){
					setSelectedEntry(i);
					return;
				}
			}
		}
	}
}