#include "Enemy.h"
#include "Bullet.h"
#include <SDL_rect.h>
#include "Collision.h"

Enemy::~Enemy()
{
	ShooterObject::~ShooterObject();
}
Enemy::Enemy():
	ShooterObject()
{		
	m_appearTime = 120;
}

void Enemy::update()
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
				m_currentFrame = m_startFrame + m_direction + (m_health - 1)*4;
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
void Enemy::draw()
{
	ShooterObject::draw();
}
void Enemy::collision()
{
	ShooterObject::collision();	
	// handle enemy contains bonus

}
void Enemy::move()
{
	// check for move capacity
	m_canMove = true;
	checkMovePosible();		
	checkObjectsCollision();
	checkMapCollision();
	//---------------------------------
	if (m_canMove)
	{
		m_position += m_velocity;
		// random change direction
		if (rand()%100 == 0) // 1%
		{
			changeDirection();
		}
	}
	else
	{
		changeDirection();
	}		
}
void Enemy::shot()
{

}

