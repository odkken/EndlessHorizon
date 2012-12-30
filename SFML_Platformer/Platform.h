#pragma once
#include "VisibleGameObject.h"

class Platform : public VisibleGameObject
{
public:
	Platform(float width, float height, float x, float y, int color);
	~Platform(void);

	void Update(sf::Time elapsedtime);

private:
	sf::SoundBuffer soundBuffer;
	sf::Sound dong;
	sf::Clock _jumpClock;
	static float _jumpTime;
};

