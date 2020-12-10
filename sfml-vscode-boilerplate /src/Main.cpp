#include "Game.h"
#include "Menu.h"
#include "Platform/Platform.hpp"
int main()
{

	MainMenu* mainMenu = new Menu("Main Menu");
	// MainMenu* playButton = new MenuItem("Play(P)");
	// mainMenu->add(playButton);

	MainMenu* diffEasy = new MenuItem("Easy(E)");
	mainMenu->add(diffEasy);
	MainMenu* diffHard = new MenuItem("Hard(H)");
	mainMenu->add(diffHard);
	MainMenu* displayButton = new Menu("Display(D)");
	MainMenu* inderpreet = new MenuItem("Inderpreet");
	MainMenu* edward = new MenuItem("Edward");
	MainMenu* arya = new MenuItem("Arya");
	displayButton->add(inderpreet);
	displayButton->add(edward);
	displayButton->add(arya);
	mainMenu->add(displayButton);

	MainMenu* quitButton = new MenuItem("Quit(Q)");
	mainMenu->add(quitButton);

	while (mainMenu->running())
	{
		mainMenu->update();
		mainMenu->render();
	}

	// Menu menu(800, 600);
	// while (menu.running())
	// {
	// 	menu.update();
	// 	menu.render();
	// }
}