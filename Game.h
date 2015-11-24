#ifndef GUARD_GAME_H
#define GUARD_GAME_H
#include "SDL.h"
#include "MainMenuState.h"
#include "GameStateMachine.h"
#include "SoundManager.h"

const int MAX_LEVEL = 20;
class Game
{
public:
	bool init(const char* tilte, int xpos, int ypos, int width, int height);
	void update();
	void render();
	void handleEvents();
	void clean();

	SDL_Renderer* getRenderer() const {return m_pRenderer;}
	static Game* Instance(){
		if (!s_pInstance)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
	bool running() const {return m_bRunning;}
	void quit(){m_bRunning = false;}
	bool isKeyDown(int key);

	GameStateMachine* getGameStateMachine(){return m_pGameStateMachine;}

	int getGameWidth() const{return m_width;}
	int getGameHeight() const{return m_height;}
	void onGameOver();
	bool gameOver() const{return m_bGameOver;}
	void setGameOver(bool gameOver){m_bGameOver = gameOver;}
	void setPlayerLives(int playerLives){m_playerLives = playerLives;}
	int getPlayerLives()const{return m_playerLives;}
	int getCurrentLevel() const{return m_currentLevel;}
	void setLevel(int level){m_currentLevel = level;}
private: 
	Game();
	static Game* s_pInstance;
private:
	bool m_bGameOver;
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	GameStateMachine* m_pGameStateMachine;

	// handleEvents
	const Uint8* m_keystates;

	int m_width;
	int m_height;

	int m_playerLives;
	int m_currentLevel;
};


#endif // !GUARD_GAME_H


