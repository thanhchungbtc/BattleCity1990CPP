#include "PlayState.h"
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "AnimatedGraphic.h"


void PlayState::onEnter()
{
	Game::Instance()->setLevel(Game::Instance()->getCurrentLevel() + 1);
	SoundManager::Instance()->playSound("start", 0);

	TextureManager::Instance()->load("images/bullet1.png", "bullet1", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("images/smallexplosion.png", "smallexplosion", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("images/tankexplosion.png", "tankexplosion", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("images/map.png", "map", Game::Instance()->getRenderer());
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("level.xml");	
	
	pGameOver = new AnimatedGraphic();
	
}
void PlayState::onExit()
{
	delete pLevel;
}
void PlayState::update()
{
	pLevel->update();
	
	if (Game::Instance()->gameOver())
	{
		pGameOver->update();
	}
}
void PlayState::render()
{
	pLevel->render();	
	// draw border
	for (int i = 0; i<30; ++i) // 30 rows
	{
		TextureManager::Instance()->drawFrame("map", 640, i*16, 16, 16, 2, 2, Game::Instance()->getRenderer());
	}

	// draw player lives
	for (int i = 0; i<Game::Instance()->getPlayerLives(); ++i)
	{
		if (i>=3)
		{
			break;
		}
		TextureManager::Instance()->drawFrame("graphics", 660 +i*32, 400, 32, 32, 0, 20, Game::Instance()->getRenderer());
	}
	// --------------------------------------------------
	// draw remain enemies
	for (int i = 0; i<pLevel->getLevelObjects()->size(); ++i)
	{
		ShooterObject* pObject = (*pLevel->getLevelObjects())[i];
		pObject->drawAt(660 + i%3 * 32, i/3 * 32);
	}


	if (Game::Instance()->gameOver())
	{
		pGameOver->draw();
	}
}