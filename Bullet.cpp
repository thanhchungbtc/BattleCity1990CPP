#include "Bullet.h"
#include "SDL.h"
#include "Collision.h"
#include "Game.h"
#include "SoundManager.h"
Bullet::Bullet(ShooterObject* owner):
	ShooterObject()
{
	m_owner = owner;
	pLevel = owner->getLevel();
	m_width = 11;
	m_height = 11;
	m_currentFrame = 0;
	m_currentRow = 0;

	m_textureID = "bullet1";
	m_moveSpeed = owner->getBulletSpeed();
	m_direction = owner->getDirection();
	m_health = 1;
	m_dyingTime = 1;
	m_dyingCounter = 0;

	// determine appear position of bullet
	if (m_direction == UP)
	{
		m_velocity.setY(-m_moveSpeed);
		m_position.setY(owner->getPosition().getY());
		m_position.setX(owner->getPosition().getX() + (owner->getWidth()-m_width)/2);
	}
	else if(m_direction == RIGHT)
	{
		m_velocity.setX(m_moveSpeed);		
		m_position.setY(owner->getPosition().getY() + (owner->getHeight() - m_height)/2);
		m_position.setX(owner->getPosition().getX() + owner->getWidth());
	}
	else if(m_direction == DOWN)
	{
		m_velocity.setY(m_moveSpeed);
		m_position.setY(owner->getPosition().getY() + owner->getHeight());
		m_position.setX(owner->getPosition().getX() + (owner->getWidth() - m_width)/2);
	}
	else if(m_direction == LEFT)
	{
		m_velocity.setX(-m_moveSpeed);		
		m_position.setY(owner->getPosition().getY() +  (owner->getHeight() - m_height)/2);
		m_position.setX(owner->getPosition().getX());
	}
}

void Bullet::update()
{
	checkBulletsObjectsCollision();
	checkMapCollision();
	if (!m_bDying)
	{
		move();		
	}
	else
	{
		doDyingAnimation();
	}	
}

void Bullet::draw()
{
	ShooterObject::draw();
}
void Bullet::collision()
{
	m_health--;
	if (m_health == 0)
	{
		m_textureID = "smallexplosion";
		m_width = 11;
		m_height = 11;
			
		m_numFrames = 4;
		m_currentRow = 0;
		m_bDying = true;
	}
}
void Bullet::move()
{
	checkMovePosible();
	if (m_canMove)
	{
		m_position += m_velocity;
	}
	else
	{
		collision();
	}
}
void Bullet::shot()
{
	// do nothing
}

void Bullet::doDyingAnimation()
{
	// explosion frame
	m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));

	// m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % 9));

	if (m_dyingCounter == m_dyingTime) // dying finished
	{
		m_bDying = false;
		m_bDead = true;
	}
	m_dyingCounter++;	
}


void Bullet::checkMapCollision()
{
	std::vector<std::vector<int>>* tilesIDs = pLevel->getTileIDs();
	Vector2D newPosition = m_position + m_velocity;
	SDL_Rect rect1;
	rect1.x = newPosition.getX();
	rect1.y = newPosition.getY();
	rect1.w = m_width;
	rect1.h = m_height;

	if (rect1.x < 0){rect1.x = 0;}
	if (rect1.y < 0){rect1.y = 0;}
	if (rect1.x + rect1.w >= Game::Instance()->getGameWidth()){rect1.x = Game::Instance()->getGameWidth() - rect1.w -1;}
	if (rect1.y + rect1.h >= Game::Instance()->getGameHeight()){rect1.y = Game::Instance()->getGameHeight() - rect1.h -1;}
	// get tile id at rect1's area	
	if (m_direction == UP)
	{
		int r, c1, c2;
		r = (rect1.y)/16;
		c1 = (rect1.x)/16;
		c2 = (rect1.x + rect1.w - 1)/16;		
		for (int i = c1; i<=c2; ++i)
		{
			// no collidable tile
			if ((*tilesIDs)[r][i] == 0 ||(*tilesIDs)[r][i] == 10 || (*tilesIDs)[r][i] == 11 || (*tilesIDs)[r][i] == 13 || (*tilesIDs)[r][i] == 14 ||(*tilesIDs)[r][i] == 15||(*tilesIDs)[r][i] == 9)
			{
				continue;
			}

			if ((*tilesIDs)[r][i] != 0)
			{
				m_position.setY((r+1)*16 );
				m_canMove = false;							
				if (!m_bDying)
				{																	
					killTileMap(UP, &(*tilesIDs)[r][i]);						
				}						
			}			
		}		
	}
	else if (m_direction == RIGHT)
	{
		int c, r1, r2;
		c = (rect1.x)/16;
		r1 = rect1.y/16;
		r2 = (rect1.y + rect1.h - 1)/16;
		for (int i = r1; i <= r2; ++i)
		{
			// no collidable tile
			if ((*tilesIDs)[i][c] == 0 ||(*tilesIDs)[i][c] == 10 || (*tilesIDs)[i][c] == 11 || (*tilesIDs)[i][c] == 14 ||(*tilesIDs)[i][c] == 15||(*tilesIDs)[i][c] == 13||(*tilesIDs)[i][c] == 9)
			{
				continue;
			}

			if ((*tilesIDs)[i][c] != 0)
			{
				m_position.setX((c)*16 - m_width);
				m_canMove = false;
				if (!m_bDying)
				{
					killTileMap(RIGHT, &(*tilesIDs)[i][c]);
				}		
			}
		}
	}
	else if (m_direction == DOWN)
	{
		int r, c1, c2;
		r = (rect1.y)/16;
		c1 = (rect1.x)/16;
		c2 = (rect1.x + rect1.w - 1)/16;
		for (int i = c1; i<=c2; ++i)
		{
			// no collidable tile
			if ((*tilesIDs)[r][i] == 0 ||(*tilesIDs)[r][i] == 10 || (*tilesIDs)[r][i] == 11 || (*tilesIDs)[r][i] == 14 ||(*tilesIDs)[r][i] == 15||(*tilesIDs)[r][i] == 13||(*tilesIDs)[r][i] == 9)
			{
				continue;
			}

			if ((*tilesIDs)[r][i] != 0)
			{
				m_position.setY((r)*16 - m_height);
				m_canMove = false;
				if (!m_bDying)
				{
					killTileMap(DOWN, &(*tilesIDs)[r][i]);
				}		
			}
		}
	}
	else if (m_direction == LEFT)
	{
		int c, r1, r2;
		c = (rect1.x)/16;
		r1 = rect1.y/16;
		r2 = (rect1.y + rect1.h - 1)/16;
		for (int i = r1; i <= r2; ++i)
		{
			// no collidable tile
			if ((*tilesIDs)[i][c] == 0 ||(*tilesIDs)[i][c] == 10 || (*tilesIDs)[i][c] == 11 || (*tilesIDs)[i][c] == 14 ||(*tilesIDs)[i][c] == 15 ||(*tilesIDs)[i][c] == 13||(*tilesIDs)[i][c] == 9)
			{
				continue;
			}
			if ((*tilesIDs)[i][c] != 0)
			{
				m_position.setX((c + 1)*16);
				m_canMove = false;
				if (!m_bDying)
				{
					killTileMap(LEFT, &(*tilesIDs)[i][c]);
				}			
			}
		}
	}
		
	if (!m_canMove)
	{
		collision();
	}
}

void Bullet::killTileMap(Direction direction, int *tileID)
{
	switch(*tileID)
	{
	case 1: // brick
		if (type()=="PlayerBullet")
		{
			SoundManager::Instance()->playSound("brickhit", 0);
		}
		
		switch(direction)
		{
		case UP:
			(*tileID) = 6;
			break;
		case RIGHT:
			*tileID = 7;
			break;
		case DOWN:
			*tileID = 2;
			break;
		case LEFT:
			*tileID = 3;
			break;
		}
		break;
	case 5: // stone
		if (type()=="PlayerBullet")
		{
			SoundManager::Instance()->playSound("steelhit", 0);
		}
		break;
	case 10: // glass
		break;
	default:
		*tileID = 0;
		break;
	}
}

void PlayerBullet::checkBulletsObjectsCollision()
{
	if (m_bDying)
	{
		return;
	}
	SDL_Rect rect1;
	rect1.x = m_position.getX();
	rect1.y = m_position.getY();
	rect1.w = m_width;
	rect1.h = m_height;
	for (int j = 0; j<pLevel->getShooterObjects()->size(); ++j)
	{
		ShooterObject* pObject = (*pLevel->getShooterObjects())[j];
		if (pObject->type() == std::string("Player") || pObject->dying() || pObject->appearing())
		{
			continue;
		}
		SDL_Rect rect2;
		rect2.x = pObject->getPosition().getX();
		rect2.y = pObject->getPosition().getY();
		rect2.w = pObject->getWidth();
		rect2.h = pObject->getHeight();
		// check collision with enemy bullet
		if (!pObject->getBullets()->empty())
		{
			for (int k = 0; k<pObject->getBullets()->size(); ++k)
			{
				Bullet* pBullet = (*pObject->getBullets())[k];
				// bug here
				if (pBullet->dying())
				{
					continue;
				}
				SDL_Rect rectBullet;				
				rectBullet.x = pBullet->getPosition().getX();
				rectBullet.y = pBullet->getPosition().getY();
				rectBullet.w = pBullet->getWidth();
				rectBullet.h = pBullet->getHeight();
				if (RectRect(&rect1, &rectBullet))
				{
					collision();
					pBullet->collision();
					break;
				}
			}
		}
		// check collision with object
		if (!m_bDying)
		{
			if (RectRect(&rect1, &rect2))
			{
				collision();
				pObject->collision();
				break;
			}
		}						
	}
}

void EnemyBullet::checkBulletsObjectsCollision()
{
	if (m_bDying)
	{
		return;
	}
	SDL_Rect rect1;
	rect1.x = m_position.getX();
	rect1.y = m_position.getY();
	rect1.w = m_width;
	rect1.h = m_height;
	for (int j = 0; j<pLevel->getPlayerObjects()->size(); ++j)
	{
		ShooterObject* pObject = (*pLevel->getPlayerObjects())[j];
		if (pObject->dying() || pObject->appearing())
		{
			continue;
		}
		SDL_Rect rect2;
		rect2.x = pObject->getPosition().getX();
		rect2.y = pObject->getPosition().getY();
		rect2.w = pObject->getWidth();
		rect2.h = pObject->getHeight();
		// check collision with player bullet
		if (!pObject->getBullets()->empty())
		{
			for (int k = 0; k<pObject->getBullets()->size(); ++k)
			{
				Bullet* pBullet = (*pObject->getBullets())[k];
				if (pBullet->dying())
				{
					continue;
				}
				SDL_Rect rectBullet;				
				rectBullet.x = pBullet->getPosition().getX();
				rectBullet.y = pBullet->getPosition().getY();
				rectBullet.w = pBullet->getWidth();
				rectBullet.h = pBullet->getHeight();
				if (RectRect(&rect1, &rectBullet))
				{
					collision();
					pBullet->collision();
					break;
				}
			}
		}
		// check collision with object
		if (!m_bDying)
		{
			if (RectRect(&rect1, &rect2))
			{
				collision();
				pObject->collision();
				break;
			}
		}						
	}
}