#ifndef GAME_H
#define GAME_H
#include "Mediator.h"
#include "Point.h"
#include "abstractFactory.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	Mediator* controlSpeed;
	int health;
	bool endGame;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned maxEnemies;
	bool mouseHeld;
	EnemyCreationFactory* factory;
	Point* points;
	std::vector<Enemy*>
		enemies;
	Enemy* enemy;
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();
	//Resources
	sf::Font font;
	//Test
	sf::Text uiText;

public:
	Game();
	void setDiff(int);
	virtual ~Game();
	bool running() const;
	bool getEndGame() const;
	void spawnEnemy();
	void updateEnemies();
	void renderEnemies(sf::RenderTarget& target);
	void pollEvents();
	void updateMousePositions();
	void updateText();
	void renderText(sf::RenderTarget& target);
	void update();
	void render();
};

#endif