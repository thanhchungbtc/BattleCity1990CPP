#ifndef GUARD_ENEMY_H
#define GUARD_ENEMY_H
#include "ShooterObject.h"
class Enemy: public ShooterObject
{
public:
	~Enemy();
	Enemy();

	virtual void update();
	virtual void draw();
	virtual void collision();
	virtual void move();
	virtual void shot();
	
	virtual std::string type(){return "Enemy";}
	
private:
	virtual void changeDirection(){}
};
#endif // !GUARD_ENEMY_H
