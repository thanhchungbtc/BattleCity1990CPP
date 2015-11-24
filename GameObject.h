#ifndef GUARD_GAMEOBJECT_H
#define GUARD_GAMEOBJECT_H
#include "Vector2D.h"
#include "LoaderParams.h"
class GameObject
{
public:
	~GameObject(){}
	
	virtual void load(const LoaderParams* pParams){
		m_position.setX(pParams->getX());
		m_position.setY(pParams->getY());
		m_width = pParams->getWidth();
		m_height = pParams->getHeight();

		m_numFrames = pParams->getNumFrames();
		m_startFrame = pParams->getStartFrame();
		m_startRow = pParams->getStartRow();

		m_currentFrame = m_startFrame;
		m_currentRow = m_startRow;
		m_textureID = pParams->getTextureID();
	
	}

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;
	virtual std::string type() = 0;
	int getWidth() const {return m_width;}
	int getHeight()const {return m_height;}
	Vector2D& getPosition() {return m_position;}
	
protected:
	GameObject():m_position(0, 0), m_velocity(0, 0), m_width(0), m_height(0),
		m_numFrames(0), m_startFrame(0), m_startRow(0),
		m_currentFrame(0), m_currentRow(0), m_textureID("graphics"), m_margin(0)
	{}

	Vector2D m_position;
	Vector2D m_velocity;
	int m_width;
	int m_height;

	int m_numFrames;
	int m_startFrame;
	int m_startRow;
	int m_currentFrame;
	int m_currentRow;
	int m_margin;
	std::string m_textureID;
};
#endif