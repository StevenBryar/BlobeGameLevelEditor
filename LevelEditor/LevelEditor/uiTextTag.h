#ifndef UI_TEXT_TAG
#define UI_TEXT_TAG
#include "uiElement.h"

class Text;

class UiTextTag : public UiElement{
public:
	UiTextTag(const int& x,const int& y,Camera* camera,Text* text);
	virtual ~UiTextTag();

	void update();

protected:
	Text* m_Text;
};
#endif