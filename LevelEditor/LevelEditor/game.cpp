#include "game.h"
#include "common.h"

Game* Game::m_Instance = NULL;

Game* Game::instance(){return m_Instance;}
void Game::cleanupInstance(){}
void Game::reset(){}

Game::Game(){}
Game::~Game(){}
void Game::loadContent(){}
void Game::initialize(){}
	