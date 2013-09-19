#ifndef Tile_H
#define Tile_H

#include "GameObject.h"

class Tile : public GameObject{
public:
	Tile(const unsigned int& tileTypes);
	~Tile();

	void update(const double& delta);

	void setTileTypes(const unsigned int& types);
    unsigned int getTileTypes() const;
	std::string getType() const;
protected:
	unsigned int m_TileTypes;
	static int m_TileCount;
};
#endif