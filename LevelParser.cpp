#include "LevelParser.h"
#include "Player.h"
#include "StupidTank.h"
#include "base64.h"
#include "zlib.h"
#include "King.h"
#include "FastTank.h"
#include "Game.h"
#include "HeavyTank.h"
#include "tinyxml.h"
#include "GameOverState.h"
Level* LevelParser::parseLevel(const char* levelFile)
{
	Level *pLevel = new Level();
	TiXmlDocument levelDoc;
	levelDoc.LoadFile(levelFile);
	TiXmlElement* rootNode = levelDoc.RootElement();
	std::string encripytString;
	TiXmlElement* pDataNode;
	for (TiXmlElement* e = rootNode->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int currentLevel;
		e->Attribute("id", &currentLevel);
		if (currentLevel == Game::Instance()->getCurrentLevel())
		{
			pDataNode = e->FirstChildElement();
			break;
		}
	}
	// can not find any level-> the user clear all level. reach gameover state
	if (!pDataNode)
	{
		Game::Instance()->getGameStateMachine()->changeState(new GameOverState());
		return;
	}

	std::string decodedIDs;
	for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	int width = 40, height = 30;
	// uncompress zlib compression
	uLongf sizeofids = width * height * sizeof(int);
	std::vector<int> ids(width * height);
	uncompress((Bytef*)&ids[0], &sizeofids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(width);

	for(int j = 0; j < height; j++)
	{
		pLevel->getTileIDs()->push_back(layerRow);
	}

	for(int rows = 0; rows < height; rows++)
	{
		for(int cols = 0; cols < width; cols++)
		{
			(*pLevel->getTileIDs())[rows][cols] = ids[rows * width + cols];
		}
	}
	
	// setup player
	ShooterObject* pPlayer = new Player();	
	ShooterObject* pKing = new King();
	pPlayer->setLevel(pLevel);
	pKing->setLevel(pLevel);
	
	pLevel->getPlayerObjects()->push_back(pPlayer);
	pLevel->getPlayerObjects()->push_back(pKing);
	pLevel->getShooterObjects()->push_back(pPlayer);
	pLevel->getShooterObjects()->push_back(pKing);
	//-----------------------------

	createShooterObjects(pLevel);	

	return pLevel;
}

void LevelParser::createShooterObjects(Level* pLevel)
{
	static int positionY[3] = {0, (Game::Instance()->getGameWidth() - 32)/2, Game::Instance()->getGameWidth() - 32};
	static int currentPosition = 0;

	// create random enemy objects
	for (int i = 0; i<20; ++i)
	{
		ShooterObject* pObject;

		int baseNumber = MAX_LEVEL - Game::Instance()->getCurrentLevel();
		int randomNumber = rand()%baseNumber;
		if (randomNumber == 0)
		{
			pObject = new FastTank(1 + rand()%3);
		}
		else if(randomNumber >= 1 && randomNumber <= 5)
		{
			pObject = new HeavyTank(1 + rand()%3);
		}
		else
		{
			pObject = new StupidTank(1 + rand()%3);
		}
		
		pObject->setLevel(pLevel);
		pObject->getPosition().setY(0);
		pObject->getPosition().setX(positionY[currentPosition++]);
		pLevel->getLevelObjects()->push_back(pObject);		
		currentPosition %= 3;
	}

	// init playing object
	for (int i = 0; i<3; ++i)
	{
		pLevel->getShooterObjects()->push_back(pLevel->getLevelObjects()->back());
		pLevel->getLevelObjects()->pop_back();
	}
}