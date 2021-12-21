#include "LightInfantry.h"


LightInfantry::LightInfantry(std::list<sf::Vector2i> l) :Enemy(l,EnemyType::Light_Infantry)
{
	sf::Rect <int> rect(0, 0, 64, 64);
	sf::Image widget; //создаем объект Image (изображение)
	widget.loadFromFile("data/light_infantry.png");//загружаем в него файл
	widget.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(widget);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}
void LightInfantry::draw(sf::RenderWindow* window)
{
	if (visible)
	{
		//rectHealthbar.setTexture(&healthbar);
		sprite.setTexture(texture);
		window->draw(sprite);
		window->draw(rectHealthbar);
	}
}