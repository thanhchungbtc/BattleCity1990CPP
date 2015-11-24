#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "SoundManager.h"

using namespace  std;

Game* Game::s_pInstance = 0;
Game::Game(){
	
}
bool Game::init(const char* tilte, int xpos, int ypos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_width = 640;
		m_height = 480;
		cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(tilte, xpos, ypos, width, height, 0);
		if (m_pWindow != 0)
		{
			cout << "window init success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
			if (m_pRenderer != 0)
			{
				cout << "renderer init success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				cout << "renderer init failed\n";
				return false;
			}
		}
		else
		{
			cout << "Window init failed\n";
			return false;
		}
	}
	else
	{
		cout << "SDL init failed\n";
		return false;
	}
	
	TextureManager::Instance()->load("images/graphics.png", "graphics", m_pRenderer);
	TextureManager::Instance()->load("images/gameover.png", "gameover", m_pRenderer);
	TextureManager::Instance()->load("images/armor.png", "armor", m_pRenderer);

	SoundManager::Instance()->load("sounds/levelstarting.ogg", "start", SOUND_SFX);
	SoundManager::Instance()->load("sounds/eexplosion.ogg", "tankexplosion", SOUND_SFX);
	SoundManager::Instance()->load("sounds/shoot.ogg", "shoot", SOUND_SFX);
	SoundManager::Instance()->load("sounds/brickhit.ogg", "brickhit", SOUND_SFX);
	SoundManager::Instance()->load("sounds/steelhit.ogg", "steelhit", SOUND_SFX);
	SoundManager::Instance()->load("sounds/gameover.ogg", "gameover", SOUND_SFX);
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());


	m_playerLives = 3;
	m_bRunning = true;
	m_bGameOver = false;
	m_currentLevel = 0;
	return true;
}
void Game::update()
{
	m_pGameStateMachine->update();
	if (m_bGameOver)
	{
		//pGameOver->update();
	}
}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}
void Game::handleEvents()
{
	SDL_Event e;
	m_keystates = SDL_GetKeyboardState(0);
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case  SDL_QUIT:
			m_bRunning = false;
			break;

		case  SDL_KEYDOWN:
			m_keystates = SDL_GetKeyboardState(0);
			break;

		case  SDL_KEYUP:
			m_keystates = SDL_GetKeyboardState(0);
			break;
		default:
			break;
		}
	}
}
void Game::clean()
{

}

bool Game::isKeyDown(int key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}		
	}
	return false;
}

void Game::onGameOver()
{
	SoundManager::Instance()->playSound("gameover", 0);
	m_bGameOver = true;		
	//pGameOver = new AnimatedGraphic();
}