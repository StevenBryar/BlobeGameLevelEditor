#ifndef UI_TEXT_BOX
#define UI_TEXT_BOX
#include "uiElement.h"
#include "MessageListener.h"
#include "inputListener.h"
#include <string>
#include <vector>

class Text;
class Vector3;

class UiTextBox : public UiElement , public MessageListener , public InputListener{
public:
	UiTextBox(Text* text,Camera* camera,const int& x = 0,const int& y = 0,const int& width = 128,const int& height = 30);
	UiTextBox(const std::string& font,const int& fontSize,const std::string& text,const Vector3& color,Camera* camera,
				const int& x = 0,const int& y = 0,const int& width = 128,const int& height = 30);
	~UiTextBox();
	bool getFocus();
	void setFocus(const bool& focus);
	std::string getString();
	void setString(const std::string& aString);
	Text* getText();
	void setText(Text* text);
	void appendString(const std::string& aString);
	void update();

	static std::vector<UiTextBox*>* getTextBoxes();

	void mouseInputCalback(const inputEvent& event,const int& x,const int& y);
protected:
	Text* m_Text;
	bool m_HasFocus;
	void handleMessage(const Message& msg);
	static std::vector<UiTextBox*>* m_TextBoxes;
};
#endif