#include "pch.h"


TEST(LairConstructor, InitConstructor) {
	std::cout << "\n\n";
	std::cout << "////////////////////////Lair////////////////////" << std::endl;
	Tile tile;
	//Tower tower(Tower(&tile, TowerType::SimpleTower));
	std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
	Lier lair(&tile, chepoits);

	ASSERT_EQ(lair.getWaves().size(), 1);
}

TEST(LairConstructor, TestException)
{
	std::cout << "There have not exception!!!" << std::endl;
}

TEST(LairMethods, Setters)
{
	std::cout << "There have not setters!!!" << std::endl;
}

TEST(LairMethods, Parameters)
{
	std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
	Tile tile;
	sf::Sprite sprite;
	sprite.setPosition(sf::Vector2f(40, 100));
	tile.setSprite(sprite);
	Lier lair(&tile, chepoits);
	auto waves = lair.getWaves();
	while (lair.getWaves()[0]->getEnemies()[0]->getVisible() != true)
	{
		const sf::Time frameTime = sf::seconds(1.f / 60.f);
		lair.update(frameTime);
	}
	ASSERT_EQ(true, lair.getWaves()[0]->getEnemies()[0]->getVisible());
}