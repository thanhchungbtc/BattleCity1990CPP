#include "MainMenuState.h"
#include "MenuBox.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::~MainMenuState(){}
void MainMenuState::onEnter()
{
	TextureManager::Instance()->load("images/welcome.png", "welcome",
		Game::Instance()->getRenderer());

	GameObject* box = new MenuBox();
	MenuBox* pBox = dynamic_cast<MenuBox*>(box);	
	box->load(new LoaderParams(280, 200, 32, 32, 21, 0, 1, "graphics"));
	pBox->getCallback()->push_back(s_menuToPlay);
	pBox->getCallback()->push_back(s_menuToQuit);

	m_gameObjects.push_back(box);
}
void MainMenuState::onExit()
{
	for (int i = 0; i<m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
}
void MainMenuState::update()
{
	for (int i = 0; i<m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}
void MainMenuState::render()
{
	TextureManager::Instance()->drawImage("welcome", 80, 0, 640, 400, Game::Instance()->getRenderer());
	for (int i = 0; i<m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

void MainMenuState::s_menuToPlay()
{
	Game::Instance()->setPlayerLives(3);
	Game::Instance()->setLevel(0);
	Game::Instance()->setGameOver(false);
	Game::Instance()->getGameStateMachine()->changeState(new PlayState());
}
void MainMenuState::s_menuToQuit()
{
	Game::Instance()->quit();
}