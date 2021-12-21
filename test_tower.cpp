#include "pch.h"


TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(TowerConstructor, InitConstructor) {
	std::cout << "\n\n";
	std::cout << "////////////////////////Tower////////////////////" << std::endl;
	Tile tile;
	//Tower tower(Tower(&tile, TowerType::SimpleTower));
	Tower tow(&tile, TowerType::SimpleTower);
	const float a[] = { 100, 140 };
	const  float b[] = { 50 , 80 };
	ASSERT_EQ(a[0], tow.getRange());
	const TableStateTower t = tow.getTable();
	ASSERT_EQ(b[0], t.damage);
	//lvlup
	tow.lvlUP();
	const TableStateTower f = tow.getTable();
	ASSERT_EQ(a[1], tow.getRange());
	ASSERT_EQ(b[1], f.damage);


	//copy constructor
	Tower tow2(tow);
	ASSERT_EQ(a[1], tow2.getRange());
	const TableStateTower t2 = tow2.getTable();
	ASSERT_EQ(b[1], t2.damage);
	//lvlup
	tow2.lvlUP();
	const TableStateTower f2 = tow2.getTable();
	ASSERT_EQ(a[1], tow2.getRange());
	ASSERT_EQ(b[1], f2.damage);
}

TEST(TowerConstructor, TestException)
{
	std::cout << "There are exeptions of costruct!!" << std::endl;
}

TEST(TowerMethods, Setters)
{
	std::cout << "There are default setters!!!" << std::endl;
}

TEST(TowerMethods, Parameters)
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

	while (en.gethp() == hp )
	{
		const sf::Time frameTime = sf::seconds(1.f / 60.f);
		en.update(frameTime);
		sf::Vector2f pos = en.getPosition() - tower.getTile()->getSprite().getPosition();
		if (MoveSystem::getDistance(pos) <= tower.getRange() )
		{
			tower.setTarget(&en);
		}
		tower.update(frameTime);
	}

	std::cout << "Hp enemy:: " << en.gethp() << std::endl;

	const double err = 0.0001;
	ASSERT_NEAR(-11.7682886, tower.getAngle(), err);
	//ASSERT_EQ(EffectType::frost, en.get);


}
int main(int argc, char** argv) {
	clear_boy();
	//TestSituation *test;
	//::testing::AddGlobalTestEnvironment((::testing::Environment*)test);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}