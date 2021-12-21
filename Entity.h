#pragma once
#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__
#include <SFML/Graphics.hpp>
class EntityManager;

/*!
\brief The general abstract entity class*/
class Entity
{
public:
	Entity() = default;

	/*!
	\brief A virtual method of the class that handles the time tick*/
	virtual void update(sf::Time) = 0;
	void setEManager(EntityManager*);
	EntityManager* getEManager()
	{
		return _manager;
	}
protected:
	EntityManager* _manager;///< Safety pointer to the entity controller
};

#endif