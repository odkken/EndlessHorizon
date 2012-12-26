#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "NewtonianObject.h"
void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Pang!");

	_mainWindow.setFramerateLimit(0);

	_view.setSize(1024, 768);
	_view.setCenter(_mainWindow.getDefaultView().getCenter());

	PlayerHero *player1 = new PlayerHero();
	player1->SetPosition(sf::Vector2f((SCREEN_WIDTH/2),500));
	_gameObjectManager.Add("Player",player1);

	VisibleGameObject *background = new VisibleGameObject();
	background->Load("images/background.png");
	_gameObjectManager.Add("Background", background);

	//GameBall *ball = new GameBall();
	//ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2)-15);

	//_gameObjectManager.Add("Ball",ball);

	_gameState= Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}


sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}


void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	switch(_gameState)
	{
	case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
	case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
	case Game::Playing:
		{
			_mainWindow.setView(_view);
			_mainWindow.clear(sf::Color(0,0,0));

			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);

			_mainWindow.display();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || currentEvent.type==sf::Event::Closed) _gameState = Game::Exiting;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
				_mainWindow.setFramerateLimit(60);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
				_mainWindow.setFramerateLimit(0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			{
				NewtonianObject* player = (NewtonianObject*)_gameObjectManager.Get("Player");
				player->SetPosition(sf::Vector2f(400,400));
				player->Stop();
				
			}
			break;
		}
	}
}

sf::View& Game::GetView()
{
	return _view;
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
		_gameState = Exiting;
		break;
	case MainMenu::Play:
		_gameState = Playing;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::View Game::_view;