#include "LevelEditorMenu.h"
#include "spriteManager.h"
#include "gameObject.h"
#include "common.h"
#include "constants.h"
#include "camera.h"
#include "inputManager.h"
#include "BlobGameConstants.h"
#include "selectionManager.h"
#include "level.h"
#include "tile.h"
#include "Util.h"
#include "MessageHandler.h"
#include "2dSprite.h"
#include "MessageHandler.h"
#include "UnitFactory.h"
#include "Vector3.h"
#include "LevelEditor.h"
#include "uiButton.h"
#include "TextManager.h"
#include "Text.h"
#include "uiListMenu.h"
#include <fstream>
#include <sys\stat.h>
#include <sys\types.h>
#include "dirent.h"

LevelEditorMenu* LevelEditorMenu::m_Instance = NULL;
LevelEditorMenu::LevelEditorMenu() :
	m_CurrentState(None){
	loadContent();
	reset();
}
LevelEditorMenu::~LevelEditorMenu(){
	if(m_GameObjects != NULL){
		SafeVectorDelete((*m_GameObjects));
		SafePtrRelease(m_GameObjects);
	}
	SafePtrRelease(m_LevelSelect);
	SafePtrRelease(m_Level);
	SafePtrRelease(m_Camera);
	SafePtrRelease(m_Editor);
	SafePtrRelease(m_GameObjectsToDelete);
	MessageHandler::Instance()->cleanUpInstance();
	TextManager::instance()->cleanupInstance();
}

void LevelEditorMenu::cleanupInstance(){
	if(m_Instance != NULL){
		delete m_Instance;
		m_Instance = NULL;
	}
}
LevelEditorMenu* LevelEditorMenu::instance(){
	if(m_Instance == NULL){
		m_Instance = new LevelEditorMenu();
	}
	return m_Instance;
}
void LevelEditorMenu::loadContent(){
	SpriteManager::instance()->
		loadTexture("PathGuy.png");
	SpriteManager::instance()->
		loadTexture("TestEnemy.png");
	SpriteManager::instance()->
		loadTexture("GroundTile.png");
	SpriteManager::instance()->
		loadTexture("WallTile.png");
	SpriteManager::instance()->
		loadTexture("EmptyTile.png");
	SpriteManager::instance()->
		loadTexture("ScrollUpD.png");
	SpriteManager::instance()->
		loadTexture("ScrollUpS.png");
	SpriteManager::instance()->
		loadTexture("ScrollDownD.png");
	SpriteManager::instance()->
		loadTexture("ScrollDownS.png");
	SpriteManager::instance()->
		loadTexture("Finished.png");
	SpriteManager::instance()->
		loadTexture("FinishedS.png");
	SpriteManager::instance()->
		loadTexture("ReturnD.png");
	SpriteManager::instance()->
		loadTexture("ReturnS.png");
	TextManager::instance()->
		loadFont("tfa_squaresans.ttf");
}
void LevelEditorMenu::initialize(){
	m_Camera = new Camera();
	m_Level = NULL;
	m_GameObjects = new std::vector<GameObject*>();
	m_GameObjectsToDelete = new std::vector<GameObject*>();
	m_Editor = NULL;
	m_LevelSelect = NULL;
	InputManager::instance()->registerMouseInput(this,MOUSE_MOVED);
}
void LevelEditorMenu::update(){
	MessageHandler::Instance()->update();
	(this->*blobUpdate)();
}
Camera* LevelEditorMenu::getCamera() const{return m_Camera;}
void LevelEditorMenu::setCamera(Camera* camera){m_Camera = camera;}
LevelEditorStates LevelEditorMenu::getState() const{return m_CurrentState;}
Level* LevelEditorMenu::getLevel() const{return m_Level;}
std::vector<GameObject*> LevelEditorMenu::getObjects() const{return *m_GameObjects;}

void LevelEditorMenu::reset(){
	InputManager::instance()->cleanUpInstance();
	initialize();
	changeState(Editor);
}

void LevelEditorMenu::addObject(GameObject* obj){
	m_GameObjects->push_back(obj);
}
void LevelEditorMenu::deleteObject(GameObject* obj){
	for(int i = 0;i < m_GameObjects->size();i++){
		if((*m_GameObjects)[i] == obj){
			m_GameObjectsToDelete->push_back(obj);
			return;
		}
	}
}

void LevelEditorMenu::changeState(const LevelEditorStates& state){
	switch(m_CurrentState){
	case Editor:
		endEditor();
		break;
	}
	switch(state){
	case Editor:
		beginEditor();
		blobUpdate = &LevelEditorMenu::editor;
		break;
	}
	m_CurrentState = state;
}
void LevelEditorMenu::editor(){
	if(m_Editing){
		m_Editor->update();
	}
	else{
		for(int i = 0;i < m_GameObjects->size();i++){
			(*m_GameObjects)[i]->update();
		}
		m_LevelSelect->update();
	}
}

void LevelEditorMenu::beginEditor(){
	SafePtrRelease(m_Editor);
	if(!m_GameObjects){
		m_GameObjects = new std::vector<GameObject*>();
	}
	m_Editing = false;
	DIR* dir;
	struct stat fileStat;
	struct dirent* dirp;
	std::string levelName;
	std::string filePath;
	unsigned int width;
	unsigned int height;
	UiButton* selectLevel = new UiButton(510,380,64,128,"Finished.png","FinishedS.png",
											FIRE_ON_RELEASED,m_Camera,loadEditor,NULL);
	m_GameObjects->push_back(selectLevel);
	m_LevelSelect = new UiListMenu(200,50,m_Camera,NULL,NULL,"tfa_squaresans.ttf",10,6);
	m_LevelSelect->setHeight(300);
	m_LevelSelect->setWidth(700);
	m_LevelSelect->addEntry("New Level");
	selectLevel->setCallBackParam(m_LevelSelect);
	
	dir = opendir("levels");
	if(dir == NULL){
		std::cout << "Levels not found!" << std::endl;
		changeState(Editor);
		return;
	}
	while((dirp = readdir(dir))){
		filePath = "levels/" + std::string(dirp->d_name);

		if(stat(filePath.c_str(),&fileStat)){continue;}
		if(S_ISDIR(fileStat.st_mode)){continue;}

		if(loadPreview(&levelName,&width,&height,filePath)){
			m_LevelSelect->addEntry("Name :" + levelName + " Size : " + intToString(width) + " X " + intToString(height)); 
		}
	}
	SafePtrRelease(dir);
}
void LevelEditorMenu::endEditor(){
	SafePtrRelease(m_Editor);
	SafePtrRelease(m_LevelSelect);
	if(m_GameObjects != NULL){
		SafeVectorDelete((*m_GameObjects));
		SafePtrRelease(m_GameObjects);
	}
}
void LevelEditorMenu::mouseInputCalback(const inputEvent& event,const int& x,const int& y){
	double delta = Util::instance()->getDelta();
	if(getState() == Editor){
		if(event == MOUSE_MOVED){
			if(x < 2){
				m_Camera->move(-CAMERA_SPEED*delta,0);
			}
			else if(x > m_Camera->getWidth() - 4){
				m_Camera->move(CAMERA_SPEED*delta,0);
			}
			if(y < 2){
				m_Camera->move(0,-CAMERA_SPEED*delta);
			}
			else if(y > m_Camera->getHeight() - 4){
				m_Camera->move(0,CAMERA_SPEED*delta);
			}
		}
	}
}
void LevelEditorMenu::handleMessage(const Message& msg){
	switch(msg.type){
	case CHANGE_STATE:{
		int s  = (int)msg.extraInfo;
		changeState((LevelEditorStates)s);
		break;
	}
	case LOAD_LEVEL_EDITOR:{
		if(m_CurrentState == Editor){
			int level = (int)msg.extraInfo - 1;
			if(level < 0){
				int tileTypes[MAX_HORIZONTAL_TILES*MAX_VERTICAL_TILES];
				for(int i = 0;i < (MAX_HORIZONTAL_TILES*MAX_VERTICAL_TILES);i++){
					tileTypes[i] = Empty;
				}
				Level* newLevel  = new Level(MAX_HORIZONTAL_TILES,MAX_VERTICAL_TILES,
												TILE_SIZE,tileTypes,NULL,NULL);
				m_Editor = new LevelEditor(newLevel,m_Camera);
				m_Editing = true;
				SafePtrRelease(m_LevelSelect);
				if(m_GameObjects != NULL){
					SafeVectorDelete((*m_GameObjects));
					SafePtrRelease(m_GameObjects);
				}
				return;
			}
			else{
				DIR* dir;
				struct stat fileStat;
				struct dirent* dirp;
				std::string levelName;
				std::string filePath;
				unsigned int width;
				unsigned int height;
				int i = 0;
				dir = opendir("levels");
				if(dir == NULL){
					std::cout << "Levels not found!" << std::endl;
					return;
				}
				while(i <= level && (dirp = readdir(dir))){
					filePath = "levels/" + std::string(dirp->d_name);

					if(stat(filePath.c_str(),&fileStat)){continue;}
					if(S_ISDIR(fileStat.st_mode)){continue;}

					if(loadPreview(&levelName,&width,&height,filePath)){
						if(i == level){
							m_Editing = true;
							m_Editor = new LevelEditor(NULL,m_Camera);
							m_Editor->loadLevelToEditor(filePath);
							SafePtrRelease(dir);
							SafePtrRelease(m_LevelSelect);
							if(m_GameObjects != NULL){
								SafeVectorDelete((*m_GameObjects));
								SafePtrRelease(m_GameObjects);
							}
							return;
						}
						else{
							i++;
						}
					}
				}
			}
			break;
		}
	}
	default:
		break;
	}
}

void changeGameState(void* state){
	MessageHandler::Instance()->createMessage(CHANGE_STATE,
		LevelEditorMenu::instance(),LevelEditorMenu::instance(),state,0);
}
void listScrollDown(void* thing){
	UiListMenu* menu = (UiListMenu*)thing;
	menu->scrollDown();
}
void listScrollUp(void* thing){
	UiListMenu* menu = (UiListMenu*)thing;
	menu->scrollUp();
}
void loadEditor(void* levelMenu){
	UiListMenu* levelselect = (UiListMenu*)levelMenu;
	MessageHandler::Instance()->createMessage(
		LOAD_LEVEL_EDITOR,NULL,LevelEditorMenu::instance(),(void*)(levelselect->getSelecedEntryNumber()-1),0);
}