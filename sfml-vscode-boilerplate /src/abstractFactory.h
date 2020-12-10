#ifndef __ABSTRACT_H__
#define __ABSTRACT_H__
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Enemy
{
public:
	sf::RectangleShape* enemy;
	double speed;
	Enemy()
	{
		enemy = new sf::RectangleShape();
	};
	virtual void move() = 0;
};

class EasyEnemy : public Enemy
{
public:
	EasyEnemy() :
		Enemy()
	{
		this->speed = 5.0;
		this->enemy->setSize(sf::Vector2f(100.f, 100.f));
		this->enemy->setFillColor(sf::Color::Green);
		this->enemy->setPosition(
			static_cast<float>(rand() % static_cast<int>(600 - this->enemy->getSize().x)),
			0.f);
	}
	void move()
	{
		this->enemy->move(0.f, this->speed);
	}
};

class EnemyCreationFactory
{
public:
	virtual Enemy* createEnemy() = 0;
};

class EasyEnemyFactory : public EnemyCreationFactory
{
public:
	// EasyEnemy* easyenemy;
	EasyEnemy* createEnemy()
	{
		return new EasyEnemy();
	}
};

class HardEnemy : public Enemy
{
public:
	HardEnemy() :
		Enemy()
	{
		this->speed = 5;
		this->enemy->setSize(sf::Vector2f(75.f, 75.f));
		this->enemy->setFillColor(sf::Color::Blue);
		this->enemy->setPosition(
			static_cast<float>(rand() % static_cast<int>(600 - this->enemy->getSize().x)),
			0.f);
	}
	void move()
	{
		this->enemy->move(0.f, this->speed);
	}
};

class HardEnemyFactory : public EnemyCreationFactory
{
public:
	// EasyEnemy* easyenemy;
	HardEnemy* createEnemy()
	{
		return new HardEnemy();
	}
};

#endif