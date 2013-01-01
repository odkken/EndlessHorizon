#include "stdafx.h"
#include "Platform.h"
#include "Game.h"

float Platform::_colorTime(.08f);//seconds

Platform::Platform(float width, float height, float x, float y, note n) 
{
	_colorClock.restart();
	sf::Color sfcol;
	switch (n)
	{
	case 0:
		soundBuffer.loadFromFile("sounds/1c.wav");
		sfcol=sf::Color::Red;
		break;
	case 1:
		soundBuffer.loadFromFile("sounds/1c#.wav");
		sfcol=sf::Color::Green;
		break;
	case 2:
		soundBuffer.loadFromFile("sounds/1d.wav");
		sfcol=sf::Color::Blue;
		break;
	case 3:
		soundBuffer.loadFromFile("sounds/1d#.wav");
		sfcol=sf::Color::Red;
		break;
	case 4:
		soundBuffer.loadFromFile("sounds/1e.wav");
		sfcol=sf::Color::Green;
		break;
	case 5:
		soundBuffer.loadFromFile("sounds/1f.wav");
		sfcol=sf::Color::Blue;
		break;
	case 6:
		soundBuffer.loadFromFile("sounds/1f#.wav");
		sfcol=sf::Color::Red;
		break;
	case 7:
		soundBuffer.loadFromFile("sounds/1g.wav");
		sfcol=sf::Color::Green;
		break;
	case 8:
		soundBuffer.loadFromFile("sounds/1g#.wav");
		sfcol=sf::Color::Blue;
		break;
	case 9:
		soundBuffer.loadFromFile("sounds/2a.wav");
		sfcol=sf::Color::Red;
		break;
	case 10:
		soundBuffer.loadFromFile("sounds/2a#.wav");
		sfcol=sf::Color::Green;
		break;
	case 11:
		soundBuffer.loadFromFile("sounds/2b.wav");
		sfcol=sf::Color::Blue;
		break;
	case 12:
		soundBuffer.loadFromFile("sounds/2c.wav");
		sfcol=sf::Color::Red;
		break;
	case 13:
		soundBuffer.loadFromFile("sounds/2c#.wav");
		sfcol=sf::Color::Green;
		break;
	case 14:
		soundBuffer.loadFromFile("sounds/2d.wav");
		sfcol=sf::Color::Blue;
		break;
	case 15:
		soundBuffer.loadFromFile("sounds/2d#.wav");
		sfcol=sf::Color::Red;
		break;
	case 16:
		soundBuffer.loadFromFile("sounds/2e.wav");
		sfcol=sf::Color::Green;
		break;
	case 17:
		soundBuffer.loadFromFile("sounds/2f.wav");
		sfcol=sf::Color::Blue;
		break;
	case 18:
		soundBuffer.loadFromFile("sounds/2f#.wav");
		sfcol=sf::Color::Red;
		break;
	case 19:
		soundBuffer.loadFromFile("sounds/2g.wav");
		sfcol=sf::Color::Green;
		break;
	case 20:
		soundBuffer.loadFromFile("sounds/2g#.wav");
		sfcol=sf::Color::Blue;
		break;
	case 21:
		soundBuffer.loadFromFile("sounds/3a.wav");
		sfcol=sf::Color::Red;
		break;
	case 22:
		soundBuffer.loadFromFile("sounds/3a#.wav");
		sfcol=sf::Color::Red;
		break;

	case -1:
		sfcol=sf::Color::Black;
	default:
		sfcol=sf::Color::Black;
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
	if (_colorClock.getElapsedTime().asSeconds() > _colorTime)
	{
		//tbd fade color
		_shape.setOutlineColor(sf::Color(0,0,0,127));
		_colorClock.restart();
	}
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
		((playerBox.left<=platformBox.left && playerBox.right>=platformBox.right) || (playerBox.left >= platformBox.left && playerBox.left <= platformBox.right) || (playerBox.right >= platformBox.left && playerBox.right <= platformBox.right))
		&&
		(playerBox.bottom >= platformBox.top && playerBox.bottom < platformBox.top+20 && player.GetVelocity().y>0) //only if you're trying to fall into the platform
		)
	{
		//only sound it if you've got enough downward velocity.  Takes care of infinite hitting while standing, and also makes sense (have to give it a whack)
		if (player.GetVelocity().y > 5)
		{
			_shape.setOutlineColor(sf::Color(255,255,255,255));
			_colorClock.restart();
			dong.play();
		}
		player.SetClosest(_shape);
		player.GroundCollide(true);
	}
}
