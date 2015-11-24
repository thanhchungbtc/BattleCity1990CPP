#ifndef GUARD_HEAVY_TANK
#define GUARD_HEAVY_TANK
#include "Enemy.h"
#include "ShooterObject.h"
#include "Bullet.h"
class HeavyTank:public Enemy
{
public:
	~HeavyTank(){
		ShooterObject::~ShooterObject();
	}
	HeavyTank(int health = 1):
	Enemy(){
		
		m_width = 32;
		m_height = 32;	
		m_health = 2*health;
		m_startRow = m_currentRow = 6;
		m_startFrame = 4;
		m_currentFrame = m_startFrame + ((m_health + 1)/2 - 1)*4;
		m_bulletPerShot = 1;
		m_bulletSpeed = 6;
		m_moveSpeed = 1;		
		m_textureID = "graphics";
		
		m_position.setX(0);
		m_position.setY(0);
		m_direction = DOWN;
		m_velocity.setY(m_moveSpeed);
	}

	virtual void update()
	{
		if (m_bAppearing)
		{
			doAppearAnimation();			
		}
		else
		{
			if (m_bDying)
			{
				doDyingAnimation();
			}
			else
			{			
				shot();
				move();		
				if (m_velocity.getX() != 0 || m_velocity.getY() != 0)
				{
					// move animation
					m_currentRow = m_currentRow == m_startRow ? m_currentRow + 1 : m_startRow;

					// new from shooter object
					m_currentFrame = m_startFrame + m_direction + ((m_health+1)/2 - 1)*4;
					//-----------------------------------------------
				}			
			}
			// update bullets
			if (!m_bullets.empty())
			{
				for (std::vector<Bullet*>::iterator it= m_bullets.begin(); it != m_bullets.end();)
				{
					if ((*it)->dead())
					{
						delete (*it);
						it = m_bullets.erase(it);
					}
					else
					{
						(*it)->update();
						++it;
					}
				}			
			}
		}	
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