#include "stdafx.h"
#include "Platform.h"
#include "Game.h"

float Platform::_jumpTime(1);//seconds
Platform::Platform(float width, float height, float x, float y, int color) 
{
	_jumpClock.restart();
	sf::Color sfcol;
	switch (color)
	{
	case 0:
		soundBuffer.loadFromFile("sounds/1c-xylo.wav");
		sfcol=sf::Color::Red;
		break;
	case 1:
		soundBuffer.loadFromFile("sounds/1e-xylo.wav");
		sfcol=sf::Color::Green;
		break;
	case 2:
		soundBuffer.loadFromFile("sounds/1g-xylo.wav");
		sfcol=sf::Color::Blue;
		break;
	default:
		break;
	}
	dong.setBuffer(soundBuffer);
	_isShape=true;
	_shape.setSize(sf::Vector2f(width,height));
	_shape.setPosition(x,y);
	_shape.setFillColor(sfcol);
	_shape.setOutlineThickness(-4);
	_shape.setOutlineColor(sf::Color(0,0,0,127));
}


Platform::~Platform(void)
{
}

void Platform::Update(sf::Time elapsedTime)
{
	_shape.setOutlineColor(sf::Color(0,0,0,127));
	static PlayerHero& player = *(PlayerHero*)Game::_gameObjectManager.Get("CPlayer");
	static struct box {float top, right, left, bottom;} playerBox, platformBox;

	static sf::FloatRect playerRect;
	//update playerbox
	playerRect = player.GetBounds();
	playerBox.left = playerRect.left;
	playerBox.top = playerRect.top;
	playerBox.right = playerBox.left + playerRect.width;
	playerBox.bottom = playerBox.top + playerRect.height;

	//update platformbox
	platformBox.left =_shape.getPosition().x;
	platformBox.right = platformBox.left + _shape.getSize().x;
	platformBox.top = _shape.getPosition().y;
	platformBox.bottom = platformBox.top + _shape.getSize().y;

	//check for player colliding with this platform
	if
		(
			((playerBox.left >= platformBox.left && playerBox.left <= platformBox.right) || (playerBox.right >= platformBox.left && playerBox.right <= platformBox.right))
		&&
			(playerBox.bottom >= platformBox.top && playerBox.bottom < platformBox.top+20 && player.GetVelocity().y>0) //only if you're trying to fall into the platform
		)
	{
		//only sound it if you've got enough downward velocity.  Takes care of infinite hitting while standing, and also makes sense (have to give it a whack)
		if (player.GetVelocity().y > 5)
		{
			dong.play();
		}
		_shape.setOutlineColor(sf::Color(255,255,255,255));
		player.SetClosest(_shape);
		player.GroundCollide(true);
	}
}
