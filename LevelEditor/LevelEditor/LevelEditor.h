#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include "inputListener.h"
#include <string>
#include <vector>

class Level;
class Tile;
class Camera;
class UiListMenu;
class UiTextBox;
class UiButton;
class Sprite2d;
class GameObject;
class UiTextTag;

class LevelEditor : public InputListener {
public:
	LevelEditor(Level* level,Camera* camera);
	virtual ~LevelEditor();

	bool loadLevelToEditor(const std::string& path);
	bool saveLevelFromEditor(const std::string& dFolder);
	void setCamera(Camera* camera);
	Camera* getCamera() const;
	void update();
	void mouseInputCalback(const inputEvent& event,const int& x,const int& y);
protected:
	void changeTile(const unsigned int& tileType,const int& posX,const int& posY);

	Level* m_Level;
	Camera* m_Camera;
	UiButton* m_ObjectsUp;
	UiButton* m_ObjectsDown;
	UiButton* m_BaseTilesUp;
	UiButton* m_BaseTilesDown;
	UiButton* m_SaveLevel;
	UiButton* m_ReturnToMenu;
	UiListMenu* m_BaseTiles;
	UiListMenu* m_Objects;
	UiTextBox* m_NameBox;
	std::vector<Sprite2d*>* m_ObjectSprites;
	UiTextTag* m_NameTag;
	
};

bool   loadPreview(std::string* name,unsigned int* width,unsigned int* height,const std::string& path);
Level* loadLevel(const std::string& path,bool editMode,
				std::vector<GameObject*>* objects,
				GameObject*(factory)(const unsigned int& flags,Tile* tile));
void   saveLevel(const std::string& path,Level* level);

void saveLevelInEditorCB(void* levelEditor);
#endif