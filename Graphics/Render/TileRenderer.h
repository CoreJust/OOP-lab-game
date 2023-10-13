// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>

#include "Math/Vector.h"
#include "World/Tile/TileId.h"
#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Camera.h"

class TileRenderer final {
private:
	struct TileRenderInfo {
		TileId id;
		math::Vector2f pos;
	};

private:
	ResourceManager& m_pManager;

	std::vector<TileRenderInfo> m_tiles[2]{ };

public:
	TileRenderer(ResourceManager& pManager);

	void addTile(const bool isForeground, const math::Vector2f& pos, const TileId id);

	void render(sf::RenderWindow& window, Camera& camera);
};