#include "MenuBox.h"
#include "Game.h"
#include "TextureManager.h"
void MenuBox::load(const LoaderParams* pParams)
{
	GameObject::load(pParams);
	m_textureID = pParams->getTextureID();
	m_selectedValue = 0;
}
void MenuBox::update()
{
	if (Game::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{		
		m_keyPressCounter++;
		if (m_keyPressCounter > m_keyPressSpeed)
		{
			if (m_selectedValue < 1)
			{
				m_selectedValue++;
				m_keyPressCounter = 0;
			}			
		}		
	}
	else if (Game::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_keyPressCounter++;
		if (m_keyPressCounter > m_keyPressSpeed)
		{
			if (m_selectedValue > 0)
			{
				m_selectedValue--;
				m_keyPressCounter = 0;
			}			
		}			
	}
	else if(Game::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{	
		if (m_selectedValue < m_callbacks.size())
		{
			m_callbacks[m_selectedValue]();
		}		
	}
	else 
	{
		m_keyPressCounter = m_keyPressSpeed;
	}

}
void MenuBox::draw()
{	
	TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY() + m_selectedValue*30 , 
		m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
}
void MenuBox::clean()
{

}
