#ifndef GUARD_LEVEL_H
#define GUARD_LEVEL_H

#include <vector>
class ShooterObject;
class Level
{
public:
	~Level();
	Level():m_hasDead(true){}
	void update();
	void render();
	std::vector<ShooterObject*>* getShooterObjects(){return &m_shooterObjects;}
	std::vector<ShooterObject*>* getPlayerObjects(){return &m_playerObjects;}	
	std::vector<ShooterObject*>* getLevelObjects(){return &m_levelObjects;}
	std::vector<std::vector<int>>* getTileIDs() {return &m_tileIDs;}
private:
	// gameobjects
	std::vector<ShooterObject*> m_shooterObjects;
	std::vector<ShooterObject*> m_playerObjects;	
	std::vector<ShooterObject*> m_levelObjects;

	// map
	std::vector<std::vector<int> > m_tileIDs;

	bool m_hasDead;

};
#endif // !GUARD_LEVEL_H
