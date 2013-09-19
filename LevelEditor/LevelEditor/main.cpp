#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "LevelEditorMenu.h"
#include "InputManager.h"
#include "constants.h"
#include "InputListener.h"
#include "Renderer.h"
#include "Camera.h"
#include "SpriteManager.h"
#include "GameObject.h"
#include "2dSprite.h"
#include "Util.h"
#include "uiTextBox.h"
#include "MessageHandler.h"

void updateMouse(sf::Window* window);

int main(){
	sf::RenderWindow* window = new sf::RenderWindow
		(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),WINDOW_NAME);
	window->setFramerateLimit(60);
	sf::Clock theClock;
	double lastUpdateTime = theClock.getElapsedTime().asSeconds();
	double delta = 0.0f;
	bool focus = true;
	LevelEditorMenu::instance()->getCamera()->setView
		(new sf::View(sf::FloatRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT)));
	//Game loop
	while(window->isOpen()){
		Util::instance()->update();
		delta = theClock.getElapsedTime().asSeconds() - lastUpdateTime;
		lastUpdateTime = theClock.getElapsedTime().asSeconds();
		sf::Event event;
		InputManager::instance()->update();
		while(window->pollEvent(event)){
			switch(event.type){
			case sf::Event::Closed:
				SpriteManager::instance()->cleanupInstance();
				InputManager::instance()->cleanUpInstance();
				LevelEditorMenu::instance()->cleanupInstance();
				Renderer::instance()->cleanupInstance();
				Util::instance()->cleanUpInstance();
				window->close();
				return 0;
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
				focus = !focus;
				break;
			case sf::Event::MouseMoved:
				if(focus){
					InputManager::instance()->handleMouseInput
						(MOUSE_MOVED,sf::Mouse::getPosition(*window).x,
						sf::Mouse::getPosition(*window).y);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if(focus){
					if(event.mouseButton.button == sf::Mouse::Left){
						InputManager::instance()->handleMouseInput
						(MOUSE_LB_RELEASED,sf::Mouse::getPosition(*window).x,
						sf::Mouse::getPosition(*window).y);
					}
					else if(event.mouseButton.button == sf::Mouse::Right){
						InputManager::instance()->handleMouseInput
						(MOUSE_RB_RELEASED,sf::Mouse::getPosition(*window).x,
						sf::Mouse::getPosition(*window).y);
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if(focus){
					if(event.mouseButton.button == sf::Mouse::Left){
						InputManager::instance()->handleMouseInput
							(MOUSE_LB_PRESSED,sf::Mouse::getPosition(*window).x,
							sf::Mouse::getPosition(*window).y);
					}
					else if(event.mouseButton.button == sf::Mouse::Right){
						InputManager::instance()->handleMouseInput
							(MOUSE_RB_PRESSED,sf::Mouse::getPosition(*window).x,
							sf::Mouse::getPosition(*window).y);
					}
				}
				break;
			case sf::Event::TextEntered:
				if(focus && event.text.unicode < 128 &&
					event.text.unicode > 31 || event.text.unicode == 8){
					std::vector<UiTextBox*>* textBoxes = UiTextBox::getTextBoxes();
					for(int i = 0;i < textBoxes->size();i++){
						if((*textBoxes)[i]->getFocus()){
							MessageHandler::Instance()->
							createMessage(TEXT_ENTERED,NULL,
							(*textBoxes)[i],(void*)event.text.unicode,0);
						}
					}
				}
				break;
			case sf::Event::KeyReleased:
				if(focus){
					if(event.key.code != sf::Keyboard::Escape){
						InputManager::instance()->handleKeyInput(KEY_RELEASED,(keyType)event.key.code);
					}
					else{
						SpriteManager::instance()->cleanupInstance();
						InputManager::instance()->cleanUpInstance();
						LevelEditorMenu::instance()->cleanupInstance();
						Renderer::instance()->cleanupInstance();
						Util::instance()->cleanUpInstance();
						window->close();
						return 0;
					}
				}
			}
		}
		LevelEditorMenu::instance()->update();
		SpriteManager::instance()->update();
		Renderer::instance()->render(window,LevelEditorMenu::instance()->getCamera());
		if(focus){
		updateMouse(window);
		}
	}
	return 0;
}

void updateMouse(sf::Window* window){
		if(sf::Mouse::getPosition(*window).x < 0){
			sf::Mouse::setPosition(sf::Vector2i(0,sf::Mouse::getPosition(*window).y),(*window));
		}
		else if(sf::Mouse::getPosition(*window).x > LevelEditorMenu::instance()->getCamera()->getWidth()){
			sf::Mouse::setPosition(sf::Vector2i(LevelEditorMenu::instance()->getCamera()->getWidth()-2,
				sf::Mouse::getPosition(*window).y),(*window));
		}
		if(sf::Mouse::getPosition(*window).y < 0){
			sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(*window).x,0),(*window));
		}
		else if(sf::Mouse::getPosition(*window).y > LevelEditorMenu::instance()->getCamera()->getHeight()){
			sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(*window).x,
				LevelEditorMenu::instance()->getCamera()->getHeight()-2),(*window));
		}
}
