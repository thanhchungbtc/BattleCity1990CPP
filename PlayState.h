#ifndef GUARD_PLAYSTATE_H
#define GUARD_PLAYSTATE_H
#include <string>
#include "GameState.h"
#include "Level.h"
#include "AnimatedGraphic.h"
//#include "Level.h"
class PlayState: public GameState
{
public:
	virtual ~PlayState(){}
	virtual void onEnter();
	virtual void onExit();
	virtual void update();
	virtual void render();
	virtual std::string getStateID() const {return "PLAY";}
	
private:
	Level* pLevel;
	AnimatedGraphic* pGameOver;
};
#endif