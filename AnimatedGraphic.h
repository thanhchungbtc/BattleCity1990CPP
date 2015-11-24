#ifndef GUARD_AnimatedGraphic_H
#define GUARD_AnimatedGraphic_H
#include "ShooterObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "MainMenuState.h"
class AnimatedGraphic:public ShooterObject
{
public:
	~AnimatedGraphic(){}
	AnimatedGraphic():ShooterObject()		
	{		
		m_width = 200;
		m_height = 32;
		m_bDead = false;
		m_position.setX(300);
		m_position.setY(400);
		m_destPosition.setX(280);
		m_destPosition.setY(200);
		m_textureID = "gameover";
		m_velocity.setY(-2);
		m_velocity.setX(0);
	}


	virtual void update(){
		
		if (m_position.getY() > m_destPosition.getY())
		{
			m_position += m_velocity;
		}
		else
		{
			Game::Instance()->getGameStateMachine()->changeState(new MainMenuState());
		}
	}
	virtual void draw(){
		TextureManager::Instance()->drawImage(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, Game::Instance()->getRenderer());
	}
	virtual void collision(){

	}
	virtual void move(){}
	virtual void shot(){}


	virtual std::string type(){return "GameOver";}
private:
	Vector2D m_destPosition;
};
#endif