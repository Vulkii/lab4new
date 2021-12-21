#pragma once

#ifndef __BUILDING_N_INCLUDED__
#define __BUILDING_H_INCLUDED__

#include "Entity.h"
#include "Tile.h"

class Tile;

/*!
\brief It is a descriptor of a logical structure that occupies a single tile*/
class Bulding:public Entity
{
public:
	Bulding();
	Bulding(const Tile* tile);
	void setTile(const Tile* tile);
	const Tile * getTile();
	virtual void update(sf::Time) = 0;

protected:
	Tile _tile;
};

#endif