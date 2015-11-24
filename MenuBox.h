#ifndef GUARD_MENUBOX_H
#define GUARD_MENUBOX_H
#include "GameObject.h"
#include <vector>
typedef void(*CallBack)();
class MenuBox: public GameObject
{

public:
	
	MenuBox():m_keyPressCounter(0),
	m_keyPressSpeed(8){}
	virtual void load(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();
	virtual std::string type(){return "MenuBox";}
	std::vector<CallBack>* getCallback() {return &m_callbacks;}

	void setSelectedValue(int selectedValue){m_selectedValue = selectedValue;}
	int selectedValue() const {return m_selectedValue;}


private:
	// adjust keypress speed
	int m_keyPressCounter;
	int m_keyPressSpeed;
	// ---------------------

	int m_selectedValue;
	
	// handle callback base on selected value
	
	std::vector<CallBack> m_callbacks;	
};

#endif