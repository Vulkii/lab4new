#include "pch.h"
#include <SFML/Graphics.hpp>

TEST(CastleConstructor, InitConstructor) {
	std::cout << "\n\n";
	std::cout << "////////////////////////Castle////////////////////" << std::endl;
	Tile tile;
	//Tower tower(Tower(&tile, TowerType::SimpleTower));
	Castle castle(&tile);
	ASSERT_EQ(1000.f, castle.gethp());
}

TEST(CastleConstructor, TestException)
{
	std::cout << "There have not exception!!!"<< std::endl;
}

TEST(CastleMethods, Setters)
{
	std::cout << "There have not setters!!!" << std::endl;
}

TEST(CastleMethods, Parameters)
{
	std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
	Enemy en(chepoits, EnemyType::Light_Infantry);
	Tile tile;
	sf::Sprite sprite;
	sprite.setPosition(sf::Vector2f(40, 100));
	tile.setSprite(sprite);
	Castle castle(&tile);
	en.setVisible(true);

	while (en.getPosition() != castle.getTile()->getSprite().getPosition())
	{
		const sf::Time frameTime = sf::seconds(1.f / 60.f);
		en.update(frameTime);
		if (en.getPosition() == castle.getTile()->getSprite().getPosition())
			castle.takeDamage(en.gethp());
	}

	std::cout << "Hp castle:: " << castle.gethp() << std::endl;
	ASSERT_EQ(750, castle.gethp());
	bool flag = false;
	for (int i = 0; i < 3; i++)
	{
		flag = false;
		flag = castle.takeDamage(en.gethp());
		std::cout << "Hp castle:: " << castle.gethp() << std::endl;
	}
	ASSERT_EQ(true, flag);
}