#ifndef GUARD_LEVELCHANGESTATE_H
#define GUARD_LEVELCHANGESTATE_H
#include "GameState.h"
#include <string>
class LevelChangeState: public GameState
{
public:

	virtual ~LevelChangeState();
	virtual void onEnter();
	virtual void onExit();
	virtual void update();
	virtual void render();
	virtual std::string getStateID() const {return "LEVELCHANGE";}
};
#endif