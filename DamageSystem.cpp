#include "DamageSystem.h"
#include "EntityManager.h"
#include "Enemy.h"
DamageSystem::DamageSystem()
{

}
DamageSystem::DamageSystem(EntityManager* manager)
{
	this->setManager(manager);
	castles = this->_manager->getCastles();
	liers = this->_manager->getLiers();
}
void DamageSystem::update(sf::Time dt)
{
	int liers_s = liers.size();
	for (int i = 0; i < liers_s; i++)
	{
		handleEnemies(liers[i]);
	}
	handleTraps();
}

int DamageSystem::handleEnemies(Lier* lier)
{
	traps = this->_manager->getTraps();
	std::vector<EnemyWave*> waves;
	waves = lier->getWaves();
	int waves_s = waves.size();
	for (int i = 0; i < waves_s; i++)
	{
		std::vector<Enemy*> enemies = waves[i]->getEnemies();
		int size_en = enemies.size();
		if (size_en&&enemies[0]->getVisible())
		{
			for (int j = 0; j < size_en; j++)
			{
				handleCastles(enemies[j],waves[i]);
			}
		}
	}
	return 1;
}
void  DamageSystem::handleCastles(Enemy* enemy, EnemyWave* wave)
{
	//std::cout << "Enemy index " << j << "HP,Position, " << enemies[j]->getHP() << " {" << enemies[j]->getPosition().x << " | "<<enemies[j]->getPosition().y << "} " << std::endl;
	sf::Vector2f pos_e = enemy->getPosition();
	pos_e.x = (int)pos_e.x;
	pos_e.y = (int)pos_e.y;


	int size_c = castles.size();
	for (int i_c = 0; i_c < size_c; i_c++)
	{
		sf::Vector2f pos = castles[i_c]->getTile()->getSprite().getPosition();
		//std::cout << "Position castles {" << pos.x << " | " << pos.y <<"} "<< std::endl;
		if (pos == pos_e)
		{
			dealDamageCastle(wave, enemy, castles[i_c]);
		}
	}

}

void DamageSystem::handleTraps()
{

	int size_t = traps.size();
	for (int i = 0; i < size_t; i++)
	{
		if (!traps[i]->getMode())
		{
			//std::cout<<"otfunboleno po modu" << std::endl;
			continue;
		}
		if (!traps[i]->checkTime())
		{
			//std::cout << "otfunboleno po time" << std::endl;
			continue;
		}
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
						enemy->setEnemyWave(wave);
						pos_e.x += 32;
						pos_e.y += 32;
						sf::Vector2f pos2 = pos;
						pos = pos - pos_e;
						if (getDistance(pos) <= traps[i]->getRange())
						{
							std::cout << "Pos traps: {"<<pos2.x<<" | "<< pos2.y<<"} Range" << getDistance(pos) << " Posittion enemy with orgn:" << pos_e.x << " | " << pos_e.y << std::endl;
							targets.push_back(enemy);
						}
					}
				}
			}
		}
		if (!targets.empty())
		{
			dealDamageEnemy(targets, traps[i]);
		}
		size_t = traps.size();
	}
}
void DamageSystem::dealDamageCastle (EnemyWave* wave, Enemy* enemy, Castle* castle)
{
	float hp_e = enemy->gethp();
	castle->takeDamage(hp_e);
	wave->removeEnemy(enemy);
}

void DamageSystem::dealDamageEnemy( std::vector<Enemy*> enemies, Trap* trap)
{
	//Добавить таймер
	for (auto enemy : enemies)
	{
		float hp_e = enemy->gethp();
		std::cout << "Take damage unit " << enemy->getName() << " Position" << enemy->getPosition().x << " | " << enemy->getPosition().y << std::endl;
		if (hp_e - trap->getDamage() <= 0)
		{
			_manager->addGold(enemy->getGold());
		}
		enemy->takeDamage(trap->getDamage(), trap->getEffectType());
		std::cout << "HP unit " << enemy->gethp()<<std::endl;
	}
	sf::Vector2i pos;
	pos.x = (int)trap->getTile()->getSprite().getPosition().x;
	pos.y = (int)trap->getTile()->getSprite().getPosition().y;
	_manager->removeTrap(pos);
}