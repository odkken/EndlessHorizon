#include "stdafx.h"
#include "Platform.h"
#include "Game.h"


Platform::Platform(float width, float height, float x, float y) 
{
	_isShape=true;
	_shape.setSize(sf::Vector2f(width,height));
	_shape.setPosition(x,y);
	_shape.setFillColor(sf::Color::Red);
	_shape.setOutlineThickness(-4);
	_shape.setOutlineColor(sf::Color(0,0,0,127));
}


Platform::~Platform(void)
{
}

void Platform::Update(sf::Time elapsedTime)
{
	_shape.setOutlineColor(sf::Color(0,0,0,127));
	static PlayerHero& player = *(PlayerHero*)Game::_gameObjectManager.Get("APlayer");
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
	if (
		(
			(playerBox.left <= platformBox.left && playerBox.right >= platformBox.left) //straddling left edge
			||
			(playerBox.left >= platformBox.left && playerBox.right <= platformBox.right) //all the way in
			||
			(playerBox.left <= platformBox.right && playerBox.right >= platformBox.right) //straddling right
		)
		&&
		(playerBox.bottom >= platformBox.top && playerBox.bottom < platformBox.bottom && player.GetVelocity().y>0) //only if you're trying to fall into the platform
	   )
	{
		_shape.setOutlineColor(sf::Color(255,255,255,255));
		player.SetClosest(_shape);
		player.GroundCollide(true);
	}
}
