#include "InputManager.h"
#include "InputListener.h"
#include "constants.h"
#include <stdlib.h>

InputManager* InputManager::m_Instance = NULL;
InputManager* InputManager::instance(){
	if(m_Instance == NULL){
		m_Instance = new InputManager();
	}
	return m_Instance;
}
void InputManager::cleanUpInstance(){
	if(m_Instance != NULL){
		delete m_Instance;
		m_Instance = NULL;
	}
}

InputManager::InputManager(){
	m_InputRegistry = new 
		std::multimap<InputListener*, InputType>();
	m_InputsToRemove = new 
		std::multimap<InputListener*, InputType>();
	m_InputsToAdd = new 
		std::multimap<InputListener*, InputType>();
	m_InputsPaused = new 
		std::multimap<InputListener*, InputType>();
}

InputManager::~InputManager(){
	if(m_InputRegistry != NULL){
		m_InputRegistry->clear();
		delete m_InputRegistry;
	}
	if(m_InputsToAdd != NULL){
		m_InputsToAdd->clear();
		delete m_InputsToAdd;
	}
	if(m_InputsToRemove != NULL){
		m_InputsToRemove->clear();
		delete m_InputsToRemove;
	}
	if(m_InputsPaused != NULL){
		m_InputsPaused->clear();
		delete m_InputsPaused;
	}
}

void InputManager::registerKeyinput(InputListener* listener,
							const keyType& key,const inputEvent& event){
	m_InputsToAdd->insert(std::pair<InputListener*,InputType>
		(listener,InputType(event,key)));
}
void InputManager::registerMouseInput(InputListener* listener,
										const inputEvent& event){
	m_InputsToAdd->insert(std::pair<InputListener*,InputType>
		(listener,InputType(event,none)));
}

void InputManager::handleKeyInput(const inputEvent& event,const keyType& key) const{
		std::multimap<InputListener*, 
		InputType>::iterator iterator;

		for(iterator = m_InputRegistry->begin();
		iterator != m_InputRegistry->end();iterator++)
			if(iterator->second.event == event &&
				iterator->second.key == key)
					iterator->first->keyInputCallback(key,event);
}
void InputManager::handleMouseInput(const inputEvent& event,const int& x,const int& y) const{
	std::multimap<InputListener*, 
		InputType>::iterator iterator;

		for(iterator = m_InputRegistry->begin();
		iterator != m_InputRegistry->end();iterator++)
			if(iterator->second.event == event)
				iterator->first->mouseInputCalback(event,x,y);
}

void InputManager::pauseInput(InputListener* listener,
								const InputType& type){
	m_InputsToRemove->insert(std::pair<InputListener*,InputType>
		(listener,type));

	m_InputsPaused->insert(std::pair<InputListener*,InputType>
		(listener,type));
}
void InputManager::pauseAllOf(InputListener* listener){
	std::multimap<InputListener*, 
		InputType>::iterator iterator;

	for(iterator = m_InputRegistry->begin();
		iterator != m_InputRegistry->end();iterator++)
			if((*iterator).first == listener)
				pauseInput(iterator->first,iterator->second);
}
void InputManager::pauseAll(){
		std::multimap<InputListener*, 
		InputType>::iterator iterator;

	for(iterator = m_InputRegistry->begin();
		iterator != m_InputRegistry->end();iterator++)
				pauseInput(iterator->first,iterator->second);
}

void InputManager::resumeInput(InputListener* listener,const InputType& type){
		std::multimap<InputListener*, 
		InputType>::iterator iterator;
	for(iterator = m_InputsPaused->begin();
		iterator != m_InputsPaused->end();iterator++)
				if(iterator->first == listener &&
					iterator->second == type){
						m_InputsPaused->erase(iterator);
						break;
				}

	m_InputsToAdd->insert(std::pair<InputListener*,InputType>
		(listener,type));
}
void InputManager::resumeAllOf(InputListener* listener){
	std::multimap<InputListener*, InputType> tempPaused = 
		(*m_InputsPaused);

		std::multimap<InputListener*, 
		InputType>::iterator iterator;
	for(iterator = tempPaused.begin();
		iterator != tempPaused.end();iterator++)
				if(iterator->first == listener)
					resumeInput(listener,iterator->second);
}
void InputManager::resumeAll(){
		std::multimap<InputListener*, InputType> tempPaused = 
		(*m_InputsPaused);

		std::multimap<InputListener*, 
		InputType>::iterator iterator;
	for(iterator = tempPaused.begin();
		iterator != tempPaused.end();iterator++)
		resumeInput(iterator->first,iterator->second);
}

void InputManager::removeInput(InputListener* listener,const InputType& type){
	m_InputsToRemove->insert(std::pair<InputListener*,InputType>
		(listener,type));
}
void InputManager::removeAllOf(InputListener* listener){
		std::multimap<InputListener*, 
		InputType>::iterator iterator;
	for(iterator = m_InputRegistry->begin();
		iterator != m_InputRegistry->end();iterator++)
				if(iterator->first == listener)
					removeInput(listener,iterator->second);
}

void InputManager::update(){
	std::multimap<InputListener*, 
		InputType>::iterator iterator;
		std::multimap<InputListener*, 
		InputType>::iterator iterator2;

	for(iterator = m_InputsToRemove->begin();
		iterator != m_InputsToRemove->end();iterator++){
		for(iterator2 = m_InputRegistry->begin();
			iterator2 != m_InputRegistry->end();iterator2++){
			if(iterator->first == iterator2->first &&
				iterator->second == iterator2->second){
				m_InputRegistry->erase(iterator2);
					break;
			}
		}
	}
	m_InputsToRemove->clear();

	for(iterator = m_InputsToAdd->begin();
		iterator != m_InputsToAdd->end();iterator++){
			m_InputRegistry->
				insert(std::pair<InputListener*,InputType>
				(iterator->first,iterator->second));
	}
	m_InputsToAdd->clear();
}

