#ifndef InputManager_H
#define InputManager_H

#include <map>
#include <vector>

class InputListener;
enum keyType;
enum inputEvent;

struct InputType{
public:
	inputEvent event;
	keyType key;

	InputType(const inputEvent& aEvent,const keyType& aKey){
		event = aEvent;key = aKey;
	}

	bool operator==(const InputType& type) const{
		if(this->event == type.event &&
			this->key == type.key)
				return true;

		return false;
	}
	bool operator!=(const InputType& type) const{
		return !(*this == type);
	}
};

class InputManager{
public:
	static InputManager* instance();
	static void cleanUpInstance();

	void registerKeyinput(InputListener* listener,
							const keyType& key,const inputEvent& event);
	void registerMouseInput(InputListener* listener,
								const inputEvent& event);

	void handleKeyInput(const inputEvent& event,const keyType& key) const;
	void handleMouseInput(const inputEvent& event,const int& x,const int& y) const;

	void pauseInput(InputListener* listener,const InputType& type);
	void pauseAllOf(InputListener* listener);
	void pauseAll();

	void resumeInput(InputListener* listener,const InputType& type);
	void resumeAllOf(InputListener* listener);
	void resumeAll();

	void removeInput(InputListener* listener,const InputType& type);
	void removeAllOf(InputListener* listener);

	void update();

private:
	InputManager();
	~InputManager();

	static InputManager* m_Instance;

	std::multimap<InputListener*, InputType>* m_InputRegistry;
	std::multimap<InputListener*, InputType>* m_InputsPaused;
	std::multimap<InputListener*, InputType>* m_InputsToAdd;
	std::multimap<InputListener*, InputType>* m_InputsToRemove;
};
#endif