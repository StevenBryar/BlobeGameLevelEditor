#include "Text.h"
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Font.hpp"
#include "Vector3.h"
#include "common.h"

Text::Text(sf::Font* font,const std::string& text,const int& size,const Vector3& color,const unsigned int& atts,const int& alpha,const float& x,const float& y){
	m_String = new sf::Text();
	m_String->setFont(*font);
	m_String->setCharacterSize(size);
	m_String->setString(text);
	m_String->setPosition(x,y);
	sf::Color tColor(color.X,color.Y,color.Z,alpha);
	m_String->setColor(tColor);
	m_TextAtt = atts;
	m_Visible = true;
}
Text::~Text(){
	SafePtrRelease(m_String);
}

void Text::update(){
	if(ContainsFlags(m_TextAtt,FADING) &&
	   getAlpha() != 0){
		setColor(getColor(),getAlpha()-2);
	}
	if(ContainsFlags(m_TextAtt,RISING)){
		setPosition(getPosX(),getPosY()-0.5);
	}
	if(ContainsFlags(m_TextAtt,FALLING)){
		setPosition(getPosX(),getPosY()+0.5);
	}
	if(ContainsFlags(m_TextAtt,SHRINKING) &&
		getSize() > 0){
		setSize(getSize()-1);
	}
	if(ContainsFlags(m_TextAtt,GROWING)){
		setSize(getSize()+1);
	}
	if(ContainsFlags(m_TextAtt,TO_THE_LEFT)){
		setPosition(getPosX()-0.5,getPosY());
	}
	if(ContainsFlags(m_TextAtt,TO_THE_RIGHT)){
		setPosition(getPosX()+0.5,getPosY());
	}
}
void Text::setVisible(const bool& v){m_Visible = v;}
void Text::setText(const std::string& s){
	m_String->setString(s);
}
void Text::setPosition(const float& x,const float& y){
	m_String->setPosition(x,y);
}
void Text::setSize(const int& size){
	m_String->setCharacterSize(size);
}
void Text::setColor(const Vector3& rgb,const int& alpha){
	sf::Color tColor(rgb.X,rgb.Y,rgb.Z,alpha);
	m_String->setColor(tColor);
}
void Text::addAttribute(const textAttribute& att){
	if(!ContainsFlags(m_TextAtt,att)){
		m_TextAtt |= att;
	}
}
void Text::setAttributes(const unsigned int& att){
	m_TextAtt = att;
}
std::string Text::getText() const{return m_String->getString();}
float Text::getPosX() const{return m_String->getPosition().x;}
float Text::getPosY() const{return m_String->getPosition().y;}
int Text::getSize() const{return m_String->getCharacterSize();}
Vector3 Text::getColor() const{
	Vector3 color(m_String->getColor().r,
				  m_String->getColor().g,
				  m_String->getColor().b);
	return color;
}	
int Text::getAlpha() const{return m_String->getColor().a;}
unsigned int Text::getAttributes() const{return m_TextAtt;}
bool Text::getVisible() const{return m_Visible;}