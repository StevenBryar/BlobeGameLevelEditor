#ifndef Renderer_H
#define RENDNDER_H
//get sprites from sprite manager.
//draw and display.
#include <SFML/Graphics.hpp>

class Camera;

class Renderer{
public:
	static Renderer* instance();
	void cleanupInstance();
	void render(sf::RenderWindow* window,Camera* theCamera);
private:
	static Renderer* m_Instance;
	Renderer();
	~Renderer();
};

#endif