#ifndef Camera_H
#define Camera_H
#include <SFML/Graphics.hpp>

class GameObject;

//wrap around SFML view class.
class Camera{
public:
	Camera();
	Camera(sf::View* view);
	~Camera();
	void rotate(const float& rotation);
	void moveTo(const float& x,const float& y);
	void centre(const float& x,const float& y);
	void zoom(const float& z);
	void move(const float& x,const float& y);
	void setSize(const float& x,const float& y);
	void setView(sf::View* view);
	void setFollow(GameObject* thing);

	float getRotation() const;
	GameObject* getFollow() const;
	sf::View* getView() const;
	float getWidth() const;
	float getHeight() const;
	float getCentreX() const;
	float getCentreY() const;
	float getWorldPosX() const;
	float getWorldPosY() const;

private:
	sf::View* m_View;
	GameObject* m_Follow;
};
#endif