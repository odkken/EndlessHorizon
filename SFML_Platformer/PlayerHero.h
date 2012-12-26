#pragma once
#include "NewtonianObject.h"

class PlayerHero : public NewtonianObject
{
public:
	PlayerHero();
	~PlayerHero();

	void Update(sf::Time elapsedTime);

private:
	int sensitivity; //sets acceleration control for movement

};
