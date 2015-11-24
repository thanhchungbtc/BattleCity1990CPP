#ifndef GUARD_MAINMENUSTATE_H
#define GUARD_MAINMENUSTATE_H

#include "GameState.h"
#include "GameObject.h"
#include "MenuBox.h"
#include <vector>
#include <string>

class MainMenuState: public GameState
{
public:
	
	virtual ~MainMenuState();
	virtual void onEnter();
	virtual void onExit();
	virtual void update();
	virtual void render();
	virtual std::string getStateID() const {return "MAINMENU";}
private:
	std::vector<GameObject*> m_gameObjects;
	
	//callback functions
	static void s_menuToPlay();
	static void s_menuToQuit();
};
#endif