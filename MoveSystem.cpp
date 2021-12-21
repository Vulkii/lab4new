#include "MoveSystem.h"
#include "EntityManager.h"
#include "QuickSort.h"
#include <list>
#include <ctime>
#include <cstdlib>

Targets::Targets(std::vector<Enemy*> enemies, std::vector<float>distance, std::vector<float> distance2)
{
	targets = enemies;
	distances_t = distance;
	distances_c = distance2;
}
void MoveSystem::update(sf::Time)
{
	towers = this->_manager->getTowers();
	traps = this->_manager->getTraps();
	int size_t = towers.size();
	Enemy* goalTarget;
	for (int i = 0; i < size_t; i++)
	{

		Targets targets;
		// Step 1-  check position enemies
		int size_l = liers.size();
		for (int j = 0; j < size_l; j++)
		{
			Targets partTargets;
			partTargets = detectTargets(liers[j], towers[i]);
			if (!partTargets.targets.empty())
			{
				targets.targets.insert(targets.targets.end(), partTargets.targets.begin(), partTargets.targets.end());
				targets.distances_c.insert(targets.distances_c.end(), partTargets.distances_c.begin(), partTargets.distances_c.end());
				targets.distances_t.insert(targets.distances_t.end(), partTargets.distances_t.begin(), partTargets.distances_t.end());
			}
		}
		//Targets targets_info(targets, distance, distanceToCastle);
		goalTarget = choosePriorityTarget(&targets);
		if (goalTarget != nullptr)
		{
			if (towers[i]->getTarget() == nullptr)
			{
				towers[i]->setTarget(goalTarget);
			}
			else
			{
				towers[i]->setTarget(goalTarget);
			}
		}
	}

	//handle Towers
	setModeTraps();
}
Targets MoveSystem::detectTargets(Lier* lier, Tower* tower)
{
	std::vector<Enemy*> targets;
	std::vector<EnemyWave*> waves;
	std::vector<float> distance;
	std::vector<float> distanceToCastle;
	waves = lier->getWaves();
	int waves_s = waves.size();
	for (int i = 0; i < waves_s; i++)
	{
		std::vector<Enemy*> enemies = waves[i]->getEnemies();
		int size_en = enemies.size();
		if (size_en && enemies[0]->getVisible())
		{
			for (int j = 0; j < size_en; j++)
			{
				if (enemies[j]->getVisible())
				{
					//handle towers
					Enemy* tmp = enemies[j];
					tmp->setEnemyWave(waves[i]);
					sf::Vector2f Origin(WIDTH/2, HEIGHT/2);
					sf::Vector2f pos_e = enemies[j]->getPosition();
					pos_e = pos_e + Origin;
					sf::Vector2f pos_t = tower->getTile()->getSprite().getPosition();
					sf::Vector2f vector_range = pos_t - pos_e;
					float dist = getDistance(vector_range);
					if (dist <= tower->getRange())
					{
						float dist_c = getDistanceToCastle(tmp);
						distance.push_back(dist);
						distanceToCastle.push_back(dist_c);
						targets.push_back(tmp);
					}
				}
			}
		}
	}
	Targets _targets(targets, distance, distanceToCastle);
	return _targets;
}
void MoveSystem::setModeTraps()
{

	int size_t = traps.size();
	bool change = false;
	for (int i = 0; i < size_t; i++)
	{
		std::vector<Enemy* >targets;
		for (auto lier : liers)
		{
			for (auto wave : lier->getWaves())
			{
				for (auto enemy : wave->getEnemies())
				{
					if (enemy->getVisible())
					{
						sf::Vector2f pos = traps[i]->getTile()->getSprite().getPosition();
						sf::Vector2f pos_e = enemy->getPosition();
						pos_e.x += 32;
						pos_e.y += 32;
						pos = pos - pos_e;
						if (getDistance(pos) <= traps[i]->getRange())
						{
							if (!traps[i]->getMode())
							{
								traps[i]->setMode(true);
								change = true;
							}
						}
					}
				}
			}
		}
	}
	if (change)
	{
		_manager->applyChanges();
	}
}
Enemy* MoveSystem::choosePriorityTarget(Targets* targets)
{
	srand(time(0));
	if (!targets->targets.empty())
	{
		Targets firstP = firstPriority(targets);
		if (firstP.targets.size() > 1)
		{
			Targets secondP = secondPriority(&firstP);
			if (secondP.targets.size() > 1)
			{
				Targets thirdP = thirdPriority(&secondP);
				if (thirdP.targets.size() > 1)
				{
					//Really? oh my god
					int index = rand() / thirdP.targets.size();
					return thirdP.targets[index];
				}
				return thirdP.targets[0];
			}
			return secondP.targets[0];
		}
		return firstP.targets[0];
	}
	return nullptr;
}

Targets MoveSystem::firstPriority(Targets* targets)
{
	int size_tar = targets->targets.size();
	std::vector<float> distance = targets->distances_t;
	std::sort(distance.begin(), distance.end());
	std::vector<float> dist_first;
	int i = 0;

	Targets newTargets;
	while ((i < distance.size()) && ((int)distance[i] == (int)distance[0]))
	{
		dist_first.push_back(distance[i]);
		++i;
	}
	int size_f = dist_first.size();
	for (int j = 0; j < size_f; j++)
	{
		for (int i = 0; i < size_tar; i++)
		{
			if (dist_first[j] == targets->distances_t[i])
			{
				newTargets.distances_t.push_back(dist_first[j]);
				newTargets.distances_c.push_back(targets->distances_c[i]);
				newTargets.targets.push_back(targets->targets[i]);
			}
		}
	}
	return newTargets;
}

Targets MoveSystem::secondPriority(Targets* targets)
{
	int size_tar = targets->targets.size();
	std::vector<float> distance = targets->distances_c;
	std::sort(distance.begin(), distance.end());
	std::vector<float> dist_first;
	int i = 0;

	Targets newTargets;
	while ((i < distance.size()) && ((int)distance[i] == (int)distance[0]))
	{
		dist_first.push_back(distance[i]);
		++i;
	}
	int size_f = dist_first.size();
	for (int j = 0; j < size_f; j++)
	{
		for (int i = 0; i < size_tar; i++)
		{
			if (dist_first[j] == targets->distances_c[i])
			{
				newTargets.distances_t.push_back(dist_first[j]);
				newTargets.distances_c.push_back(targets->distances_t[i]);
				newTargets.targets.push_back(targets->targets[i]);
			}
		}
	}
	return newTargets;
}

Targets MoveSystem::thirdPriority(Targets* targets)
{
	int size_tar = targets->targets.size();
	std::vector<float> hp;
	//Initilazing hp 
	for (int i = 0; i < size_tar; i++)
	{
		hp.push_back(targets->targets[i]->gethp());
		++i;
	}
	sort(hp.begin(), hp.end());
	std::vector<float> hp_first;
	int i = 0;

	Targets newTargets;
	while ((i < hp.size()) && ((int)hp[i] == (int)hp[0]))
	{
		hp_first.push_back(hp[i]);
	}
	int size_f = hp_first.size();
	for (int j = 0; j < size_f; j++)
	{
		for (int i = 0; i < size_tar; i++)
		{
			if (hp_first[j] == targets->targets[i]->gethp())
			{
				newTargets.distances_t.push_back(hp_first[j]);
				newTargets.distances_c.push_back(targets->distances_t[i]);
				newTargets.targets.push_back(targets->targets[i]);
			}
		}
	}
	return newTargets;
}
float MoveSystem::getDistance(sf::Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}
MoveSystem::MoveSystem(EntityManager* manager)
{
	this->setManager(manager);
	liers = this->_manager->getLiers();
	castles = this->_manager->getCastles();
}
float MoveSystem::getDistanceToCastle(Enemy* target)
{
	const std::list<sf::Vector2i>* list = target->getPointsList();
	std::list<sf::Vector2i>::const_iterator it = list->begin();
	float distanceToCastle = 0;
	sf::Vector2f old;
	for (it; it != list->end(); ++it)
	{
		sf::Vector2f vec;
		vec.x = (float)(*it).x;
		vec.y = (float)(*it).y;
		if (distanceToCastle == 0)
		{
			vec = vec - target->getPosition();
		}
		else
		{
			vec = vec - old;
		}
		distanceToCastle += getDistance(vec);
		old = vec;
	}
	return distanceToCastle;
}