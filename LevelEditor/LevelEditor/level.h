#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

class Tile;
class GameObject;

class Level
{
public:
	Level(const unsigned int& horizontalTiles, const unsigned int& verticalTiles, 
		const unsigned int& tileSize,const int tileTypes[],
		std::vector<GameObject*>* objects,
		GameObject*(factory)(const unsigned int& flags,Tile* tile));

	virtual ~Level();

	//Standard lifecycle methods
	virtual void update(const double& delta);

	std::string getName() const;
	void setName(const std::string& name);

	//Tile count methods
	unsigned int getNumberOfHorizontalTiles() const;
	unsigned int getNumberOfVerticalTiles() const;

	//Validate that the tile coordinates passed in are valid
	bool validateTileCoordinates(const int& coordinatesX, const int& coordinatesY);

	//Converts a position in screen space into a position in coordinate space
	int getTileCoordinateForPosition(const int& position);

	//Index methods
	int getTileIndexForPosition(const int& positionX, const int& positionY);
	int getTileIndexForCoordinates(const int& coordinatesX, const int& coordinatesY);
	int getTileIndexForTile(Tile* tile);

	//Tile methods
	Tile* getTileForPosition(const int& positionX, const int& positionY);
	Tile* getTileForCoordinates(const int& coordinatesX, const int& coordinatesY);
	Tile* getTileForTileIndex(const int& index);

	std::vector<Tile*>* getTiles() const;

	void changeTile(Tile* replacementTile);
protected:
	//Member variables
	std::vector<Tile*>* m_Tiles;
	unsigned int m_HorizontalTiles;
	unsigned int m_VerticalTiles;
	unsigned int m_TileSize;
	std::string m_Name;
};

#endif