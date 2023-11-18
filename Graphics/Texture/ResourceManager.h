// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <map>
#include <memory>

#include "World/Entity/EntityId.h"
#include "Texture.h"
#include "TextureAtlas.h"

/*
*	ResourceManager(.h/.cpp) contains a class that contains and manages 
*	the game's resources - medias such as textures, animations, sounds, etc.
*
*	It must be filled in by the ResourceRegisterer before usage.
*/

// Manages images/animations/...
class ResourceManager final {
private:
	std::unique_ptr<TextureAtlas> m_atlas;
	std::unique_ptr<Texture> m_entityTextures[EntityId::NUMBER_ENTITY_IDS];

public:
	ResourceManager();

	TextureAtlas& getTextureAtlas();
	Texture& getEntityTexture(const EntityId id);

	void loadTextureAtlas();
	void loadEntityTexture(const EntityId id, const std::string& fileName);
};