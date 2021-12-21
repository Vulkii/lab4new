#pragma once
#ifndef __LIER_H_INCLUDED__
#define __LIER_H_INCLUDED__
#include "Bulding.h"
#include"EnemyWave.h"
#include <list>

/*!
\brief It is a lair descriptor
Controls the launch of waves.
\bug lier == lair (English)
\todo fix engl
*/
class Lier :public Bulding
{
public:
	Lier(const Tile* tile, std::list <sf::Vector2i>);

	/*!
\brief A virtual overloaded method of the class that handles the time tick
\warning There may be breakdowns due to frequent font loading: unknow bug
\todo fix load texture
*/
	virtual void update(sf::Time);
	void draw(sf::RenderWindow* window);
	std::vector<EnemyWave*> getWaves();
private:
	void generateWave();
	sf::Font font;
	sf::Text textLier;
	std::list <sf::Vector2i> checkPoints;//way from lier to castle. Mass of coordinate
	std::vector<EnemyWave> waves;
	sf::Time beginTime;
	const sf::Time cooldownWave;
	const int numberWaves;
	int numberWave;

};

#endif