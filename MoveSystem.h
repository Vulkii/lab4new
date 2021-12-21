#pragma once
#ifndef __MOVESYSTEM_H_INCLUDED__
#define __MOVESYSTEM_H_INCLUDED__
#include "System.h"
#include "Tower.h"
#include "Lier.h"
#include "Castle.h"
#include "Trap.h"



/// Structure that describes all the visible towers of the enemies, with their characteristics
struct Targets
{
	/*std::vector<Target> targets;*/
	std::vector<Enemy*> targets; ///< Enemies visible by towers
	std::vector<float> distances_t;///< distance to tower for enemies
	std::vector<float> distances_c;///< distance to castle for enemies
	Targets() = default;
	Targets(std::vector<Enemy*>, std::vector<float>, std::vector<float>);
};

/*!
\brief One of the core system classes that are required to trace changes in the movement of enemies

It implements a system of targeting towers and traps, relative to the movement of enemies
/bug error of the explosion trap
*/
class MoveSystem : public System
{
public:

	MoveSystem() = default;
	MoveSystem(EntityManager*);
	~MoveSystem() = default;
	virtual void update(sf::Time);
	float static getDistance(sf::Vector2f);
private:
	//functions

	/*!
	\brief Treatment of tower: a search for target
	\return Targets - found array of targets for a single tower
	*/
	Targets detectTargets(Lier*, Tower*);


	/*!
	\brief The main function that determines the target of the tower
	\return Enemy*  <- the chosen target
	*/
	Enemy* choosePriorityTarget(Targets*);
	void setModeTraps();

	/*!
	\brief Selecting a goal by first priority

	The first priority is the distance to the tower
	*/
	Targets firstPriority(Targets*);

	/*!
	\brief The sample target according to the second priority

	The second priority is the distance to the castle
	*/
	Targets secondPriority(Targets*);

	/*!
	\brief Sampling targets for the third priority

	The third priority is HP. There is a selection of enemies with the highest HP
	*/
	Targets thirdPriority(Targets*);

	float getDistanceToCastle(Enemy*);
	//attribute

	std::vector<Tower*> towers;
	std::vector<Lier*> liers;
	std::vector<Castle*>castles;
	std::vector<Trap*>traps;
};

#endif