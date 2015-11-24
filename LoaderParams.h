#ifndef GUARD_LOADERPARAMS_H
#define GUARD_LOADERPARAMS_H
#include <string>
class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, int startFrame,
		int startRow, int numFrames, std::string textureID, int health = 1):
	m_x(x), m_y(y), m_width(width), m_height(height), m_startFrame(startFrame),
		m_startRow(startRow), m_numFrames(numFrames), m_textureID(textureID), m_health(health)
	{

	}
	int getX() const {return m_x;}
	int getY() const {return m_y;}
	int getWidth() const {return m_width;}
	int getHeight() const {return m_height;}

	int getStartFrame() const {return m_startFrame;}
	int getStartRow() const {return m_startRow;}
	int getNumFrames() const {return m_numFrames;}

	int getHealth() const {return m_health;}
	std::string getTextureID() const {return m_textureID;}
private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;
	
	int m_startFrame;
	int m_startRow;
	int m_numFrames;
	std::string m_textureID;
	int m_health;
};
#endif