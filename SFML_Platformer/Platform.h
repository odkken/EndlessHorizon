#pragma once
#include "VisibleGameObject.h"

class Platform : public VisibleGameObject
{
public:
	enum note{c1,cs1,d1,ds1,e1,f1,fs1,g1,gs1,a2,as2,b2,c2,cs2,d2,ds2,e2,f2,fs2,g2,gs2,a3,as3};

	Platform(float width, float height, float x, float y, note n);
	~Platform(void);

	void Update(sf::Time elapsedtime);

private:
	sf::SoundBuffer soundBuffer;
	sf::Sound dong;
	sf::Clock _colorClock;
	static float _colorTime;
};

