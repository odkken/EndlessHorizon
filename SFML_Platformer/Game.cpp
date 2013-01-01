#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "NewtonianObject.h"
#include "Platform.h"
#include <random>
void Game::Start(void)
{
	const int PLAT_WIDTH = 100;
	const int PLAT_HEIGHT = 90;
	if(_gameState != Uninitialized)
		return;
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Pang!");



	//create player
	PlayerHero *player1 = new PlayerHero();
	player1->SetPosition(sf::Vector2f(0,300));
	player1->SetMaxSpeed(40);
	player1->name="CPlayer";
	_gameObjectManager.Add(player1->name,player1);
	
	_playerCamera.setSize(1024, 768);
	_playerCamera.setCenter(_mainWindow.getDefaultView().getCenter());

	//create distinct starting platform
	Platform *ground = new Platform(1000000,300,-500000,600, (Platform::note)-1);
	ground->name="Bground";
	_gameObjectManager.Add(ground->name, ground);

	//NOTES//////////////
	std::vector< std::vector<Platform::note> > chords;
	typedef Platform::note qnote;

	chords.push_back(MakeChord(qnote::cs1,qnote::f1,qnote::as2));
	chords.push_back(MakeChord(qnote::c1,qnote::f1,qnote::a2));
	chords.push_back(MakeChord(qnote::cs1,qnote::f1,qnote::as2));
	chords.push_back(MakeChord(qnote::c1,qnote::f1,qnote::a2));
	chords.push_back(MakeChord(qnote::cs1,qnote::f1,qnote::as2));
	chords.push_back(MakeChord(qnote::ds1,qnote::gs1,qnote::c2));
	chords.push_back(MakeChord(qnote::f1,qnote::gs1,qnote::cs2));
	chords.push_back(MakeChord(qnote::ds1,qnote::gs1,qnote::c2));
	chords.push_back(MakeChord(qnote::f1,qnote::gs1,qnote::cs2));
	chords.push_back(MakeChord(qnote::f1,qnote::as2,qnote::d2));
	chords.push_back(MakeChord(qnote::fs1,qnote::as2,qnote::ds2));
	chords.push_back(MakeChord(qnote::f1,qnote::as2,qnote::d2));
	chords.push_back(MakeChord(qnote::fs1,qnote::as2,qnote::ds2));
	chords.push_back(MakeChord(qnote::g1,qnote::cs2,qnote::e2));
	chords.push_back(MakeChord(qnote::as2,qnote::c2,qnote::f2));
	chords.push_back(MakeChord(qnote::as2,qnote::c2,qnote::f2));
	chords.push_back(MakeChord(qnote::a2,qnote::c2,qnote::f2));
	chords.push_back(MakeChord(qnote::a2,qnote::c2,qnote::f2));
	//procedurally create "pixel" platforms.  Need to make a class to do this 
	std::mt19937 mt;
	mt.seed(_gameClock.getElapsedTime().asMicroseconds());
	std::uniform_real_distribution<float> dr;
	std::uniform_int_distribution<int> di(0,2);

	
	int i=0;
	int j=0;
	for (std::vector<Platform::note> chord : chords)
	{
		for (Platform::note note : chord)
		{
			Platform *plat = new Platform(PLAT_WIDTH,PLAT_HEIGHT,(PLAT_WIDTH*3 + 200)*i+PLAT_WIDTH*j, 500 +5*j, note);
			plat->name="BPlatform" + std::to_string(i) + "_" + std::to_string(j);
			_gameObjectManager.Add(plat->name, plat);
			++j;
		}
		j=0;
		++i;
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
			_mainWindow.clear(sf::Color(50,200,255));
			_gameObjectManager.UpdateAll();
			UpdateView();
			_gameObjectManager.DrawAll(_mainWindow);
			
			_mainWindow.display();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || currentEvent.type==sf::Event::Closed) _gameState = Game::Exiting;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
				_mainWindow.setFramerateLimit(60);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
				_mainWindow.setFramerateLimit(0);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			{
				_gameObjectManager.GetNewtonian("CPlayer")->SetPosition(sf::Vector2f(0,300));
				_gameObjectManager.GetNewtonian("CPlayer")->Stop();
				_playerCamera.move(_gameObjectManager.GetNewtonian("CPlayer")->GetPosition().x - _playerCamera.getCenter().x, 0);
			}
			break;
		}
	}
}

sf::View& Game::GetView()
{
	return _playerCamera;
}

//magic numbers for mathemagics
void Game::UpdateView()
{
	static float maxCamSpeed=100;
	static PlayerHero& player = *(PlayerHero*)_gameObjectManager.Get("CPlayer");
	// the third term keeps the camera ahead of the player, according to his current velocity.
	float viewOffset = player.GetPosition().x+player.GetBounds().width/2.0f - _playerCamera.getCenter().x + 10*player.GetVelocity().x;
	float velocity= (abs(viewOffset) > 100) ? .001f*abs(viewOffset)*viewOffset : 0;
	float time = _gameClock.restart().asSeconds()*10;
	if (abs(velocity)>maxCamSpeed)
		velocity = velocity>0 ? maxCamSpeed : -maxCamSpeed;
	_playerCamera.move(time*velocity, 0);
	//_playerCamera.setCenter(player.GetPosition());  //fixed on player always
	_mainWindow.setView(_playerCamera);
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}


std::vector<Platform::note> Game::MakeChord(Platform::note root, Platform::note third, Platform::note fifth)
	{
		std::vector<Platform::note> chord;
		chord.push_back(root);
		chord.push_back(third);
		chord.push_back(fifth);
	return chord;	
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