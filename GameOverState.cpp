#include "GameOverState.h"
#include "PlayState.h"
#include "Game.h"
GameOverState::~GameOverState()
{

}
void GameOverState::onEnter()
{

}
void GameOverState::onExit()
{

}
void GameOverState::update()
{
	Game::Instance()->getGameStateMachine()->changeState(new PlayState());
}
void GameOverState::render()
{

}
