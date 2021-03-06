#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "PlayerHero.h"
#include "GameObjectManager.h"
#include "Platform.h"

class Game
{
public:
	static GameObjectManager _gameObjectManager;
	static void Start();
	static sf::RenderWindow& GetWindow();
	static sf::View& GetView();
	const static sf::InputStream& GetInput();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	static float MAX_SPEED;

private:
	static std::vector<Platform::note> MakeChord(Platform::note root, Platform::note third, Platform::note fifth);
	static bool IsExiting();
	static void GameLoop();
	static void ShowSplashScreen();
	static void ShowMenu();
	static void UpdateView();

	enum GameState { Uninitialized, ShowingSplash, Paused, 
					ShowingMenu, Playing, Exiting };

	static sf::Clock _gameClock;
	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static sf::View _playerCamera;
};
