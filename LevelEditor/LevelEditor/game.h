#ifndef Game_H
#define Game_H

class Game{
public:
	static Game* instance();
	virtual void cleanupInstance();
	virtual void update() = 0;
	virtual void reset();
protected:
	Game();
	virtual ~Game();
	virtual void loadContent();
	virtual void initialize();
	static Game* m_Instance;
};

#endif