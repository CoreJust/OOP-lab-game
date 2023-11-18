// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "ResourceManager.h"

/*
*	ResourceRegisterer(.h/.cpp) contains a class that allows to load resources.
*
*	It accepts the resource manager and loads all the game medias to it.
* 
*	Usage:
*		ResourceRegisterer(manager).registerAll();
*/

class ResourceRegisterer final {
private:
	ResourceManager& m_resManager;

public:
	ResourceRegisterer(ResourceManager& resManager);

	void registerAll();

private:
	void registerEntityTexture(const EntityId id);
};