#ifndef GUARD_SHOOTER_OBJECT_H
#define GUARD_SHOOTER_OBJECT_H
#include "GameObject.h"
#include "Level.h"
#include <vector>
typedef enum{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
} Direction;

class Bullet;
class ShooterObject: public GameObject
{
public:
	~ShooterObject();
	ShooterObject();

	virtual void update();
	virtual void draw();
	virtual void collision();
	virtual void move();
	virtual void shot();
	virtual void clean(){}
	virtual std::string type(){return "SDLGameObject";}

	bool dead() const {return m_bDead;}
	bool dying() const {return m_bDying;}
	bool appearing() const {return m_bAppearing;}
	int getBulletSpeed() const {return m_bulletSpeed;}
	Direction getDirection() const {return m_direction;}
	
	void setLevel(Level* level){pLevel = level;}
	Level* getLevel() const {return pLevel;}
	std::vector<Bullet*>* getBullets() {return &m_bullets;}
	virtual void drawAt(int x, int y);

	bool invulnerable() const{return m_bInvulnerable;}
protected:
	virtual void doDyingAnimation();
	virtual void doAppearAnimation();
	void checkMovePosible();
	bool checkShotPosible();
	void checkObjectsCollision();
	void checkMapCollision();
	virtual void doInvulnerableAnimation();
protected:
	// appear animation variables
	int m_appearCounter;
	int m_appearTime;
	bool m_bAppearing;

	// move variables
	Direction m_direction;
	int m_moveSpeed;
	bool m_canMove;

	// level the object is in
	Level *pLevel;
	//-----------------------------------------------------
	// attack capacity
	int m_bulletPerShot;
	int m_bulletSpeed;
	std::vector<Bullet*> m_bullets;	

	// dying animation variables
	int m_dyingCounter;
	int m_dyingTime;
	bool m_bDying;
	bool m_bDead;
	int m_health;

	// invulnerable
	int m_invulnerableCounter;
	int m_invulnerableTime;
	int m_bInvulnerable;
	int m_invulnerableFrame;
};
#endif // !GUARD_SHOOTER_OBJECT_H
