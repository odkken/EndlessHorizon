#include "stdafx.h"
#include "Platform.h"
#include "Game.h"


Platform::Platform(float width, float height, float x, float y) 
{
	_isShape=true;
	_shape.setSize(sf::Vector2f(width,height));
	_shape.setPosition(x,y);
	_shape.setFillColor(sf::Color::Red);
}


Platform::~Platform(void)
{
}

void Platform::Update(sf::Time elapsedTime)
{
	static PlayerHero& player = *(PlayerHero*)Game::_gameObjectManager.Get("Player");
	static struct box {float top, right, left, bottom;} playerBox, platformBox;
	
	static sf::FloatRect playerRect;
	//update playerbox
	playerRect = player.GetSprite().getGlobalBounds();
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
			(playerBox.left < platformBox.left && playerBox.right > platformBox.left) //straddling left edge
			||
			(playerBox.left > platformBox.left && playerBox.right < platformBox.right) //all the way in
			||
			(playerBox.left < platformBox.right && playerBox.right > platformBox.right) //straddling right
		)
		&&
		(playerBox.bottom > platformBox.top && playerBox.bottom < platformBox.bottom) //only if you're trying to fall into the platform
	   )
	{
		player.SetClosest(_shape);
		player.GroundCollide(true);
	}
}
