#include "pch.h"


TEST(EffectConstructor, InitConstructor) {
	std::cout << "\n\n";
	std::cout << "////////////////////////Effect////////////////////" << std::endl;
	/*std::list<sf::Vector2i> chepoits = { sf::Vector2i(40,40),sf::Vector2i(40,100) };
	Enemy enemy(chepoits, EnemyType::Light_Infantry);*/
	float speed = 150, hp = 2000, incD = 0.f;
	Effect typical_effect_first(EffectType::m_weakness,  &hp, & speed , &incD);
	
	ASSERT_EQ(speed, 150);
	ASSERT_EQ(incD, 0.3f);

	Effect typical_effect_second(EffectType::frost, &hp, &speed, &incD);

	ASSERT_EQ(speed, 105);
	ASSERT_EQ(incD, 0.3f);
}

TEST(EffectConstructor, TestException)
{
	float speed = 150, hp = 2000, incD = 1.f;
	ASSERT_ANY_THROW(Effect typical_effect_first(EffectType::m_weakness, &hp, &speed, &incD));
	hp = 0 , incD = 0;
	ASSERT_ANY_THROW(Effect typical_effect_first(EffectType::m_weakness, &hp, &speed, &incD));
	hp = 11, speed = 0;
	ASSERT_ANY_THROW(Effect typical_effect_first(EffectType::frost, &hp, &speed, &incD));
	speed = 150;
	ASSERT_ANY_THROW(Effect typical_effect_first(EffectType::frost, &hp, &incD , &speed));
}

TEST(EffectMethods, Setters)
{
	float speed = 150, hp = 2000, incD = 0.f;
	Effect typical_effect_first(EffectType::m_weakness, &hp, &speed, &incD);
	typical_effect_first.setTime(sf::Time::Zero);
	ASSERT_EQ(false, typical_effect_first.checkTime());
	ASSERT_ANY_THROW(typical_effect_first.setTime(sf::seconds(10.f)););
}

TEST(EffectMethods, Parameters)
{
	float speed = 150, hp = 2000, incD = 0.f;
	Effect typical_effect_first(EffectType::frost, &hp, &speed, &incD);
	typical_effect_first.returnState(&speed, &incD);
	ASSERT_EQ(150,speed);

}