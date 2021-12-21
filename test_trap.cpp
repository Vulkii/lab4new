#include "pch.h"


//TEST(TrapConstructor, InitConstructor) {
//	std::cout << "\n\n";
//	std::cout << "////////////////////////Trap////////////////////" << std::endl;
//	const Tile tile;
//	//Tower tower(Tower(&tile, TowerType::SimpleTower));
//	Tower tow(&tile, TowerType::SimpleTower);
//	const float a[] = { 100, 140 };
//	const  float b[] = { 50 , 80 };
//	ASSERT_EQ(a[0], tow.getRange());
//	const TableStateTower t = tow.getTable();
//	ASSERT_EQ(b[0], t.damage);
//	//lvlup
//	tow.lvlUP();
//	const TableStateTower f = tow.getTable();
//	ASSERT_EQ(a[1], tow.getRange());
//	ASSERT_EQ(b[1], f.damage);
//
//
//	//copy constructor
//	Tower tow2(tow);
//	ASSERT_EQ(a[1], tow2.getRange());
//	const TableStateTower t2 = tow2.getTable();
//	ASSERT_EQ(b[1], t2.damage);
//	//lvlup
//	tow2.lvlUP();
//	const TableStateTower f2 = tow2.getTable();
//	ASSERT_EQ(a[1], tow2.getRange());
//	ASSERT_EQ(b[1], f2.damage);
//}
//
//TEST(TrapConstructor, TestException)
//{
//
//}
//
//TEST(TrapMethods, Setters)
//{
//	const Tile tile;
//	Tower tow(&tile, TowerType::SimpleTower);
//	ASSERT_EQ(nullptr, tow.getTarget());
//	ASSERT_EQ(TowerType::SimpleTower, tow.getTowerType());
//
//	const TableStateTower t2 = tow.getTable();
//	ASSERT_EQ(EffectType::none, t2.type_ef);
//
//	ASSERT_ANY_THROW(tow.setAngle(-181));
//}
//
//TEST(TrapMethods, Parameters)
//{
//	std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
//	Enemy en(chepoits, EnemyType::Light_Infantry);
//	Tile tile;
//	sf::Sprite sprite;
//	sprite.setPosition(sf::Vector2f(45, 64));
//	tile.setSprite(sprite);
//	tile.setPositionToCenter();
//	Tower tower(&tile, TowerType::MagicTowerF);
//	//Play in situaton
//	float hp = en.gethp();
//
//	while (en.gethp() == hp)
//	{
//		const sf::Time frameTime = sf::seconds(1.f / 60.f);
//		en.update(frameTime);
//		sf::Vector2f pos = en.getPosition() - tower.getTile()->getSprite().getPosition();
//		if (MoveSystem::getDistance(pos) <= tower.getRange())
//		{
//			tower.setTarget(&en);
//		}
//		tower.update(frameTime);
//	}
//
//	std::cout << "Hp enemy:: " << en.gethp() << std::endl;
//
//	const double err = 0.0001;
//	ASSERT_NEAR(-11.7682886, tower.getAngle(), err);
//	//ASSERT_EQ(EffectType::frost, en.get);
//
//
//}