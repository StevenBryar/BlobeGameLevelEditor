#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H	

enum keyType;
enum inputEvent;

class InputListener{
public:
	virtual void keyInputCallback(const keyType& key,const inputEvent& event);
	virtual void mouseInputCalback(const inputEvent& event,const int& x,const int& y);

	virtual ~InputListener();
};

#endif