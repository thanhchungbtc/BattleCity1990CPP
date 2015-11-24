#ifndef GUARD_BULLET_H
#define GUARD_BULLET_H
#include "ShooterObject.h"

class Bullet: public ShooterObject
{
public:
	Bullet(ShooterObject* owner);
	virtual void update();
	virtual void draw();
	virtual void collision();
	virtual void move();
	virtual void shot();

	virtual std::string type(){return "Bullet";}

private:
	void killTileMap(Direction direction, int *tileID);
	
private:
	virtual void doDyingAnimation();
	virtual void checkBulletsObjectsCollision(){}
	virtual void checkMapCollision();
	ShooterObject* m_owner;

};
class PlayerBullet:public Bullet
{
public:
	PlayerBullet(ShooterObject* owner):Bullet(owner){}
	virtual std::string type(){return "PlayerBullet";}
private:
	virtual void checkBulletsObjectsCollision();
};
class EnemyBullet: public Bullet
{
public:
	EnemyBullet(ShooterObject* owner):Bullet(owner){}
	virtual std::string type(){return "EnemyBullet";}
private:
	virtual void checkBulletsObjectsCollision();
};

#endif // !GUARD_BULLET_H