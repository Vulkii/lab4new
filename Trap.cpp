#include "Trap.h"
#include <iostream>
Trap::Trap(const Tile* tile, EffectType typ):Bulding(tile),damage(200),range(64),type(typ),explosion(false)
{
	sf::Rect <int> rect(0, 0, 64, 64);
	sf::Image widget; //создаем объект Image (изображение)
	widget.loadFromFile("data/Trap_v3.png");//загружаем в него файл
	widget.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(widget);
	_tile.setTexture(texture, rect);
	_tile.setOrigin(32,32);
	_tile.setPositionToCenter();
	if (type == EffectType::frost)
		_tile.setColor(sf::Color::Cyan);
	if (type == EffectType::poison)
		_tile.setColor(sf::Color::Green);
	if (type == EffectType::m_weakness)
		_tile.setColor(sf::Color::Red);
}

void Trap::update(sf::Time dt)
{
	elapsedTime += dt;
	if (elapsedTime >= timeDetonation)
	{
		std::cout << "Time to destroi" << std::endl;
		elapsedTime = timeDetonation;
	}
}
bool Trap::checkTime()const
{
	if (elapsedTime == timeDetonation)
		return true;
	return false;
}
void Trap::draw(sf::RenderWindow* window)
{
	_tile.setTexture(texture);
	window->draw(_tile.getSprite());
}
Trap::Trap(const Trap& c)
{
	if (this != &c)
	{
		_manager = c._manager;
		this->damage = c.damage;
		this->elapsedTime = c.elapsedTime;
		this->range = c.range;
		this->explosion = c.explosion;
		this->texture = c.texture;
		this->type = c.type;
		this->_tile = c._tile;
	}
}
const Trap& Trap::operator=(const Trap& c)
{
	if (this != &c)
	{
		_manager = c._manager;
		this->damage = c.damage;
		this->elapsedTime = c.elapsedTime;
		this->range = c.range;
		this->explosion = c.explosion;
		this->texture = c.texture;
		this->type = c.type;
		this->_tile = c._tile;
	}
	return *this;
}