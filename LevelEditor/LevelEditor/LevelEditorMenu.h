#ifndef BLOBGAME_H	
#define BLOBGAME_H
#include "game.h"
#include "inputListener.h"
#include "MessageListener.h"
#include <vector>

enum LevelEditorStates{
	None,
	Editor
};

class GameObject;
class Level;
class Camera;
class Tile;
class Sprite2d;
class LevelEditor;
class UiListMenu;

class LevelEditorMenu : public Game , public InputListener , public MessageListener{
public:
	void update();
	void reset();
	void cleanupInstance();
	static LevelEditorMenu* instance();
	void mouseInputCalback(const inputEvent& event,const int& x,const int& y);
	Camera* getCamera() const;
	void setCamera(Camera* camera);
	LevelEditorStates getState() const;
	
	Level* getLevel() const;
	std::vector<GameObject*> getObjects() const;

	void addObject(GameObject* obj);
	void deleteObject(GameObject* obj);
	void addEffect(Sprite2d* effect);

	void handleMessage(const Message& msg);
	void changeState(const LevelEditorStates& state);
protected:
	LevelEditorMenu();
	virtual ~LevelEditorMenu();
	static LevelEditorMenu* m_Instance;

	void loadContent();
	void initialize();
	void (LevelEditorMenu::*blobUpdate)();

	void editor();

	void beginEditor();
	void endEditor();

	LevelEditorStates m_CurrentState;
	Level* m_Level;
	UiListMenu* m_LevelSelect;
	Camera* m_Camera;
	LevelEditor* m_Editor;
	bool m_Editing;
	std::string m_LevelToLoad;

	std::vector<GameObject*>* m_GameObjects;
	std::vector<GameObject*>* m_GameObjectsToDelete;
};

void listScrollUp(void* thing);
void listScrollDown(void* thing);
void changeGameState(void* state);
void loadEditor(void* levelMenu);
#endif