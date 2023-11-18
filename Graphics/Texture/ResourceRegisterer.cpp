// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ResourceRegisterer.h"

ResourceRegisterer::ResourceRegisterer(ResourceManager& resManager)
	: m_resManager(resManager) {
}

void ResourceRegisterer::registerAll() {
	for (id_t id = 0; id < EntityId::NUMBER_ENTITY_IDS; id++) {
		registerEntityTexture(EntityId::Value(id));
	}

	m_resManager.loadTextureAtlas();
}

void ResourceRegisterer::registerEntityTexture(const EntityId id) {
	std::string name = id.toString();
	std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });

	m_resManager.loadEntityTexture(id, name);
}
