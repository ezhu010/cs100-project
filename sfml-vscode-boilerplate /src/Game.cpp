#include "Game.h"
void Game::initVariables()
{
	this->enemy = nullptr;
	this->window = nullptr;
	this->endGame = false;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;										   //window height
	this->videoMode.width = 800;										   //window width
	this->window = new sf::RenderWindow(this->videoMode, "CS100 Project"); //creates the window
	this->window->setFramerateLimit(60);
}

//create the enemy
// void Game::initEnemies()
// {
// 	this->enemy->setPosition(10.f, 10.f);
// 	this->enemy->setSize(sf::Vector2f(100.f, 100.f));
// 	this->enemy->setScale(sf::Vector2f(0.5f, 0.5f));
// 	this->enemy->setFillColor(sf::Color::Cyan);
// 	this->enemy->setOutlineColor(sf::Color::Green);
// 	this->enemy->setOutlineThickness(1.f);
// }
void Game::initFonts()
{
	if (this->font.loadFromFile("content/fonts/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to Load"
				  << "\n";
	}
}
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("None");
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	// this->initEnemies();
	this->factory = nullptr;
	// this->factory1 = new EasyEnemyFactory(); // if easy mode
	// this->factory2 = new HardEnemyFactory();
	this->points = new Point();
	this->controlSpeed = new Mediator();
	this->enemy = nullptr;
}
Game::~Game()
{
	delete window;
}

void Game::setDiff(int flag)
{
	if (flag == 0)
	{
		factory = new EasyEnemyFactory();
	}
	else
	{
		factory = new HardEnemyFactory();
	}
}

bool Game::running() const
{
	return this->window->isOpen();
}

bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnEnemy()
{

	// this->enemy = new sf::RectangleShape();
	//this->enemy = new Enemy();
	this->enemy = factory->createEnemy();

	// switch (type)
	// {
	// 	case 0:
	// 		this->enemy = factory1->createEnemy();
	// 		break;
	// 	case 1:
	// 		this->enemy = factory2->createEnemy();
	// 		// this->enemy->setPosition(
	// 		// 	static_cast<float>(rand() % static_cast<int>(600 - this->enemy->getSize().x)),
	// 		// 	0.f);
	// 		// this->enemy->setSize(sf::Vector2f(70.f, 70.f));
	// 		// this->enemy->setFillColor(sf::Color::Blue);
	// 		break;
	// 	default:
	// 		// handle error
	// 		std::cout << "Test";
	// 		break;
	// }

	this->enemies.push_back(this->enemy);
	//Remove enemies
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(*(e->enemy));
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points->score << "\n"
	   << "Health: " << this->health;
	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();

			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	for (unsigned long i = 0; i < this->enemies.size(); i++)
	{
		controlSpeed->checkrate(this->enemies[i], this->points);
		this->enemies[i]->move();
		// controlSpeed->checkrate(this->points);
		// this->enemies[i]->move(0.f, 5.f * controlSpeed->rate);
		if (this->enemies[i]->enemy->getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}
	//Check if clicked

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			for (size_t i = 0; i < this->enemies.size() && deleted == false; ++i)
			{
				if (this->enemies[i]->enemy->getGlobalBounds().contains(this->mousePosView))
				{

					if (this->enemies[i]->enemy->getFillColor() == sf::Color::Blue)
					{
						this->points->incrementHard();
					}

					else if (this->enemies[i]->enemy->getFillColor() == sf::Color::Green)
					{
						this->points->incrementEasy();
					}
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

//handles key board events
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window->close();
			break;
		}
		if (this->ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	this->pollEvents();
	if (this->endGame == false)
	{
		this->updateMousePositions();
		this->updateText();
		this->updateEnemies();
	}
	//endgame condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}
}
void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}
void Game::render()
{
	this->window->clear();
	// this->window->draw(this->enemy);
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}
