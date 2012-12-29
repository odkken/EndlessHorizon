#include "stdafx.h"
#include "PlayerHero.h"
#include "Game.h"
#include "Platform.h"


PlayerHero::PlayerHero() : sensitivity(15)
{
	_isShape=false;
	Load("images/runner.png");
	assert(IsLoaded());
	_maxSpeed=30;
}

PlayerHero::~PlayerHero()
{
}


void PlayerHero::Update(sf::Time elapsedTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		Push(sf::Vector2f(-sensitivity,0));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		Push(sf::Vector2f(sensitivity,0));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && _touchingGround)
		Push(sf::Vector2f(0, -3/elapsedTime.asSeconds()));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		Push(sf::Vector2f(0,GetMass()*9.8));

	DoPhysics(elapsedTime);
}