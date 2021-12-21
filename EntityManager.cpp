#include "EntityManager.h"
#include "GameState.h"
#include "Tile.h"
#include "Grid.h"
#include <math.h>
#include <string>
#include "DamageSystem.h"
#include "MoveSystem.h"
#include "GameState.h"

const int TableCostTower::getInfo(TowerType type, int level)const
{
	if (type == TowerType::SimpleTower)
	{
		if (level == 1)
		{
			const int cost = SimpleTowerCost::S_TOWER_1;
			return cost;
		}
		else
		{
			const int cost = SimpleTowerCost::S_TOWER_2;
			return cost;
		}
	}
	else
	{
		if (level == 1)
		{
			if (type == TowerType::MagicTowerF)
			{
				return MagicTowerCost::M_TOWER_1_F;
			}
			if (type == TowerType::MagicTowerP)
			{
				return MagicTowerCost::M_TOWER_1_P;
			}
			if (type == TowerType::MagicTowerM)
			{
				return MagicTowerCost::M_TOWER_1_M;
			}
		}
		else
		{
			if (type == TowerType::MagicTowerF)
			{
				return MagicTowerCost::M_TOWER_2_F;
			}
			if (type == TowerType::MagicTowerP)
			{
				return MagicTowerCost::M_TOWER_2_P;
			}
			if (type == TowerType::MagicTowerM)
			{
				return MagicTowerCost::M_TOWER_2_M;
			}
		}
	}
}

void EntityManager::setGameState(GameState* gS)
{
	this->gState = gS;
}
EntityManager::EntityManager(Level& lvl) :score(), costTable()
{
	std::vector<std::vector<Tile>> tileMap = lvl.getGrid().getTiles();
	int size_y = tileMap.size();
	int size_x = tileMap[0].size();
	std::map<std::string, std::list <sf::Vector2i>>* lierRoads = lvl.getRoad();
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			//road- 1, castle -2, lier -3, tower -4
			if (tileMap[i][j].getState() == 2)
			{
				Castle  castle(&tileMap[i][j]);
				this->castles.push_back(castle);
			}
			if (tileMap[i][j].getState() == 3)
			{
				for (int k = 1; k <= lierRoads->size(); k++)
				{
					std::string key = "solid" + std::to_string(k);
					std::map<std::string, std::list <sf::Vector2i>>::iterator it_m = lierRoads->find(key);
					std::list <sf::Vector2i> tmp = (*it_m).second; 
					std::list <sf::Vector2i>::iterator it = tmp.begin();
					if ((((*it).x) == (int)tileMap[i][j].getSprite().getPosition().x) && (((*it).y) == (int)tileMap[i][j].getSprite().getPosition().y))
					{
						Lier lier(&tileMap[i][j], tmp);
						this->liers.push_back(lier);

						break;
					}
				}
			}
		}
	}
	addStates();
}
void EntityManager::addGold(int gold)
{

	int curr = getGold();
	curr += gold;
	setGold(curr);
}
void EntityManager::addStates()
{
	//Liers
	int size = liers.size();
	for (int i = 0; i < size; i++)
	{
		addState(&liers[i]);
	}
	//Castles
	size = castles.size();
	for (int i = 0; i < size; i++)
	{
		addState(&castles[i]);
	}
}

std::vector<Lier*> EntityManager::getLiers()
{
	std::vector<Lier*> tmp;
	int size = liers.size();
	for (int i = 0; i < size; i++)
	{
		tmp.push_back(&liers[i]);
	}
	return tmp;
}
std::vector<Castle*> EntityManager::getCastles()
{
	std::vector<Castle*> tmp;
	int size = castles.size();
	for (int i = 0; i < size; i++)
	{
		tmp.push_back(&castles[i]);
	}
	return tmp;
}
std::vector<Trap*> EntityManager::getTraps()
{
	std::vector<Trap*> tmp;
	int size = traps.size();
	for (int i = 0; i < size; i++)
	{
		tmp.push_back(&traps[i]);
	}
	return tmp;
}
std::vector<Tower*> EntityManager::getTowers()
{
	std::vector<Tower*> tmp;
	int size = towers.size();
	for (int i = 0; i < size; i++)
	{
		tmp.push_back(&towers[i]);
	}
	return tmp;
}

void  EntityManager::addSystem(System* sys, int id_s)
{
	sys->setManager(this);
	systems.push_back(sys);
}
void EntityManager::addSystems()
{
	Enemy f;
	f.gethp();
}
bool EntityManager::setParameters(Level lvl)
{
	//	lvl.getGrid().getTile()
	std::vector<std::vector<Tile>> tileMap = lvl.getGrid().getTiles();
	int size_y = tileMap.size();
	int size_x = tileMap[0].size();
	std::map<std::string, std::list <sf::Vector2i>>* lierRoads = lvl.getRoad();
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			//road- 1, castle -2, lier -3, tower -4
			if (tileMap[i][j].getState() == 2)
			{
				Castle  castle(&tileMap[i][j]);
				this->castles.push_back(castle);
				addState(&this->castles.back());
			}
			if (tileMap[i][j].getState() == 3)
			{
				for (int k = 1; k <= lierRoads->size(); k++)
				{
					std::string key = "solid" + std::to_string(k);
					std::map<std::string, std::list <sf::Vector2i>>::iterator it_m = lierRoads->find(key);
					std::list <sf::Vector2i> tmp = (*it_m).second;
					std::list <sf::Vector2i>::iterator it = tmp.begin();
					if ((((*it).x - 32) == (int)tileMap[i][j].getSprite().getPosition().x) && (((*it).y - 32) == (int)tileMap[i][j].getSprite().getPosition().y))
					{
						Lier lier(&tileMap[i][j], tmp);
						this->liers.push_back(lier);
						addState(&this->liers.back());
						break;
					}
				}
			}
		}
	}
	return true;
}
bool EntityManager::update(sf::Time frameTime)
{

	for (auto& system : systems)
	{
		//system->setManager(this);
		system->update(frameTime);
	}


	int size = _entities.size();
	for (int i = 0; i < size; i++)
		_entities[i]->update(frameTime);
	return true;
}
void EntityManager::addState(Entity* enty)
{
	this->_entities.push_back(enty);
}
void EntityManager::draw(sf::RenderWindow* window)
{
	score.draw(window);
	std::vector<Tower>::iterator it = towers.begin();
	for (it; it != towers.end(); ++it)
	{

		(*it).draw(window);
	}

	std::vector<Castle>::iterator it1 = castles.begin();
	for (it1; it1 != castles.end(); ++it1)
	{
		(*it1).draw(window);
	}
	std::vector<Lier>::iterator it2 = liers.begin();
	for (it2; it2 != liers.end(); ++it2)
	{
		(*it2).draw(window);
	}

	auto it3 = traps.begin();
	for (it3; it3 != traps.end(); ++it3)
	{
		(*it3).draw(window);
	}
}

int EntityManager::getGold()const
{
	return score.getGold();
}
void EntityManager::addTower(Tower& tower)
{
	int curr = this->getGold();
	curr -= costTable.getInfo(tower.getTowerType(), 1);
	if (score.setGold(curr))
	{
		this->towers.push_back(tower);
		for (int i = 0; i < towers.size(); i++)
		{
			towers[i].setTarget(nullptr);
		}
		//_entities.push_back(&towers.back());
		applyChanges();
	}
	else
	{
		std::cout << " YOU HAVE NOT MONEY" << std::endl;
	}
}
void EntityManager::addTrap(Trap& trap)
{
	int curr = getGold();
	curr -= costTable.getInfo(TowerType::SimpleTower, 1);//cost trap equal cost simple tower 1 level
	if (score.setGold(curr))
	{
		this->traps.push_back(trap);
	}
	else
	{
		std::cout << " YOU HAVE NOT MONEY" << std::endl;
	}
}
bool EntityManager::removeTrap(sf::Vector2i vec)
{
	int number = findObject(vec,true);
	gState->getLevel()->setObject(vec, -2);
	EraseFromUnorderedByIndex(traps, number);
	applyChanges();
	return true;
}
void EntityManager::applyChanges()
{
	int size_castles = castles.size();
	int size_liers = liers.size();
	int size_towers = towers.size();
	int size_traps = traps.size();

	_entities.clear();
	for (int i = 0; i < size_towers; i++)
	{
		_entities.push_back(&towers[i]);
	}
	for (int i = 0; i < size_castles; i++)
	{
		_entities.push_back(&castles[i]);
	}
	for (int i = 0; i < size_liers; i++)
	{
		_entities.push_back(&liers[i]);
	}
	for (int i = 0; i < size_traps; i++)
	{
		if (traps[i].getMode())
		{
			_entities.push_back(&traps[i]);
		}
	}
}

int EntityManager::setGold(int gold)
{
	if (score.setGold(gold))
		return 1;
	return 0;
}
bool EntityManager::checkGold(TowerType type, int level)
{
	const int cost = costTable.getInfo(type, level);
	if (score.getGold() - cost > 0)
		return false;
	std::cout << " YOU HAVE NOT MONEY" << std::endl;
	return true;
}
bool EntityManager::lvlUP(sf::Vector2i vec)
{
	int number = findObject(vec);
	if (number == -1)
	{
		std::cout << "not find this tower" << std::endl;
		return false;
	}

	int curr = this->getGold();
	curr -= costTable.getInfo(towers[number].getTowerType(), 2);
	if (score.setGold(curr))
		towers[number].lvlUP();
	else
	{
		std::cout << " YOU HAVE NOT MONEY" << std::endl;
	}
	return true;

}

int EntityManager::findObject(sf::Vector2i vec, bool trap)
{
	const int hight = 64, wight = 64;
	if (trap)
	{
		int size = traps.size();
		for (int i = 0; i < size; i++)
		{
			std::cout << vec.x / hight << "  " << vec.y / wight << "|" << (int)traps[i].getTile()->getSprite().getPosition().x / hight << " " << (int)traps[i].getTile()->getSprite().getPosition().y / wight;
			if (((vec.x / hight) == (int)traps[i].getTile()->getSprite().getPosition().x / hight) && ((vec.y / wight) == (int)traps[i].getTile()->getSprite().getPosition().y / wight))
				return i;
		}
	}
	else
	{
		int size = towers.size();

		for (int i = 0; i < size; i++)
		{
			std::cout << vec.x / hight << "  " << vec.y / wight << "|" << (int)towers[i].getTile()->getSprite().getPosition().x / hight << " " << (int)towers[i].getTile()->getSprite().getPosition().y / wight;
			if (((vec.x / hight) == (int)towers[i].getTile()->getSprite().getPosition().x / hight) && ((vec.y / wight) == (int)towers[i].getTile()->getSprite().getPosition().y / wight))
				return i;
		}
	}
	return -1;
}

bool EntityManager::removeTower(sf::Vector2i vec)
{
	int number = findObject(vec);
	if (number == -1)
	{
		std::cout << "not find this tower" << std::endl;
		return false;
	}
	int cost = costTable.getInfo(towers[number].getTowerType(), towers[number].getLevel());
	cost /= 2;
	score.setGold(score.getGold() + cost);
	//dellete
	EraseFromUnorderedByIndex(towers, number);
	applyChanges();
}