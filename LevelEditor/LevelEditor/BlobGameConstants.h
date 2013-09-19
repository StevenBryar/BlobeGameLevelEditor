#ifndef BLOB_GAME_CONSTANTS
#define BLOB_GAME_CONSTANTS

#include "constants.h"

const enum TileStuff{
	Ground = (1 << 0),
	Wall   = (1 << 1),
	GruntStart = (1 << 2),
	TeleStart = (1 << 3),
	GlobStart = (1 << 4),
	MotherStart = (1 << 5),
	EnemySpawner = (1 << 6),
	PistolEnemy = (1 << 7),
	ShotgunEnemy = (1 << 8),
	Fire = (1 << 9),
	Posion = (1 << 10),
	Slime = (1 << 11),
	BlobOn = (1 << 12),
	EnemyOn = (1 << 13),
	Empty = (1 << 14),
	Hole = (1 << 15)
};

const enum UnitStuff{
	Posioned = (1 << 0),
	OnFire   = (1 << 1),
	Slowed = (1 << 3),
	Dead = (1 << 4),
	Consume = (1 << 5),
	Consumed = (1 << 6),
	ImmuneToFire = (1 << 7),
	createsSlime = (1 << 8)
};

extern const unsigned int BLOB_UNWALKABLES;
extern const unsigned int ENEMY_UNWALKABLES;
extern const int NUMBER_OF_HORIZONTAL_TILES;
extern const int NUMBER_OF_VERTICAL_TILES;
extern const int TILE_SIZE;
extern const int TEST_LEVEL_WALL_TILES[];

#define TILE_SPAWN_FLAGS GruntStart|EnemySpawner|PistolEnemy|TeleStart|GlobStart|MotherStart|ShotgunEnemy

#define BLOB_LEVEL_TAG 4096

#define MAX_HORIZONTAL_TILES 50
#define MAX_VERTICAL_TILES 50

#define MORPH_SPEED_INCREASE		4
#define ALLY_VISION 3
#define ENEMY_VISION 2
#define ENEMY_ATTACK_TIME 50
#define FRONT 0 
#define RIGHT 1
#define BACK  2
#define LEFT  3
#define PISTOL_RANGE 3
#define SHOTGUN_RANGE_LENGTH 4
#define SHOTGUN_RANGE_WIDTH 1//in either direction
#define PISTOL_DAMAGE 0
#define SHOTGUN_DAMAGE 0
#define FLAME_RANGE 3
#define GOO_TRAP_TIME 150

#define GRUNT_ENERGY_COST 10
#define GRUNT_POWER_COST 3
#define TELE_ENERGY_COST 25
#define TELE_POWER_COST 9
#define GLOB_ENERGY_COST 5
#define GLOB_POWER_COST 9

#define ENEMY_ENERGY_VALUE 100

//Messages
#define PISTOL_ATTACK 3
#define REMOVE_TILE_EFFECT 4
#define REMOVE_UNIT_STATUS 7
#define CHANGE_STATE 8
#define LOAD_LEVEL_EDITOR 10
#define LOAD_LEVEL 11
#define SHOTGUN_ATTACK 12

#define BASE_BLOB_CONSUME_TIME 50

//GruntContstants
#define GRUNT_BASE_MOVE_SPEED			15
#define GRUNT_BASE_ATTACK_SPEED			15
#define GRUNT_BASE_HEALTH				40
#define GRUNT_BASE_ARMOUR				6
#define GRUNT_BASE_DAMAGE				20

//TeleBlobConstants
#define TELE_BASE_MOVE_SPEED			25
#define TELE_BASE_ATTACK_SPEED			5
#define TELE_BASE_HEALTH				20
#define TELE_BASE_ARMOUR				6
#define TELE_BASE_DAMAGE				5

//GlobBlobConstants
#define GLOB_BASE_MOVE_SPEED			25
#define GLOB_BASE_ATTACK_SPEED			14
#define GLOB_BASE_HEALTH				35
#define GLOB_BASE_ARMOUR				10
#define GLOB_BASE_DAMAGE				12

//MotherBlobConstants
#define MOTHER_BASE_MOVE_SPEED			5
#define MOTHER_BASE_ATTACK_SPEED		10
#define MOTHER_BASE_HEALTH				60
#define MOTHER_BASE_ARMOUR				15
#define MOTHER_BASE_DAMAGE				4
#endif
