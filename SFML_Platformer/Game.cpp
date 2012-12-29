#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "NewtonianObject.h"
#include "Platform.h"
void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Pang!");

	_playerCamera.setSize(1024, 768);
	_playerCamera.setCenter(_mainWindow.getDefaultView().getCenter());

	PlayerHero *player1 = new PlayerHero();
	player1->SetPosition(sf::Vector2f((SCREEN_WIDTH/2),500));
	player1->SetMaxSpeed(40);
	_gameObjectManager.Add("APlayer",player1);
	
	Platform *ground = new Platform(1000,50,0,600);
	_gameObjectManager.Add("Bground", ground);

	for (int i=0; i<10; ++i)
	{
		Platform *plat = new Platform(100,30,100 + 300*i, 500);
		_gameObjectManager.Add("BPlatform" + i, plat);
	}

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
			UpdateView();
			_mainWindow.clear(sf::Color(50,200,255));
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
				_gameObjectManager.GetNewtonian("APlayer")->SetPosition(sf::Vector2f(400,400));
				_gameObjectManager.GetNewtonian("APlayer")->Stop();
				_playerCamera.move(_gameObjectManager.GetNewtonian("APlayer")->GetPosition().x - _playerCamera.getCenter().x, 0);
			}
			break;
		}
	}
}

sf::View& Game::GetView()
{
	return _playerCamera;
}

//magic numbers for mathemagic
void Game::UpdateView()
{
	static float maxCamSpeed=100;
	static PlayerHero& player = *(PlayerHero*)_gameObjectManager.Get("APlayer");
	// the third term keeps the camera ahead of the player, according to his current velocity.
	float viewOffset = player.GetPosition().x+player.GetBounds().width/2.0f - _playerCamera.getCenter().x + 10*player.GetVelocity().x;
	float velocity= (abs(viewOffset) > 100) ? .001f*abs(viewOffset)*viewOffset : 0;
	float time = _gameClock.restart().asSeconds()*10;
	if (abs(velocity)>maxCamSpeed)
		velocity = velocity>0 ? maxCamSpeed : -maxCamSpeed;
	_playerCamera.move(time*velocity, 0);
	_mainWindow.setView(_playerCamera);
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
		_gameClock.restart();
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
sf::View Game::_playerCamera;
sf::Clock Game::_gameClock;