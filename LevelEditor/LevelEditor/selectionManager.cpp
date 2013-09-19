#include "selectionManager.h"
#include "common.h"
#include "BlobGame.h"
#include "gameObject.h"
#include "constants.h"
#include "unit.h"
#include "blob.h"
#include "Util.h"
#include "inputManager.h"
#include "level.h"
#include "spriteManager.h"
#include "PathFinder.h"
#include "2dSprite.h"
#include "BlobGame.h"
#include "tile.h"
#include "BlobGameConstants.h"

SelectionManager* SelectionManager::m_Instance = NULL;
SelectionManager* SelectionManager::instance(){
	if(m_Instance == NULL){
		m_Instance = new SelectionManager();
	}
	return m_Instance;
}
void SelectionManager::cleanupInstance(){
	if(m_Instance != NULL){
		delete m_Instance;
		m_Instance = NULL;
	}
}

SelectionManager::SelectionManager(){
	m_HotKeys = new std::map<int,std::vector<Blob*>>();
	m_Selected = new std::vector<Unit*>();
	m_State = NORMAL_STATE;
	InputManager::instance()->registerMouseInput(this,MOUSE_LB_RELEASED);
	InputManager::instance()->registerMouseInput(this,MOUSE_RB_RELEASED);
	InputManager::instance()->registerMouseInput(this,MOUSE_LB_PRESSED);
	InputManager::instance()->registerMouseInput(this,MOUSE_MOVED);
	InputManager::instance()->registerKeyinput(this,W,KEY_RELEASED);
	InputManager::instance()->registerKeyinput(this,Q,KEY_RELEASED);
	InputManager::instance()->registerKeyinput(this,E,KEY_RELEASED);
	InputManager::instance()->registerKeyinput(this,S,KEY_RELEASED);
}
SelectionManager::~SelectionManager(){
	m_HotKeys->clear();
	SafePtrRelease(m_HotKeys);
	m_Selected->clear();
	SafePtrRelease(m_Selected);
	SpriteManager::instance()->deleteSprite(m_DragSprite);
}
void SelectionManager::keyInputCallback(const keyType& key,const inputEvent& event){
	float worldX = Util::instance()->screenToWorldCoordX(Util::instance()->getCursorX(),BlobGame::instance()->getCamera());
	float worldY = Util::instance()->screenToWorldCoordY(Util::instance()->getCursorY(),BlobGame::instance()->getCamera());
	switch(event){
		case KEY_RELEASED:{
			//call useAbility method for first selected ally(if any ally selected)
			//only call if the ability is not a target select ability.
			if(m_Selected->size() > 0 && 
				m_Selected->front()->getAllegiance() == "Ally" && key == S){
				for(int i = 0;i < m_Selected->size();i++){
					(*m_Selected)[i]->stop();
					if(!ContainsFlags((*m_Selected)[i]->getStatus(),Consume)){
						(*m_Selected)[i]->setTarget(NULL);
					}
				}
			}
			else if(m_Selected->size() > 0 && 
				m_Selected->front()->getAllegiance() == "Ally"){
				Blob* blob = (Blob*)m_Selected->front();
				std::map<keyType,Ability*>::iterator iterator;
				for(iterator = blob->getAbilities()->begin();
					iterator != blob->getAbilities()->end();iterator++){
						if(iterator->first == key && !iterator->second->targetAbility){
						//if yes and not "a" key send use Ability message to first current selection.
						blob->useAbility(iterator->first,worldX,worldY);
						return;
					}
				}
			}
			break;
		}
		default:
			break;
	}
}
void SelectionManager::mouseInputCalback(const inputEvent& inEvent,const int& x,const int& y){
	float worldX = Util::instance()->screenToWorldCoordX(x,BlobGame::instance()->getCamera());
	float worldY = Util::instance()->screenToWorldCoordY(y,BlobGame::instance()->getCamera());
	bool allySelect = false;
	Level* level = BlobGame::instance()->getLevel();
	std::vector<GameObject*> objects = BlobGame::instance()->getObjects();
	switch(inEvent){
		case MOUSE_LB_RELEASED:
			m_State = NORMAL_STATE;
			if(m_Selected->size() > 0 && 
				m_Selected->front()->getAllegiance() == "Ally"){
				 Blob* blob = (Blob*)m_Selected->front();
				std::map<keyType,Ability*>::iterator iterator;
				for(iterator = blob->getAbilities()->begin();
					iterator != blob->getAbilities()->end();iterator++){
					if(Util::instance()->isKeyDown(iterator->first)){
						blob->useAbility(iterator->first,worldX,worldY);
						SpriteManager::instance()->deleteSprite(m_DragSprite);
						return;
					}
				}
			}
			m_Selected->clear();
			GameObject* object;
			for(int i = 0;i < objects.size();i++){
				if(objects[i]->getType() != "GameObject"){
					Unit* unit = (Unit*)objects[i];
					if(Util::instance()->rectIntersection
						(m_DragSprite->getPositionX(),m_DragSprite->getPositionY(),
						 m_DragSprite->getWidth(),m_DragSprite->getHeight(),
						 unit->getPositionX(),unit->getPositionY(),
						 unit->getWidth(),unit->getHeight()) &&
						 unit->getAllegiance() == "Ally"){
						if(!allySelect){
							allySelect = true;
							m_Selected->clear();
						}
						m_Selected->push_back(unit);
					}
					else if(Util::instance()->rectIntersection(
						    m_DragSprite->getPositionX(),m_DragSprite->getPositionY(),
							m_DragSprite->getWidth(),m_DragSprite->getHeight(),
							unit->getPositionX(),unit->getPositionY(),
						    unit->getWidth(),unit->getHeight()) && !allySelect){
							m_Selected->push_back(unit);
					}
				}
			}
			SpriteManager::instance()->deleteSprite(m_DragSprite);
			return;
		case MOUSE_RB_RELEASED:
			if(m_Selected->size() > 0){
				GameObject* object;
				Unit* unit;
				if((object = BlobGame::instance()->
					pointWithinObject(x,y)) && m_Selected->
					front()->getAllegiance() == "Ally" &&
					object->getType() == "Enemy" && 
					!ContainsFlags(m_Selected->front()->getStatus(),Consume) &&
					!ContainsFlags((unit = (Unit*)object)->getStatus(),Consumed)){
					//attack the unit.
					m_Selected->front()->setTarget((Unit*)object);
				}
				else if(!(object = BlobGame::instance()->
					pointWithinObject(x,y)) && m_Selected->
					front()->getAllegiance() == "Ally"){
					//move the selected unit to the location
						Tile* tile;
					for(int i = 0;i < m_Selected->size();i++){
						if((tile = level->getTileForPosition(worldX,worldY))){
							(*m_Selected)[i]->setDestinationTile(tile);
							if(!ContainsFlags((*m_Selected)[i]->getStatus(),Consume)){
								(*m_Selected)[i]->setTarget(NULL);
							}
						}
					}
				}
			}
			return;
		case MOUSE_LB_PRESSED:
			if(m_State == NORMAL_STATE){
				m_State = DRAG_SELECT_STATE;
				m_PrevMousePosX = worldX;
				m_PrevMousePosY = worldY;
				//set to drag select state.
				//create a sprite for the selection box.
				m_DragSprite = SpriteManager::instance()->createSprite(NULL,"ScrollSelect.png",0);
				m_DragSprite->setPosition(m_PrevMousePosX,m_PrevMousePosY);
				m_DragSprite->setWidth(1);
				m_DragSprite->setHeight(1);
			}
			return;
		case MOUSE_MOVED:
			if(m_State == DRAG_SELECT_STATE){
				if(Util::instance()->screenToWorldCoordX
					(x,BlobGame::instance()->getCamera()) < m_PrevMousePosX){
						m_DragSprite->setPosition(worldX,m_DragSprite->getPositionY());
						m_DragSprite->setWidth(m_PrevMousePosX - worldX);
				}
				else{
					m_DragSprite->setPosition(m_PrevMousePosX,m_DragSprite->getPositionY());
					m_DragSprite->setWidth(worldX - m_PrevMousePosX);
				}
				if(Util::instance()->screenToWorldCoordY
					(y,BlobGame::instance()->getCamera()) < m_PrevMousePosY){
						m_DragSprite->setPosition(m_DragSprite->getPositionX(),worldY);
						m_DragSprite->setHeight(m_PrevMousePosY - worldY);
				}
				else{
					m_DragSprite->setPosition(m_DragSprite->getPositionX(),m_PrevMousePosY);
					m_DragSprite->setHeight(worldY - m_PrevMousePosY);
				}
			}
			return;
		default:
			return;
	}
}
void SelectionManager::update(){
	std::vector<Unit*> selectionsToRemove;
	for(int i = 0;i < m_Selected->size();i++){
		if((*m_Selected)[i]->getHealth() <= 0){
			selectionsToRemove.push_back((*m_Selected)[i]);
		}
	}
	for(int i = 0;i < selectionsToRemove.size();i++){
		for(int j = 0;j < m_Selected->size();j++){
			if(selectionsToRemove[i] == (*m_Selected)[j]){
				m_Selected->erase(m_Selected->begin()+i);
			}
		}
	}
}