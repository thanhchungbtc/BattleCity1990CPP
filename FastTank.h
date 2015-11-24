#ifndef GUARD_FASTTANK_H
#define GUARD_FASTTANK_H
#include "Enemy.h"
#include "ShooterObject.h"
#include "Bullet.h"
class FastTank:public Enemy
{
public:
	~FastTank(){
		ShooterObject::~ShooterObject();
	}
	FastTank(int health = 1):
	Enemy(){
		// stupid tank specified
		m_width = 32;
		m_height = 32;		
		m_health = health;
		m_startRow = m_currentRow = 2;
		m_startFrame = 4;
		m_currentFrame = m_startFrame + (m_health - 1)*4;
		m_bulletPerShot = 1;
		m_bulletSpeed = 6;
		m_moveSpeed = 4;
		m_textureID = "graphics";
		
		m_position.setX(0);
		m_position.setY(0);
		m_direction = DOWN;
		m_velocity.setY(m_moveSpeed);
	}

	virtual void update()
	{
		Enemy::update();
	}
	virtual void draw()
	{
		Enemy::draw();
	}
	virtual void collision()
	{
		Enemy::collision();
	}
	virtual void move()
	{
		Enemy::move();
	}

	virtual void shot()
	{
		static int timeBetweenShot = 150;
		static int waitForNewShot = 40 + rand()%timeBetweenShot;
		static int count = 0;
		count++;
		if (checkShotPosible() && count > waitForNewShot)
		{
			Bullet* pBullet = new EnemyBullet(this);
			m_bullets.push_back(pBullet);			
			waitForNewShot = rand()%timeBetweenShot;
			count = 0;
		}
	}

private:
	virtual void changeDirection()
	{
		m_velocity.setX(0);
		m_velocity.setY(0);
		switch (rand()%4)
		{
		case  UP:
			m_direction = UP;
			m_velocity.setY(-m_moveSpeed);
			break;
		case  RIGHT:
			m_direction = RIGHT;
			m_velocity.setX(m_moveSpeed);
			break;
		case DOWN:
			m_direction = DOWN;
			m_velocity.setY(m_moveSpeed);
			break;
		case LEFT:
			m_direction = LEFT;
			m_velocity.setX(-m_moveSpeed);
			break;
		default:
			break;
		}
	}
};
#endif