#include "StdAfx.h"
#include "VisibleGameObject.h"


VisibleGameObject::VisibleGameObject()
{
	name="";
	_isLoaded = false;
	_isShape = false;
}


VisibleGameObject::~VisibleGameObject()
{
}


void VisibleGameObject::Load(std::string filename)
{
	if(_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
		renderWindow.draw(_sprite);
	else if(_isShape)
		renderWindow.draw(_shape);
}

void VisibleGameObject::Update(sf::Time elapsedTime)
{
}

void VisibleGameObject::SetPosition(sf::Vector2f pos)
{
	if(_isLoaded)
	{
		_sprite.setPosition(pos.x,pos.y);
	}
	else
	{
		_shape.setPosition(pos.x, pos.y);
	}
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if(_isLoaded)
		return _sprite.getPosition();
	if(_isShape)
		return _shape.getPosition();
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

sf::RectangleShape& VisibleGameObject::GetShape()
{
	return _shape;
}

sf::FloatRect VisibleGameObject::GetBounds()
{
	return IsLoaded()? _sprite.getGlobalBounds() : _isShape? _shape.getGlobalBounds() : sf::FloatRect();
}