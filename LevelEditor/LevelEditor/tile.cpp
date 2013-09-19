#include "tile.h"
#include "spriteManager.h"
#include "constants.h"
#include "BlobGameConstants.h"
#include "2dSprite.h"
#include "common.h"

int Tile::m_TileCount = 0;
Tile::Tile(const unsigned int& tileTypes) :
GameObject(),
 m_TileTypes(tileTypes){
	 if(ContainsFlags(tileTypes,Ground)){
		setSprite(SpriteManager::instance()->
		 createSprite(this,"GroundTile.png",10));
	 }
	 else if(ContainsFlags(tileTypes,Wall)){
		 setSprite(SpriteManager::instance()->
		 createSprite(this,"WallTile.png",10));
	 }
	 else if(ContainsFlags(tileTypes,Empty)){
		 setSprite(SpriteManager::instance()->
		 createSprite(this,"EmptyTile.png",10));
	 }
	 m_TileCount++;
	 m_Name = "Tile" + intToString(m_TileCount);
	 if(getSprite()){
		 getSprite()->setColor(70,70,70,255);
	 }
 }

Tile::~Tile(){}

std::string Tile::getType() const{
	return "Tile";
}

void Tile::update(const double& delta){}

void Tile::setTileTypes(const unsigned int& types){m_TileTypes = types;}
unsigned int Tile::getTileTypes() const{return m_TileTypes;}
