#include "pch.h"


TEST(EnemyConstructor, InitConstructor) {
	std::cout << "\n\n";
	std::cout << "////////////////////////Enemy////////////////////" << std::endl;
	Enemy eny;
	ASSERT_EQ(eny.gethp(), 250.f);
	ASSERT_EQ(eny.getVisible(), false);
	ASSERT_EQ(eny.getSpeed(), 100.f);

	std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
	Enemy en(chepoits, EnemyType::Light_Infantry);

	sf::Vector2f pos;
	pos.x= (float)(*chepoits.begin()).x;
	pos.y = (float)(*chepoits.begin()).y;
	ASSERT_EQ(en.getPosition(),pos );
}

TEST(EnemyConstructor, TestException)
{
	std::list<sf::Vector2i> chepoits;
	ASSERT_ANY_THROW(Enemy en(chepoits, EnemyType::Light_Infantry));
}

TEST(EnemyMethods, Setters)
{

	std::cout << "There are default setters!!!" << std::endl;
}

TEST(EnemyMethods, Parameters)
{
	std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
	Enemy en(chepoits, EnemyType::Light_Infantry);
	Tile tile;
	sf::Sprite sprite;
	sprite.setPosition(sf::Vector2f(45, 64));
	tile.setSprite(sprite);
	tile.setPositionToCenter();
	Tower tower(&tile, TowerType::MagicTowerF);
	//Play in situaton
	float hp = en.gethp();
	en.setVisible(true);

	while (en.gethp() == hp)
	{
		const sf::Time frameTime = sf::seconds(1.f / 60.f);
		en.update(frameTime);
		sf::Vector2f pos = en.getPosition() - tower.getTile()->getSprite().getPosition();
		if (MoveSystem::getDistance(pos) <= tower.getRange())
		{
			tower.setTarget(&en);
		}
		tower.update(frameTime);
	}

	std::cout << "Hp enemy:: " << en.gethp() << std::endl;

	const double err = 0.0001;
	ASSERT_NEAR(-172.0928344, tower.getAngle(), err);
	//ASSERT_EQ(EffectType::frost, en.get);


}