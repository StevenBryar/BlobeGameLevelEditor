
#include "BlobGameConstants.h"
#include "constants.h"
#include "Blob.h"
#include "Enemy.h"
#include "Abilities.h"
#include "EnemyAttacks.h"
#include "BlobGame.h"
#include "common.h"
#include "spriteManager.h"
#include "tile.h"
#include "UnitFactory.h"
#include "Passives.h"
#include "TileManagement.h"

GameObject* createGrunt(Tile* tile){
	Blob* blob = new Blob(GRUNT_BASE_HEALTH,GRUNT_BASE_DAMAGE,GRUNT_BASE_ATTACK_SPEED,
											GRUNT_BASE_MOVE_SPEED,GRUNT_BASE_ARMOUR,tile);
	blob->setOrigin(blob->getWidth()/2,blob->getHeight()/2);
	blob->setSprite(SpriteManager::instance()->createSprite(blob,"PathGuy.png",1));
	Ability* a = new Ability("MorphSpeed",200,false,&morphSpeed);
	blob->addAbilty(a,Q);
	a = new Ability("Split",600,false,&split);
	blob->addAbilty(a,W);
	blob->calcBaseGScore = &calcGScoreBlob;
	blob->setUnwalkables(BLOB_UNWALKABLES);

	return blob;
}
GameObject* createTele(Tile* tile){
	Blob* blob = new Blob(TELE_BASE_HEALTH,TELE_BASE_DAMAGE,TELE_BASE_ATTACK_SPEED,
											TELE_BASE_MOVE_SPEED,TELE_BASE_ARMOUR,tile);
	blob->setOrigin(blob->getWidth()/2,blob->getHeight()/2);
	blob->setSprite(SpriteManager::instance()->createSprite(blob,"PathGuy.png",1));
	Ability* a = new Ability("GroupTeleport",1200,true,&groupTeleport);
	blob->addAbilty(a,Q);
	a = new Ability("TeleportToCaster",1800,true,&teleToCaster);
	blob->addAbilty(a,W);
	blob->calcBaseGScore = &calcGScoreBlob;
	blob->setUnwalkables(BLOB_UNWALKABLES);

	return blob;
}
GameObject* createGlob(Tile* tile){
	Blob* blob = new Blob(GLOB_BASE_HEALTH,GLOB_BASE_DAMAGE,GLOB_BASE_ATTACK_SPEED,
											GLOB_BASE_MOVE_SPEED,GLOB_BASE_ARMOUR,tile);
	blob->setOrigin(blob->getWidth()/2,blob->getHeight()/2);
	blob->setSprite(SpriteManager::instance()->createSprite(blob,"PathGuy.png",1));
	Ability* a = new Ability("GooTrap",400,true,&gooTrap);
	blob->addAbilty(a,Q);
	a = new Ability("GasAttack",1800,false,&gasAttack);
	blob->addAbilty(a,W);
	blob->addPassive(&createSlime);
	blob->calcBaseGScore = &calcGScoreBlob;
	blob->addStatus(createsSlime);
	blob->setUnwalkables(BLOB_UNWALKABLES);

	return blob;
}
GameObject* createMother(Tile* tile){
	Blob* blob = new Blob(MOTHER_BASE_HEALTH,MOTHER_BASE_DAMAGE,MOTHER_BASE_ATTACK_SPEED,
											MOTHER_BASE_MOVE_SPEED,MOTHER_BASE_ARMOUR,tile);
	blob->setOrigin(blob->getWidth()/2,blob->getHeight()/2);
	blob->setSprite(SpriteManager::instance()->createSprite(blob,"PathGuy.png",1));
	Ability* a = new Ability("SpawnGrunt",0,false,&spawnGrunt);
	blob->addAbilty(a,Q);
	a = new Ability("SpawnTele",0,false,&spawnTele);
	blob->addAbilty(a,W);
	a = new Ability("SpawnGlob",0,false,&spawnGlob);
	blob->addAbilty(a,E);
	blob->addPassive(&gatherResources);
	blob->setEnergy(50);
	blob->calcBaseGScore = &calcGScoreBlob;
	blob->setUnwalkables(BLOB_UNWALKABLES);

	return blob;
}

GameObject* createPistolEnemy(Tile* tile){
	Enemy* enemy = new Enemy(NULL,40,5,20,GRUNT_BASE_MOVE_SPEED,4,tile,
						"TestEnemy.png",&pistolRange,&pistolAttack,PISTOL_RANGE);
	enemy->setOrigin(enemy->getWidth()/2,enemy->getHeight()/2);
	enemy->calcBaseGScore = &calcGScoreBasicEnemy;
	enemy->setUnwalkables(ENEMY_UNWALKABLES);

	return enemy;
}
GameObject* createShotgunEnemy(Tile* tile){
	Enemy* enemy = new Enemy(NULL,40,5,20,GRUNT_BASE_MOVE_SPEED,4,tile,
						"TestEnemy.png",&shotgunRange,&shotgunAttack,SHOTGUN_RANGE_LENGTH);
	enemy->setOrigin(enemy->getWidth()/2,enemy->getHeight()/2);
	enemy->calcBaseGScore = &calcGScoreBasicEnemy;
	enemy->setUnwalkables(ENEMY_UNWALKABLES);

	return enemy;
}

GameObject* createUnit(const unsigned int& spawnFlags,Tile* tile){
	if(ContainsFlags(spawnFlags,GruntStart)){
		return createGrunt(tile);
	}
	else if(ContainsFlags(spawnFlags,TeleStart)){
		return createTele(tile);
	}
	else if(ContainsFlags(spawnFlags,GlobStart)){
		return createGlob(tile);
	}
	else if(ContainsFlags(spawnFlags,MotherStart)){
		return createMother(tile);
	}
	else if(ContainsFlags(spawnFlags,PistolEnemy)){
		return createPistolEnemy(tile);
	}
	else if(ContainsFlags(spawnFlags,ShotgunEnemy)){
		return createShotgunEnemy(tile);
	}

	return NULL;
}