#include "Renderer.h"
#include "Camera.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "Text.h"
#include "2dSprite.h"
#include <vector>

Renderer* Renderer::m_Instance = NULL;

Renderer* Renderer::instance(){
	if(m_Instance == NULL)
		m_Instance = new Renderer();

	return m_Instance;
}

void Renderer::cleanupInstance(){
	if(m_Instance != NULL){
		delete m_Instance;
		m_Instance = NULL;
	}
}

Renderer::Renderer(){
}

Renderer::~Renderer(){
}

void Renderer::render(sf::RenderWindow* window,Camera* theCamera){
	window->setView((*theCamera->getView()));
	window->clear();
	std::vector<Sprite2d*> sprites = 
		(*SpriteManager::instance()->getSprites());
	for(int i = 0;i < sprites.size();i++){
		if(!sprites[i]->getHidden()){
			window->draw((*sprites[i]->m_Sprite));
		}
	}
	std::vector<Text*> texts = 
		(*TextManager::instance()->getTexts());
	for(int i = 0;i < texts.size();i++){
		if(texts[i]->getVisible()){
			window->draw(*texts[i]->m_String);
		}
	}
	window->display();
}