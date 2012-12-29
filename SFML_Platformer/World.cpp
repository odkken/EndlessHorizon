#include "stdafx.h"
#include "World.h"

World::World()
{
	//temporary bs for now
	for (int i=0; i<5; i++)
	{
		platforms.push_back(Platform(100,50,i*200,400));
	}
}

void World::LoadWorld(GameObjectManager& manager)
{
	int i=0;
	for (Platform platform : platforms)
	{
		manager.Add("Platform" + i, &platform);
	}
}