#pragma once
#include "VisibleGameObject.h"

class Platform : public VisibleGameObject
{
public:
	Platform(float width, float height, float x, float y);
	~Platform(void);

	void Update(sf::Time elapsedtime);
};

