#include "stdafx.h"
#include "PlayerHero.h"
#include "Game.h"


PlayerHero::PlayerHero() : NewtonianObject(), sensitivity(15)
{
	Load("images/runner.png");
	assert(IsLoaded());
	OnGround(false);
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width /2, GetSprite().getGlobalBounds().height / 2);
	_maxSpeed=20;
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && GetPosition().y>490)
		Push(sf::Vector2f(0,-100));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		Push(sf::Vector2f(0,GetMass()*9.8));



	DoPhysics(elapsedTime);
}