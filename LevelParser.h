#ifndef GUARD_LEVELPARSER_H
#define GUARD_LEVELPARSER_H
#include "Level.h"
class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);
private:
	void parseMap(Level* pLevel);
	void createShooterObjects(Level* pLevel);
	std::vector<ShooterObject*> m_ShooterObjects;
};
#endif // !GUARD_LEVELPARSER_H
