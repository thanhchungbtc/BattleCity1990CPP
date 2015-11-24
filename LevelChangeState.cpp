#include "LevelChangeState.h"
#include "PlayState.h"
#include "Game.h"
LevelChangeState::~LevelChangeState()
{

}
void LevelChangeState::onEnter()
{

}
void LevelChangeState::onExit()
{

}
void LevelChangeState::update()
{
	static int count = 0;
	if (count > 120) // 2s
	{
		Game::Instance()->getGameStateMachine()->changeState(new PlayState());
	}
	else
	{
		count++;
	}
	
}
void LevelChangeState::render()
{

}

