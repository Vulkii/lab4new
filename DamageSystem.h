
#pragma once

#ifndef __DAMAGESYSTEM_H_INCLUDED__
#define __DAMAGESYSTEM_H_INCLUDED__

#include "System.h"
#include "Entity.h"
#include "Lier.h"
#include "Castle.h"
#include "Trap.h"
//#include "EntityManager.h"

	/*!
	\brief One of the core system classes that are required to trace changes in the movement of enemies

	Implemented for dealing damage to enemies and the castle
	*/
class DamageSystem : public System
{
public:
	DamageSystem();
	DamageSystem(EntityManager*);
	~DamageSystem() = default;
	virtual void update(sf::Time);
	float getDistance(sf::Vector2f vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}
private:
	int handleEnemies(Lier*);
	void dealDamageCastle(EnemyWave* wave, Enemy* enemy, Castle* castle);
	void dealDamageEnemy(std::vector<Enemy*>, Trap* trap);
	void handleCastles(Enemy*,EnemyWave* wave);
	void handleTraps();
	std::vector<Lier*>liers;
	std::vector<Castle*>castles;
	std::vector<Trap*>traps;
};

#endif