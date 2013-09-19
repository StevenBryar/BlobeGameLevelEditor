#ifndef UIBUTTON_H
#define UIBUTTON_H
#include "inputListener.h"
#include "uiElement.h"
#include <string>

enum ButtonAtt{
	FIRE_ON_PRESSED = (1 << 0),
	FIRE_ON_RELEASED = (1 << 1),
	HIGHLIGHT_ON_HOVER = (1 << 2),
};

class Sprite2d;
class Camera;
class UiButton : public UiElement,public InputListener{
public:
	UiButton(const int& offsetX,const int& offsetY,const int& width,const int& height,const std::string& defaultSprite,
				const unsigned int& buttonAtt,Camera* camera,void(*func)(void* extra),void* cbParam);
	UiButton(const int& offsetX,const int& offsetY,const int& width,const int& height,const std::string& defaultSprite,
				const std::string& downSprite,const unsigned int& buttonAtt,Camera* camera,void(*func)(void* extra),void* cbParam);
	UiButton(const int& offsetX,const int& offsetY,const int& width,const int& height,const std::string& defaultSprite,const std::string& downSprite,
				const std::string& highlightSprite,const unsigned int& buttonAtt,Camera* camera,void(*func)(void* extra),void* cbParam);
	virtual ~UiButton();

	void(*callBack)(void* extra);

	void addAttribute(const ButtonAtt& att);
	void setAttributes(const unsigned int& atts);
	void setCallBackParam(void* param);

	unsigned int getAttributes() const;
	void* getCallBackParam() const;

	void mouseInputCalback(const inputEvent& event,const int& x,const int& y);
protected:
	std::string m_DefaultSprite;
	std::string m_DownSprite;
	std::string m_HighlightSprite;
	unsigned int m_ButtonAtt;
	bool m_Hover;
	void* m_CallBackParam;
};
#endif