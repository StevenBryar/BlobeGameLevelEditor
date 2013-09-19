#ifndef UTIL_H
#define UTIL_H

//class will contain:keyboard,mouse,deltaTime,totalTime,
//maybe some other stuff i don't know right now.
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "constants.h"
#include <string>

class Camera;

class Util{
public:
	static Util* instance();
	static void cleanUpInstance();
	void update();
	double getDelta() const;
	int getElapsedTime() const;
	bool isKeyDown(const keyType& key) const;
	bool isKeyUp(const keyType& key) const;
	float screenToWorldCoordX(const int& pointScreenPosX,Camera* camera);
	float screenToWorldCoordY(const int& pointScreenPosY,Camera* camera);
	float worldToScreenCoordX(const int& pointWorldPosX,Camera* camera);
	float worldToScreenCoordY(const int& pointWorldPosY,Camera* camera);
	bool rectIntersection(const float& x1,const float& y1,const float& w1,const float& h1,
							const float& x2,const float& y2,const float& w2,const float& h2);
	int getCursorX() const;
	int getCursorY() const;
private:
	Util();
	~Util();
	static Util* m_Instance;
protected:
	double m_Delta;
	double m_TimeSinceUpdate;
	sf::Clock m_Clock;
};
#endif