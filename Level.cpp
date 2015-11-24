#include "Level.h"
#include "ShooterObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "Collision.h"
#include "PlayState.h"
#include "LevelChangeState.h"

void Level::update()
{
	if (!m_shooterObjects.empty())
	{		
		for (std::vector<ShooterObject*>::iterator it= m_shooterObjects.begin(); it != m_shooterObjects.end();)
		{
			if ((*it)->dead() && (*it)->type() != std::string("Player") && (*it)->type() != std::string("King"))
			{
				delete (*it);
				it = m_shooterObjects.erase(it);		
				m_hasDead = true;
			}
			else
			{		
				(*it)->update();
				++it;
			}
		}			
		// an enemy has dead, push new enemy to the updating objects
		if (m_hasDead)
		{
			if (!m_levelObjects.empty())
			{
				// check whether this position is valid to appear
				ShooterObject* pObject = m_levelObjects.back();
				SDL_Rect rect1;
				rect1.x = pObject->getPosition().getX();
				rect1.y = pObject->getPosition().getY();
				rect1.w = pObject->getWidth();
				rect1.h = pObject->getHeight();
				
				for (int i = 0; i<m_shooterObjects.size(); ++i)
				{
					if (m_shooterObjects[i] == pObject|| m_shooterObjects[i]->dying())
					{
						continue;
					}
					SDL_Rect rect2;
					rect2.x = m_shooterObjects[i]->getPosition().getX();
					rect2.y = m_shooterObjects[i]->getPosition().getY();
					rect2.w = m_shooterObjects[i]->getWidth();
					rect2.h = m_shooterObjects[i]->getHeight();
					if (RectRect(&rect1, &rect2))
					{
						return;
					}
				}
				// then push to the updating objects
				m_shooterObjects.push_back(m_levelObjects.back());
				m_levelObjects.pop_back();
				m_hasDead = false;
			}
			else
			{				
				if (m_shooterObjects.size() == 2) // shooterobjects includes only king and player
				{
					// level clear
					Game::Instance()->getGameStateMachine()->changeState(new LevelChangeState());
				}
			}
		}
	}
}
void Level::render()
{
	// draw objects
	if (!m_shooterObjects.empty())
	{
		for (int i = 0; i<m_shooterObjects.size(); ++i)
		{
			m_shooterObjects[i]->draw();
		}
	}
	// draw map

	int width = 40, height = 30;
	for (int i = 0; i<height; ++i)
	{
		for (int j = 0; j<width; ++j)
		{
			int id = m_tileIDs[i][j];
			if (id == 0)
			{
				continue;
			}
			id--;
			TextureManager::Instance()->drawTile("map", 0, 0, j*16, i*16, 16, 16, id/4, id%4, Game::Instance()->getRenderer());
		}
	}
}
Level::~Level()
{
	// need to clear following objects
	/*std::vector<ShooterObject*> m_shooterObjects;
	std::vector<ShooterObject*> m_playerObjects;	
	std::vector<ShooterObject*> m_levelObjects;*/
	
}