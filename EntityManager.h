#pragma once
#ifndef __ENTITYMANAGER_H_INCLUDED__
#define __ENTITYMANAGER_H_INCLUDED__
#include "Trap.h"
#include "Lier.h"
#include "Castle.h"
#include "Tower.h"
#include "System.h"
#include "level.h"
#include "Score.h"
#include <iostream>
#include <SFML/Graphics.hpp>


const int WIDTH = 64,
HEIGHT = 64;
class GameState;
class Trap;
class Lier;
class Castle;
class Tower;
enum TowerType
{
	SimpleTower = 1, // ID- 249,250
	MagicTowerF,
	MagicTowerP,
	MagicTowerM
};

/*!
\brief Structure consisting of constant values for the cost of towers
*/
struct TableCostTower
{
	const enum SimpleTowerCost
	{
		S_TOWER_1 = 110,
		S_TOWER_2 = 150
	};
	const enum MagicTowerCost
	{
		M_TOWER_1_F = 150,
		M_TOWER_2_F = 170,
		M_TOWER_1_P = 130,
		M_TOWER_2_P = 150,
		M_TOWER_1_M = 120,
		M_TOWER_2_M = 150
	};
	const int costKillEnemy; //Возможно поменятеся
	TableCostTower() :costKillEnemy(20) { ; }
	const int getInfo(TowerType type, int)const;
};

/*!
\brief The main game class that provides control over all entities*/
class EntityManager
{
public:
	EntityManager(Level&);
	bool setParameters(Level lvl);

	/*!
	\brief A main method of the class that handles the time tick
	\param
	\return bool error  -Ideally it should fix errors. But so far the breakdowns are not fixed
	\todo Think about "return"
	*/
	bool update(sf::Time frameTime);
	void draw(sf::RenderWindow* window);
	void addTower(Tower& tower);
	int getGold()const;
	int setGold(int);
	void addGold(int);
	bool checkGold(TowerType, int);
	bool lvlUP(sf::Vector2i vec);
	void addSystem(System*, int);
	std::vector<Lier*> getLiers();
	std::vector<Castle*> getCastles();
	bool removeTower(sf::Vector2i vec);
	std::vector<Trap*> getTraps();
	std::vector<Tower*> getTowers();
	void addTrap(Trap& trap);
	bool removeTrap(sf::Vector2i vec);
	void setGameState(GameState* gS);

	/*!
\brief Class method required for changing a dynamic array of entities

The bottom line: Loads all of the active elements in the array
*/
	void applyChanges();
private:
	void addSystems();
	
	void addStates();
	int findObject(sf::Vector2i vec, bool trap = false);
	void addState(Entity* state);
	GameState* gState;
	TableCostTower costTable;
	Score score;
	std::vector <System*> systems;
	std::vector<Entity*> _entities;
	std::vector<Trap> traps;
	std::vector<Lier> liers;
	std::vector<Castle> castles;
	std::vector<Tower> towers;
};

template< typename TContainer >
static bool EraseFromUnorderedByIndex(TContainer& inContainer, size_t inIndex)
{
	if (inIndex < inContainer.size())
	{
		if (inIndex != inContainer.size() - 1)
			inContainer[inIndex] = inContainer.back();
		inContainer.pop_back();
		return true;
	}
	return false;
}
#endif