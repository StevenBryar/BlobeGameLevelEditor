#include "InputListener.h"
#include "constants.h"
#include "inputManager.h"

InputListener::~InputListener(){
	InputManager::instance()->removeAllOf(this);
}
void InputListener::keyInputCallback(const keyType& key,const inputEvent& event){

}
void InputListener::mouseInputCalback(const inputEvent& event,const int& x,const int& y){

}