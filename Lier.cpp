#pragma warning(disable : 4996)
#include "Lier.h"
#include <iostream>
Lier::Lier(const Tile* tile, std::list <sf::Vector2i> list) :Bulding(tile), numberWaves(3), beginTime(sf::Time::Zero), checkPoints(list), numberWave(0), cooldownWave(sf::seconds(1.f))
{
	generateWave();
	/*checkPoints.po*/
}

void Lier::generateWave()
{
	if (numberWave < numberWaves)
	{
		EnemyWave wave(checkPoints, 1);
		waves.push_back(wave);
	}
}
void Lier::draw(sf::RenderWindow* window)
{
	int size = waves.size();
	for (int i = 0; i < size; i++)
	{
		waves[i].draw(window);
	}
	//if (!font.loadFromFile("CyrilicOld.ttf"))
	//{
	//	std::cout << "Error of downdload FONT of the text" << std::endl;
	//}
	//textLier.setFont(font);
	//textLier.setCharacterSize(24);
	////textLier.setColor(Color::Magenta);
	//sf::Vector2f pos;
	//pos = this->getTile()->getSprite().getPosition();
	//pos.x -= 10;
	//pos.y -= 10;
	//textLier.setPosition(pos.x, pos.y);
	//std::string strLier = std::to_string(numberWave) + "/" + std::to_string(this->numberWaves);
	//textLier.setString(strLier);
	//window->draw(textLier);
}
void Lier::update(sf::Time frameTime)
{
	beginTime += frameTime;
	if (beginTime > cooldownWave)
	{	
		waves[0].update(frameTime);
	}
}
std::vector<EnemyWave*> Lier::getWaves()
{
	std::vector<EnemyWave*> tmp;
	int size = waves.size();
	for (int i = 0; i < size; i++)
	{
		tmp.push_back(&waves[i]);
	}
	return tmp;

}

//void Lier::removeEn(Enemy* enemy)
//{
//	int size = waves.size();
//	for (int i = 0; i < size; i++)
//	{
//		waves[i].removeEnemy(enemy);
//	}
//}
