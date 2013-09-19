#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H
#include "MessageListener.h"
#include <vector>
#include "SFML\Graphics\Text.hpp"


class Text;
class Vector3;
enum textAttribute;
class TextManager : public MessageListener{
public:
	static TextManager* instance();
	void cleanupInstance();
	Text* createText(const std::string& text,const std::string& fontName,const int& fontSize,
						const Vector3& color,const int& alpha,const int& x,const int& y,const unsigned int& atts,
							const bool& deleteAfterTime,const float& timeTillDelete);
	void deleteText(Text* text);
	void loadFont(const std::string& file);
	std::vector<Text*>* getTexts() const;
	void update();

protected:
	TextManager();
	~TextManager();
	static TextManager* m_Instance;

	std::vector<Text*>* m_Texts;
	std::map<std::string,sf::Font*>* m_Fonts;
	void handleMessage(const Message& msg);
};
#endif