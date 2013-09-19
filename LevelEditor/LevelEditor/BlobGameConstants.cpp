#include "BlobGameConstants.h"

const unsigned int BLOB_UNWALKABLES = Wall | BlobOn | Hole;
const unsigned int ENEMY_UNWALKABLES = Wall | BlobOn | EnemyOn | Hole;
const int NUMBER_OF_HORIZONTAL_TILES = 16;
const int NUMBER_OF_VERTICAL_TILES = 12;
const int TILE_SIZE = 64;
const int TEST_LEVEL_WALL_TILES[] = { Wall, Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,
									  Wall, Ground, Ground | GruntStart, Ground, Ground | GruntStart, Ground, Ground, Ground | PistolEnemy, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Wall,
									  Wall, Ground | GruntStart, Wall,   Wall,   Wall,   Ground, Wall,   Wall,   Wall,   Wall,   Ground, Wall,   Wall,   Wall,   Ground, Wall,
									  Wall, Ground, Wall,   Ground, Ground | MotherStart, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Wall,   Ground, Wall,
									  Wall, Ground, Wall,   Ground, Ground, Wall,   Ground | GlobStart, Ground, Ground, Ground, Wall,   Ground, Ground, Wall,   Ground, Wall,
									  Wall, Ground, Ground, Ground, Ground, Ground, Ground, Wall,   Wall,   Ground, Ground, Ground, Ground, Ground, Ground, Wall,
									  Wall, Ground, Ground, Ground, Ground, Ground, Ground, Wall,   Wall,   Ground, Ground, Ground, Ground, Ground, Ground, Wall,
									  Wall, Ground, Wall,   Ground, Ground, Wall,   Ground | PistolEnemy, Ground, Ground, Ground, Wall,   Ground, Ground, Wall,   Ground, Wall,
									  Wall, Ground, Wall,   Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Wall,   Ground, Wall,
									  Wall, Ground, Wall,   Wall,   Wall,   Ground, Wall,   Wall,   Wall,   Wall,   Ground, Wall,   Wall,   Wall,   Ground, Wall,
									  Wall, Ground, Ground, Ground | PistolEnemy, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Ground, Wall,
									  Wall, Wall,	Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall,   Wall};