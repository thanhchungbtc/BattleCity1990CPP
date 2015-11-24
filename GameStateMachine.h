#ifndef GUARD_GAMESTATEMACHINE_H
#define GUARD_GAMESTATEMACHINE_H
#include "GameState.h"
#include <vector>
class GameStateMachine
{
public:
	GameStateMachine(){}
	~GameStateMachine(){}

	void update();
	void render();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void clean();


private:
	std::vector<GameState*> m_gameStates;
};
#endif