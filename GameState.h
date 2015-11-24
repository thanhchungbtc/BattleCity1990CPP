#ifndef GUARD_GAMESTATE_H
#define GUARD_GAMESTATE_H

#include <string>
// abstract class for game state
class GameState
{
public:
	virtual ~GameState(){}
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual std::string getStateID() const = 0;
	virtual void resume(){}
protected:
	

};
#endif