#include "Player.h"
#include "Game.h"
#include "Bullet.h"
#include "Collision.h"
#include <iostream>
#include "SoundManager.h"

Player::~Player()
{
	ShooterObject::~ShooterObject();
}
Player::Player()
	:ShooterObject()
{
	// player specified
	m_width = 32;
	m_height = 32;
	m_startRow = 0;
	m_startFrame = 20;
	m_bulletPerShot = 1;
	m_bulletSpeed = 6;
	m_moveSpeed = 2;
	m_appearTime = 50;
	m_textureID = "graphics";
	m_health = 1;
	m_position.setX(220);
	m_position.setY(Game::Instance()->getGameHeight() - m_height);
}

void Player::update()
{
	ShooterObject::update();		
}
void Player::draw()
{
	ShooterObject::draw();	
}
void Player::collision()
{
	if (m_bInvulnerable)
	{
		return;
	}

	Game::Instance()->setPlayerLives(Game::Instance()->getPlayerLives()-1);
	ShooterObject::collision();
	if (Game::Instance()->getPlayerLives() == 0)
	{
		Game::Instance()->onGameOver();
	}

}
void Player::move()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput();
	// check for move capacity
	m_canMove = true;
	checkMovePosible();	
	checkObjectsCollision();
	checkMapCollision();
	//------------------------------
	
	if (m_canMove)
	{		
		m_position += m_velocity;		
		
	}
	
}
void Player::shot()
{
	if (checkShotPosible())
	{
		Bullet* pBullet = new PlayerBullet(this);
		m_bullets.push_back(pBullet);

		SoundManager::Instance()->playSound("shoot", 0);
	}
}

void Player::handleInput()
{
	if (!Game::Instance()->gameOver())
	{
		if (Game::Instance()->isKeyDown(SDL_SCANCODE_UP))
		{
			m_velocity.setY(-m_moveSpeed);
			m_direction = UP;		
		}
		else if(Game::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
		{
			m_velocity.setX(m_moveSpeed);
			m_direction = RIGHT;		
		}
		else if(Game::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
		{
			m_velocity.setY(m_moveSpeed);
			m_direction = DOWN;		
		}
		else if(Game::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
		{
			m_velocity.setX(-m_moveSpeed);
			m_direction = LEFT;		
		}
		// test
		if (Game::Instance()->isKeyDown(SDL_SCANCODE_DELETE))
		{
			collision();
		}
		static bool canShot = true;
		if (Game::Instance()->isKeyDown(SDL_SCANCODE_LCTRL) && canShot)
		{
			shot(); 
			canShot = false;
		}
		else if(!Game::Instance()->isKeyDown(SDL_SCANCODE_LCTRL))
		{
			canShot = true;
		}
	}	
}

void Player::resurrect()
{
	m_position.setX(220);
	m_position.setY(Game::Instance()->getGameHeight() - m_height);
	m_direction = UP;
	m_health = 1;
	m_textureID = "graphics";
	m_width = 32;
	m_height = 32;
	m_margin = 0;
	m_currentFrame = m_startFrame;
	m_currentRow = m_startRow;
	m_bAppearing = true;
}
void Player::doDyingAnimation()
{
	// explosion frame
	//m_currentFrame = 7 + int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));
	m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));
	if (m_dyingCounter == m_dyingTime) // dying finished
	{
		m_bDying = false;
		m_dyingCounter = 0;
		resurrect();
	}
	m_dyingCounter++;
}

void Player::checkMapCollision()
{

	//ShooterObject::checkMapCollision();
	std::vector<std::vector<int>>* tilesIDs = pLevel->getTileIDs();
	Vector2D newPosition = m_position + m_velocity;
	SDL_Rect rect1;
	rect1.x = newPosition.getX();
	rect1.y = newPosition.getY();
	rect1.w = m_width;
	rect1.h = m_height;

	if (rect1.x < 0){rect1.x = 0;}
	if (rect1.y < 0){rect1.y = 0;}
	if (rect1.x + rect1.w >= Game::Instance()->getGameWidth()){rect1.x = Game::Instance()->getGameWidth() - rect1.w - 1;}
	if (rect1.y + rect1.h >= Game::Instance()->getGameHeight()){rect1.y = Game::Instance()->getGameHeight() - rect1.h - 1;}
	// get tile id at rect1's area		
	if (m_direction == UP)
	{
		int r, c1, c2;
		r = (rect1.y)/16;
		if (rect1.x + rect1.w >= Game::Instance()->getGameWidth() - 1)
		{
			c1 = (rect1.x + 1)/16;
		}
		else
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
				
				//m_position.setX(16*(c2 - 1)); // for move easier
				m_position.setX(m_position.getX() - (int)m_position.getX() % 8);

				m_canMove = false;
				return;
			}
		}
	}
	else if (m_direction == RIGHT)
	{
		int c, r1, r2;
		c = (rect1.x + rect1.w)/16;
		if (rect1.y + rect1.h >= Game::Instance()->getGameHeight() - 1)
			r1 = (rect1.y + 1)/16;
		else
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
				//m_position.setY((r2-1)*16); // for move easier
				m_position.setY(m_position.getY() - (int)m_position.getY()%8);
				m_canMove = false;
				return;
			}
		}
	}
	else if (m_direction == DOWN)
	{
		int r, c1, c2;
		r = (rect1.y + rect1.h)/16;
		if (rect1.x + rect1.w >= Game::Instance()->getGameWidth() - 1)
			c1 = (rect1.x + 1)/16;		
		else
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
				//m_position.setX(16*(c2 - 1)); // for move easier
				m_position.setX(m_position.getX() - (int)m_position.getX() % 8);
				m_canMove = false;
				return;
			}
		}
	}
	else if (m_direction == LEFT)
	{
		int c, r1, r2;
		c = (rect1.x)/16;
		if (rect1.y + rect1.h >= Game::Instance()->getGameHeight() - 1)
			r1 = (rect1.y + 1)/16;
		else
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
				//m_position.setY((r2-1)*16);
				m_position.setY(m_position.getY() - (int)m_position.getY()%8);
				m_canMove = false;
				return;
			}
		}
	}

}

void Player::doAppearAnimation()
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
		m_bInvulnerable = true;
	}
	m_appearCounter++;
}