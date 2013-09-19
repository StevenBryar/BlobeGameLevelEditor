#ifndef SELECTION_MANAGER_H
#define SELECTION_MANAGER_H

#include "InputListener.h"
#include <map>
#include <vector>
//select a Unit with mouse click
//select multiple Units with click and drag.
//inform selected Units of key commands
//select target(Tile,ally,enemy)
//inform Game about selections(to update ui)
//handle hotKey groups and selection.
//enemies and allies cannot both be selected
//if an ally is apart of selection, drop all enemies.
//centre on selection if space is pressed.
//on right click check if key down.
//if not check tile under cursor for unit.
//if no and no ally currently selected do nothing.
//if no and ally selected move to.
//if no and enemy selected deselect.
//if yes(enemy) and ally selected attack.
//if key down on right click
//check if ally selected 
//if yes call allies use ability method and pass key.
//if no do nothing
class Blob;
class GameObject;
class Enemy;
class Unit;
class Tile;
class Sprite2d;

enum selectStates{
	NORMAL_STATE,
	DRAG_SELECT_STATE,
};

class SelectionManager :
	public InputListener{
public:
	static SelectionManager* instance();
	void cleanupInstance();
	void keyInputCallback(const keyType& key,const inputEvent& event);
	void mouseInputCalback(const inputEvent& event,const int& x,const int& y);
	void update();
private:
	SelectionManager();
	virtual ~SelectionManager();
	static SelectionManager* m_Instance;
	std::map<int,std::vector<Blob*>>* m_HotKeys;
	std::vector<Unit*>* m_Selected;
	double m_DClickTimer;
	bool m_DClick;
	int m_PrevMousePosX;
	int m_PrevMousePosY;
	Sprite2d* m_DragSprite;
	selectStates m_State;
};

#endif