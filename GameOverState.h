#ifndef GUARD_GAMEOVERSTATE_H
#define GUARD_GAMEOVERSTATE_H
#include "GameState.h"
#include <string>
class GameOverState: public GameState
{
public:
	virtual ~GameOverState();
	virtual void onEnter();
	virtual void onExit();
	virtual void update();
	virtual void render();
	virtual std::string getStateID() const {return "GAMEOVERSTATE";}
};
#endif