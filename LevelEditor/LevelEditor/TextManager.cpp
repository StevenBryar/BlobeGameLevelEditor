#include "TextManager.h"
#include "Text.h"
#include "common.h"
#include "Vector3.h"
#include "MessageHandler.h"

TextManager* TextManager::m_Instance = NULL;

TextManager* TextManager::instance(){
	if(!m_Instance){
		m_Instance = new TextManager();
	}
	return m_Instance;
}
TextManager::TextManager(){
	m_Fonts = new std::map<std::string,sf::Font*>();
	m_Texts = new std::vector<Text*>();
}
TextManager::~TextManager(){
	if(m_Texts){
		SafeVectorDelete<Text>(*m_Texts);
		SafePtrRelease(m_Texts);
	}
	if(m_Fonts){
		SafeMapDelete<std::string,sf::Font>(*m_Fonts);
		SafePtrRelease(m_Fonts);
	}
}

void TextManager::cleanupInstance(){
	if(m_Instance){
		delete m_Instance;
	}
	m_Instance = NULL;
}
Text* TextManager::createText(const std::string& text,const std::string& fontName,const int& fontSize,
				 const Vector3& color,const int& alpha,const int& x,const int& y,
				 const unsigned int& atts,const bool& deleteAfterTime,const float& timeTillDelete){
	Text* t = NULL;
	if(m_Fonts->find(fontName) != m_Fonts->end()){
		t = new Text(m_Fonts->at(fontName),text,fontSize,color,atts,alpha,x,y);
		if(deleteAfterTime){
			MessageHandler::Instance()->createMessage(10,this,this,t,timeTillDelete);
		}
		m_Texts->push_back(t);
	}
	return t;
}

void TextManager::deleteText(Text* text){
	for(int i = 0;i < m_Texts->size();i++){
		if((*m_Texts)[i] == text){
			SafePtrRelease(text);
			m_Texts->erase(m_Texts->begin()+i);
			return;
		}
	}
}
void TextManager::loadFont(const std::string& file){
	if(m_Fonts->find(file) == m_Fonts->end()){
		sf::Font* font = new sf::Font();
		if(font->loadFromFile(file)){
		m_Fonts->insert(std::pair<const std::string,sf::Font*>
							(file,font));
		}
	}
}
std::vector<Text*>* TextManager::getTexts() const{return m_Texts;}
void TextManager::update(){
	for(int i = 0;i < m_Texts->size();i++){
		(*m_Texts)[i]->update();
	}
}

void TextManager::handleMessage(const Message& msg){
	switch(msg.type){
	case 10:

		break;
	}
}