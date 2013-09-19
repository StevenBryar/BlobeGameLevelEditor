#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "constants.h"
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Sprite2d;
class GameObject;
class Renderer;

class SpriteManager{

public:
	static SpriteManager* instance();
	void cleanupInstance();
	Sprite2d* createSprite(GameObject* entity,
	const std::string& textureName,const unsigned int& drawOrder);
	void deleteSprite(GameObject* owner);
	void deleteSprite(Sprite2d* sprite);
	void loadTexture(const std::string& file);
	std::vector<Sprite2d*>* getSprites();
	Sprite2d* getSprite(GameObject* owner);
	Sprite2d* getSprite(const std::string& name);
	void update();

private:
	SpriteManager();
	~SpriteManager();
	static SpriteManager* m_Instance;

	std::map<std::string,sf::Texture*>* m_Textures;
	std::multimap<unsigned int,Sprite2d*>* m_Sprites;
};
#endif