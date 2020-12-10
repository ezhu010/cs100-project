#include "Game.h"
#include "Mediator.h"
#include "Menu.h"
#include "Point.h"
#include "abstractFactory.h"
#include <catch2/catch.hpp>

TEST_CASE("Composition Window Size test X", "[CompositionMenu]")
{
	Menu* menu = new Menu("Test Menu");
	REQUIRE(menu->window->getSize().x == 800);
}

TEST_CASE("Composition Window Size test Y", "[CompositionMenu]")
{
	Menu* menu = new Menu("Test Menu");
	REQUIRE(menu->window->getSize().y == 600);
}

TEST_CASE("Composition Title Test", "[CompositionMenu]")
{
	Menu* menu = new Menu("Test Menu");

	REQUIRE(menu->title == "Test Menu");
}

TEST_CASE("Composition SubMenu Test", "[CompositionMenu]")
{
	Menu* menu = new Menu("Test Menu");
	MenuItem* item1 = new MenuItem("item1");
	MenuItem* item2 = new MenuItem("item2");
	MenuItem* item3 = new MenuItem("item3");
	menu->add(item1);
	menu->add(item2);
	menu->add(item3);

	REQUIRE(menu->numberOfMenuItems == 3);
}

TEST_CASE("Composition Zero SubMenues", "[CompositionMene]")
{
	Menu* menu = new Menu("Test Menu");
	REQUIRE(menu->numberOfMenuItems == 0);
}

TEST_CASE("Mediator Easy", "[MediatorEasyEnemy]")
{
	Mediator* controlSpeed = new Mediator();
	Point* points = new Point();
	points->score = 300;
	EasyEnemy* enemy = new EasyEnemy();
	int ypos = enemy->enemy->getPosition().y + 6.0f;
	controlSpeed->checkrate(enemy, points);
	enemy->move();
	REQUIRE(ypos == enemy->enemy->getPosition().y);
}

TEST_CASE("Mediator Hard", "[MediatorHardEnemy]")
{
	Mediator* controlSpeed = new Mediator();
	Point* points = new Point();
	points->score = 300;
	HardEnemy* enemy = new HardEnemy();
	int ypos = enemy->enemy->getPosition().y + 6.0f;
	controlSpeed->checkrate(enemy, points);
	enemy->move();
	REQUIRE(ypos == enemy->enemy->getPosition().y);
}

TEST_CASE("Easy Enemy", "[Easy Enemy]")
{
	EasyEnemy* temp = new EasyEnemy();
	REQUIRE(temp->enemy->getSize().x == 100.f);
	REQUIRE(temp->enemy->getSize().y == 100.f);
	int ypos = temp->enemy->getPosition().y + 5.0f;
	temp->enemy->move(0.f, 5.0f);
	REQUIRE(ypos == temp->enemy->getPosition().y);
	REQUIRE(temp->enemy->getFillColor() == sf::Color::Green);
}

TEST_CASE("Hard Enemy", "[Hard Enemy]")
{
	HardEnemy* temp = new HardEnemy();
	REQUIRE(temp->enemy->getSize().x == 75.f);
	REQUIRE(temp->enemy->getSize().y == 75.f);
	int ypos = temp->enemy->getPosition().y + 5.0f;
	temp->enemy->move(0.f, 5.0f);
	REQUIRE(ypos == temp->enemy->getPosition().y);
	REQUIRE(temp->enemy->getFillColor() == sf::Color::Blue);
}

TEST_CASE("sf::RenderWindow", "[renderwindow]")
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	REQUIRE(window.getSize().x == 200);
	REQUIRE(window.getSize().y == 200);

	sf::CircleShape shape(window.getSize().x / 2);
	shape.setFillColor(sf::Color::White);

	REQUIRE(shape.getRadius() == 100.0f);
	REQUIRE(shape.getFillColor() == sf::Color::White);
	REQUIRE(static_cast<int>(shape.getLocalBounds().width) == 198);
	REQUIRE(static_cast<int>(shape.getLocalBounds().height) == 200);

	REQUIRE(window.isOpen() == true);
}
