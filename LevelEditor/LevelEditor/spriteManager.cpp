#include "SpriteManager.h"
#include "2dSprite.h"
#include "common.h"

SpriteManager* SpriteManager::m_Instance = NULL;

SpriteManager* SpriteManager::instance(){
	if(m_Instance == NULL){
		m_Instance = new SpriteManager();
	}
	return m_Instance;
 }
void SpriteManager::cleanupInstance(){
	if(m_Instance != NULL){
		delete m_Instance;
		m_Instance = NULL;
	}
}

SpriteManager::SpriteManager(){
	m_Textures = new std::map<std::string,sf::Texture*>();
	m_Sprites = new std::multimap<unsigned int,Sprite2d*>();
}
SpriteManager::~SpriteManager(){
	if(m_Sprites != NULL){
	SafeMapDelete<unsigned int,Sprite2d>
		((*m_Sprites));
		delete m_Sprites;
		m_Sprites = NULL;
	}
	if(m_Textures != NULL){
		SafeMapDelete<std::string,sf::Texture>
			((*m_Textures));
		delete m_Textures;
		m_Textures = NULL;
	}
}

void SpriteManager::update(){
	std::multimap<unsigned int,Sprite2d*>::iterator iterator;
	for(iterator = m_Sprites->begin();
		iterator != m_Sprites->end();iterator++){
			iterator->second->update();
	}
}
Sprite2d* SpriteManager::createSprite(GameObject* entity,const std::string& textureName,const unsigned int& drawOrder){
	Sprite2d* sprite = NULL;
	if(m_Textures->find(textureName) != m_Textures->end()){
		sprite = new Sprite2d(entity,m_Textures->at(textureName));
		m_Sprites->insert(std::pair<unsigned int,Sprite2d*>
			(drawOrder,sprite));
	}
	return sprite;
}
void SpriteManager::deleteSprite(GameObject* owner){
	std::multimap<unsigned int,Sprite2d*>::iterator iterator;
	for(iterator = m_Sprites->begin();
		iterator != m_Sprites->end();iterator++){
		if(iterator->second->m_Owner == owner){
			SafePtrRelease(iterator->second);
			m_Sprites->erase(iterator);
			break;
		}
	}
}
void SpriteManager::deleteSprite(Sprite2d* sprite){
	std::multimap<unsigned int,Sprite2d*>::iterator iterator;
	for(iterator = m_Sprites->begin();
		iterator != m_Sprites->end();iterator++){
		if(iterator->second == sprite){
			SafePtrRelease(iterator->second);
			m_Sprites->erase(iterator);
			sprite = NULL;
			break;
		}
	}
}
void SpriteManager::loadTexture(const std::string& file){
	if(m_Textures->find(file) == m_Textures->end()){
		sf::Texture* texture = new sf::Texture();
		if(texture->loadFromFile(file)){
		m_Textures->insert(std::pair<const std::string,sf::Texture*>
							(file,texture));
		}
	}
}

Sprite2d* SpriteManager::getSprite(GameObject* owner){
	std::multimap<unsigned int,Sprite2d*>::iterator iterator;
	for(iterator = m_Sprites->begin();
		iterator != m_Sprites->end();iterator++){
		if(iterator->second->m_Owner == owner){
			return iterator->second;
		}
	}
	return NULL;
}
Sprite2d* SpriteManager::getSprite(const std::string& name){
	std::multimap<unsigned int,Sprite2d*>::iterator iterator;
	for(iterator = m_Sprites->begin();
		iterator != m_Sprites->end();iterator++){
			if(iterator->second->getName() == name){
			return iterator->second;
		}
	}
	return NULL;
}

std::vector<Sprite2d*>* SpriteManager::getSprites(){
	std::vector<Sprite2d*>* sprites = 
		new std::vector<Sprite2d*>();
	if(!m_Sprites->empty()){
		std::multimap<unsigned int,Sprite2d*>::reverse_iterator iterator;
		for(iterator = m_Sprites->rbegin();
			iterator != m_Sprites->rend();iterator++){
				sprites->push_back(iterator->second);
		}
	}
	return sprites;
}