#pragma once
#include "GameObjectManager.h"
#include "Platform.h"

class World
{
public:
	World();
	void LoadWorld(GameObjectManager& manager);

private:
	std::vector<Platform> platforms;
};

