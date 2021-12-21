#include "Enemy.h"
#include "EntityManager.h"


void Enemy::setEnemyWave(EnemyWave* wave)
{
	_wave = wave;
}

void Enemy::selfdestruction()
{
	_wave->removeEnemy(this);
}
void Enemy::update(sf::Time dt)
{
	if (visible)
	{
		auto it = checkPoints.begin();
		if (points == 0)
		{
			checkPoints.erase(it);
			it = checkPoints.begin();
			points++;
		}
		if (!checkPoints.empty())
		{
			if ((int)sprite.getPosition().x != (*it).x)
			{
				if (sprite.getPosition().x < (*it).x)
				{
					float fluctuation_x = sprite.getPosition().x + dt.asSeconds() * this->speed;
					if (fluctuation_x > (*it).x)
						fluctuation_x = (*it).x;
					sprite.setPosition(fluctuation_x, sprite.getPosition().y);
					rectHealthbar.setPosition(fluctuation_x +16, sprite.getPosition().y-10);
				}
				else
				{
					float fluctuation_x = sprite.getPosition().x - dt.asSeconds() * this->speed;
					if (fluctuation_x < (*it).x)
						fluctuation_x = (*it).x;
					sprite.setPosition(fluctuation_x, sprite.getPosition().y);
					rectHealthbar.setPosition(fluctuation_x+16, sprite.getPosition().y-10);
				}
			}
			if ((int)sprite.getPosition().y != (*it).y)
			{
				if (sprite.getPosition().y < (*it).y)
				{
					float fluctuation_y = sprite.getPosition().y + dt.asSeconds() * this->speed;
					if (fluctuation_y > (*it).y)
						fluctuation_y = (*it).y;
					sprite.setPosition(sprite.getPosition().x, fluctuation_y);
					rectHealthbar.setPosition(sprite.getPosition().x+16, fluctuation_y-10);

				}
				else
				{
					float fluctuation_y = sprite.getPosition().y - dt.asSeconds() * this->speed;
					if (fluctuation_y < (*it).y)
						fluctuation_y = (*it).y;
					sprite.setPosition(sprite.getPosition().x, fluctuation_y);
					rectHealthbar.setPosition(sprite.getPosition().x+16, fluctuation_y-10);
				}
			}
			if (((int)sprite.getPosition().y == (*it).y) && ((int)sprite.getPosition().x == (*it).x))
			{
				checkPoints.erase(it);
			}
		}
		float scale = hp / HP_MAX;
		rectHealthbar.setSize({ 32.f * scale,10.f });
		controlEffects(dt);

	}
}
bool Enemy::takeDamage(float damage, EffectType type)
{
	hp -= (damage + damage * increaseDamage);
	if ((sprite.getColor() == sf::Color::Green) && (hp <= 50))
	{
		sprite.setColor(sf::Color::Cyan);
	}
	if (hp <= 0)
	{
		hp = 0;
		return true;
	}
	addEffect(type);
	return false;
}
Enemy::Enemy() :HP_MAX(250), hp(250), money(40), speed(100.f), visible(false), points(0), increaseDamage(0)
{
	//sf::Rect <int> rect(0, 0, 10, 32);
	sf::Image widget; //создаем объект Image (изображение)
	widget.loadFromFile("data/healthbar.png");//загружаем в него файл
	widget.createMaskFromColor(sf::Color(255, 255, 255));
	healthbar.loadFromImage(widget);
	rectHealthbar.setTexture(&healthbar);
	rectHealthbar.setSize({ 32.f,10.f });
	//rectHealthbar.setTextureRect(rect);
}
Enemy::Enemy(std::list <sf::Vector2i> Points, EnemyType Type) : Enemy()
{
	name = Type;
	if (Points.empty())
		throw "Bad points";
	checkPoints = Points;
	sf::Vector2f pos;
	std::list <sf::Vector2i>::iterator it = Points.begin();
	pos.x = (*it).x;
	pos.y = (*it).y;
	sprite.setPosition(pos);
	pos.y -= 10;
	pos.x += 32;
	rectHealthbar.setPosition(pos);
}
void Enemy::setOrigin()
{
	//DANGER 32 = 64/2 64 -tile size 
	sprite.setOrigin(WIDTH / 2, HEIGHT / 2);
}
void Enemy::reSetOrigin()
{
	//DANGER 32 = 64/2 64 -tile size 
	sprite.setOrigin(0, 0);
}

bool Enemy::addEffect(EffectType type)
{
	if (type == EffectType::none)
	{
		//this->setColor(sf::Color::Red);
		return false;
	}
	if (findEffect(type) >= 0)
		return false;
	if (type == EffectType::frost)
		sprite.setColor(sf::Color::Blue);
	if (type == EffectType::poison)
		sprite.setColor(sf::Color::Green);
	if (type == EffectType::m_weakness)
		sprite.setColor(sf::Color::Yellow);
	Effect ef(type,&hp,&speed,&increaseDamage);
	//ef.setEnemy(this);
	this->effects.push_back(ef);
	return true;
}

int Enemy::controlEffects(sf::Time dt)
{
	if (effects.empty())
		return 0;
	updateEf(dt);
	removeEffects();
	if (hp <= 0)
		this->selfdestruction();
	return 1;
}
void Enemy::updateEf(sf::Time dt)
{
	auto it = effects.begin();
	for (it; it!=effects.end(); ++it)
	{
		(*it).update(dt, &hp);
	}
}

void Enemy::removeEffects()
{
	auto it = effects.begin();
	//best_list::List<Effect>::IterList del = nullptr;
	bool del = false;
	for (it; it != effects.end();del = false)
	{
		if ((*it).checkTime())
		{
			(*it).returnState(&speed, &increaseDamage);
			auto tmp = it;
			++it;
			effects.erase(tmp);
			del = true;
			if (effects.empty())
				sprite.setColor(sf::Color::White);
		}
		if (!del)
			++it;
	}
}
int Enemy::findEffect(EffectType type)
{
	auto it = effects.begin();
	for (it; it != effects.end(); ++it)
	{
		if ((*it).getType() == type)
		{
			(*it).setTime(sf::Time::Zero);
			return 1;
		}
	}
	return -1;
}