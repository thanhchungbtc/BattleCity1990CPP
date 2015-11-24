#ifndef GUARD_KING_H
#define GUARD_KING_H
#include "ShooterObject.h"
#include "Game.h"
class King:public ShooterObject
{
public:
	~King(){}
	King():ShooterObject(){
		m_startFrame = m_currentFrame = 28;
		m_startRow = m_currentRow = 2;
		m_width = 32;
		m_height = 32;
		m_bDead = false;
		m_position.setX((Game::Instance()->getGameWidth() - m_width)/2);
		m_position.setY(Game::Instance()->getGameHeight() - m_height);
	}


	virtual void update(){
		ShooterObject::update();
	}
	virtual void draw(){
		ShooterObject::draw();
	}
	virtual void collision(){
		
		if (!Game::Instance()->gameOver())
		{
			m_bDead = true;
			m_currentFrame = 29;
			Game::Instance()->onGameOver();
		}		
	}
	virtual void move(){}
	virtual void shot(){}


	virtual std::string type(){return "King";}
private:

};
#endif