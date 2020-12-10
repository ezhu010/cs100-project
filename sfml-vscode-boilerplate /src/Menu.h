#ifndef __MENU_H__
#define __MENU_H__
#include "Game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
//#define MAX_NUM_OF_ITEMS 2

class MainMenu
{
public:
	std::string title;
	// virtual void quit() = 0;
	// virtual void back() = 0;
	sf::Text text;
	sf::Font font;
	MainMenu(std::string title) :
		title(title)
	{
		if (!font.loadFromFile("content/fonts/Roboto-black.ttf"))
		{
			// handle error
		}
		text.setFont(font);
		text.setFillColor(sf::Color::Green);
		text.setString(title);
	}
	virtual void add(MainMenu* item) = 0;
	virtual bool running() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
};

class Menu : public MainMenu
{
public:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Text text;
	std::vector<MainMenu*> submenus;
	int selectedItemIndex;
	int numberOfMenuItems;
	Menu(std::string title) :
		MainMenu(title)
	{

		this->selectedItemIndex = 0;
		this->numberOfMenuItems = 0;
		this->videoMode.height = 600;
		this->videoMode.width = 800;
		this->window = new sf::RenderWindow(this->videoMode,
			this->title);
		this->window->setFramerateLimit(60);
	}

	bool running()
	{
		return this->window->isOpen();
	}

	void draw(sf::RenderWindow* window)
	{
		for (const auto& item : submenus)
			window->draw(item->text);
	}

	void add(MainMenu* item)
	{
		submenus.push_back(item);
		numberOfMenuItems++;
		for (int i = 0; i < numberOfMenuItems; i++)
		{
			submenus[i]->text.setPosition(sf::Vector2f(350, 600 / (numberOfMenuItems + 1) * (i + 1)));
		}
		//menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 1));
	}

	void render()
	{
		this->window->clear();
		this->draw(this->window);

		this->window->display();
		// std::cout << this->window->getTitle();
	}

	void pollEvents()
	{
		while (this->window->pollEvent(this->ev))
		{
			switch (this->ev.type)
			{
				case sf::Event::Closed:
					this->window->close();
					break;

				case sf::Event::KeyPressed:
					if (ev.key.code == sf::Keyboard::E)
					{
						Game game;
						game.setDiff(0);
						while (game.running() && !game.getEndGame())
						{
							game.update();
							game.render();
						}
					}
					else if (ev.key.code == sf::Keyboard::H)
					{
						Game game;
						game.setDiff(1);
						while (game.running() && !game.getEndGame())
						{
							game.update();
							game.render();
						}
					}
					else if (ev.key.code == sf::Keyboard::Q)
					{
						this->window->close();
					}
					else if (ev.key.code == sf::Keyboard::D)
					{

						MainMenu* display = submenus[2];

						while (display->running())
						{
							display->update();
							display->render();
						}
					}

				default:
					break;
			}
		}
	}

	void update()
	{
		this->pollEvents();
	}

	~Menu()
	{
		delete window;
	}
};

// class Menu : public MainMenu
// {
// private:
// 	float width, height;
// 	sf::RenderWindow* window;
// 	sf::VideoMode videoMode;
// 	sf::Event ev;

// 	int selectedItemIndex;
// 	sf::Text menu[MAX_NUM_OF_ITEMS];
// 	sf::Font font;

// 	void initVariables();
// 	void initWindow();

// public:
// 	Menu(float width, float height);
// 	~Menu();

// 	int getPressedButton();

// 	bool running() const;
// 	void pollEvents();
// 	void update();
// 	void render();

// 	void draw(sf::RenderWindow* window);
// 	void moveUp();
// 	void moveDown();
// };

class MenuItem : public MainMenu
{
public:
	MenuItem(std::string title) :
		MainMenu(title)
	{
	}
	virtual void add(MainMenu* item)
	{
		std::cout << item->title;
	}
	virtual bool running()
	{
		return false;
	}
	virtual void render()
	{
	}
	virtual void update()
	{
	}
};

#endif