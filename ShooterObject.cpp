#include "ShooterObject.h"
#include "SDL.h"
#include "Bullet.h"
#include "Game.h"
#include "TextureManager.h"
#include "Collision.h"
#include "SoundManager.h"
ShooterObject::~ShooterObject()
{
	for (int i = 0; i<m_bullets.size(); ++i)
	{
		delete m_bullets[i];
	}
	m_bullets.clear();
}
ShooterObject::ShooterObject(): GameObject(),
	m_appearCounter(0), m_appearTime(50), m_bAppearing(true),
	m_direction(UP), m_moveSpeed(1), m_canMove(true),
	m_bulletPerShot(1), m_bulletSpeed(1),
	m_dyingCounter(0), m_dyingTime(40), m_bDying(false), m_bDead(false), 
	m_health(1), m_bInvulnerable(false), m_invulnerableCounter(0), m_invulnerableTime(400),
	m_invulnerableFrame(7)
{
}

void ShooterObject::update()
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
			// invulnerable
			if (m_bInvulnerable)
			{
				doInvulnerableAnimation();
			}
			
			//---------------------
			move();		
			if (m_velocity.getX() != 0 || m_velocity.getY() != 0)
			{
				// move animation
				m_currentRow = m_currentRow == m_startRow ? m_currentRow + 1 : m_startRow;
				m_currentFrame = m_startFrame + m_direction;
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
		//----end update bullets---------------------------		

	}
}
void ShooterObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), m_margin);
	// draw bullets
	if (!m_bullets.empty())
	{
		for (int i = 0; i<m_bullets.size(); ++i)
		{
			m_bullets[i]->draw();
		}
	}
	// draw invulnerable if need
	if (m_bInvulnerable)
	{
		TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(),
			m_width, m_height, 9, m_invulnerableFrame, Game::Instance()->getRenderer(), 4);
	}
}
void ShooterObject::collision()
{
	--m_health;
	
	if (m_health == 0)
	{
		SoundManager::Instance()->playSound("tankexplosion", 0);
		m_textureID = "tankexplosion";
		m_currentRow = 0;
		m_currentFrame = 0;
		m_numFrames = 7;
		m_width = 40;
		m_height = 40;
		// set every bullets to be disappear
		for (int i = 0; i<m_bullets.size(); ++i)
		{
			m_bullets[i]->collision();
		}
		m_bDying = true;
	}
	else
	{
		SoundManager::Instance()->playSound("steelhit", 0);
	}
}
void ShooterObject::move()
{
	
}
void ShooterObject::shot()
{

}

void ShooterObject::doDyingAnimation()
{
	// explosion frame
	//m_currentFrame = 7 + int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));
	m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));
	if (m_dyingCounter == m_dyingTime) // dying finished
	{
		m_dyingCounter = 0;
		m_bDying = false;
		m_bDead = true;		
	}
	m_dyingCounter++;
}
void ShooterObject::doAppearAnimation()
{
	// appear frame
	m_currentFrame = 7 + int(((SDL_GetTicks() / (1000/ 10)) % 10));
	m_currentRow = 10;
	m_margin = 4;
	if (m_appearCounter == m_appearTime) // appear finished
	{
		m_bAppearing = false;
		m_currentRow = m_startRow;
		m_currentFrame = m_startFrame;
		m_margin = 0;
		m_appearCounter = 0;
	}
	m_appearCounter++;
}
void ShooterObject::checkMovePosible()
{
	Vector2D newPosition = m_position + m_velocity;
	
	// check bound	
	if (newPosition.getX() < 0)
	{
		//m_velocity.setX(m_position.getX());
		m_position.setX(0);
		m_canMove = false;
		return;
	}
	if (newPosition.getY() < 0)
	{
		m_position.setY(0);
		m_canMove = false;
		return;
	}
	if (newPosition.getX() + m_width>Game::Instance()->getGameWidth())
	{
		m_position.setX(Game::Instance()->getGameWidth() - m_width);
		m_canMove = false;
		return;
	}
	if (newPosition.getY() + m_height > Game::Instance()->getGameHeight())
	{
		m_position.setY(Game::Instance()->getGameHeight() - m_height);
		m_canMove = false;
		return;
	}
	//----------------------------------------------------------------------------
	//checkObjectsCollision();
}
bool ShooterObject::checkShotPosible()
{
	return m_bullets.size() < m_bulletPerShot;
}

void ShooterObject::checkObjectsCollision() // for move capacity
{
	Vector2D newPosition = m_position + m_velocity;
	SDL_Rect rect;
	rect.x = m_position.getX();
	rect.y = m_position.getY();
	rect.w = m_width;
	rect.h = m_height;

	SDL_Rect rect1;
	rect1.x = newPosition.getX();
	rect1.y = newPosition.getY();
	rect1.w = m_width;
	rect1.h = m_height;
	
	for (int i = 0; i<pLevel->getShooterObjects()->size(); ++i)
	{
		ShooterObject* pObject = (*pLevel->getShooterObjects())[i];
		if (pObject->dying() || pObject == this)
		{
			continue;
		}
		SDL_Rect rect2;
		rect2.x = pObject->getPosition().getX();
		rect2.y = pObject->getPosition().getY();
		rect2.w = pObject->getWidth();
		rect2.h = pObject->getHeight();
		
		if (RectRect(&rect1, &rect2))
		{						
			m_canMove = false;				
			
			if (RectOnRect(&rect, &rect2))
			{
				pObject->collision();					
			}	
			return;
		}
	}
}

void ShooterObject::checkMapCollision()
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
			if ((*tilesIDs)[r][i] == 0 ||(*tilesIDs)[r][i] == 10 || (*tilesIDs)[r][i] == 11 || (*tilesIDs)[r][i] == 14 ||(*tilesIDs)[r][i] == 15)
			{
				continue;
			}
			if ((*tilesIDs)[r][i] != 0) // collide with tile map
			{
				m_position.setY((r+1)*16 );								
			
				m_canMove = false;
				return;
			}
		}
	}
	else if (m_direction == RIGHT)
	{
		int c, r1, r2;
		c = (rect1.x + rect1.w)/16;
		r1 = rect1.y/16;
		r2 = (rect1.y + rect1.h - 1)/16;
		for (int i = r1; i <= r2; ++i)
		{
			// no collidable tile
			if ((*tilesIDs)[i][c] == 0 ||(*tilesIDs)[i][c] == 10 || (*tilesIDs)[i][c] == 11 || (*tilesIDs)[i][c] == 14 ||(*tilesIDs)[i][c] == 15)
			{
				continue;
			}
			if ((*tilesIDs)[i][c] != 0) // collide with tile map
			{
				m_position.setX((c)*16 - m_width);				
				m_canMove = false;
				return;
			}
		}
	}
	else if (m_direction == DOWN)
	{
		int r, c1, c2;
		r = (rect1.y + rect1.h)/16;
		c1 = (rect1.x)/16;
		c2 = (rect1.x + rect1.w - 1)/16;
		for (int i = c1; i<=c2; ++i)
		{
			// no collidable tile
			if ((*tilesIDs)[r][i] == 0 ||(*tilesIDs)[r][i] == 10 || (*tilesIDs)[r][i] == 11 || (*tilesIDs)[r][i] == 14 ||(*tilesIDs)[r][i] == 15)
			{
				continue;
			}
			if ((*tilesIDs)[r][i] != 0)
			{
				m_position.setY((r)*16 - m_height);				
				m_canMove = false;
				return;
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
			if ((*tilesIDs)[i][c] == 0 ||(*tilesIDs)[i][c] == 10 || (*tilesIDs)[i][c] == 11 || (*tilesIDs)[i][c] == 14 ||(*tilesIDs)[i][c] == 15)
			{
				continue;
			}
			if ((*tilesIDs)[i][c] != 0)
			{
				m_position.setX((c + 1)*16);				
				m_canMove = false;
				return;
			}
		}
	}

}

void ShooterObject::drawAt(int x, int y)
{
	TextureManager::Instance()->drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
}

void ShooterObject::doInvulnerableAnimation()
{
	
	m_invulnerableFrame = m_invulnerableFrame == 7?8:7;
	
	
	if (m_invulnerableCounter == m_invulnerableTime)
	{
		m_invulnerableCounter = 0;
		m_bInvulnerable = false;
	}
	m_invulnerableCounter++;
}