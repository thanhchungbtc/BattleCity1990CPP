#ifndef GUARD_PLAYER_H
#define GUARD_PLAYER_H

#include "ShooterObject.h"
#include <string>
class Player: public ShooterObject
{
public:
	~Player();
	Player();

	virtual void update();
	virtual void draw();
	virtual void collision();
	virtual void move();
	virtual void shot();


	virtual std::string type(){return "Player";}
private:
	void handleInput();
	void resurrect();
	virtual void doDyingAnimation();
	virtual void checkMapCollision();
	virtual void doAppearAnimation();
};
#endif // !GUARD_PLAYER_H
