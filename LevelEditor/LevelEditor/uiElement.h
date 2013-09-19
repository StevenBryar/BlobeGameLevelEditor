#ifndef UI_ELEMENT
#define UI_ELEMENT
#include "gameObject.h"
#include <vector>

class Camera;

class UiElement : public GameObject{
public:
	UiElement(const int& posX,const int& posY,Camera* camera);
	virtual ~UiElement();

	void setCamera(Camera* camera);
	void setScreenPos(const int& screenPosX,const int& screenPosY);
	virtual void update();

	Camera* getCamera() const;
	int getScreenPosX() const;
	int getScreenPosY() const;
protected:
	int m_ScreenPosX;
	int m_ScreenPosY;
	Camera* m_Camera;
};
#endif