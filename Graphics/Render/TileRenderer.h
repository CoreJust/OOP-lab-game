#pragma once
#include <vector>

#include "Utils/Vector.h"
#include "World/Tile/TileId.h"
#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Camera.h"

class TileRenderer final {
private:
	struct TileRenderInfo {
		TileId id;
		utils::Vector2f pos;
	};

private:
	ResourceManager* m_pManager;

	std::vector<TileRenderInfo> m_tiles[2]{ };

public:
	TileRenderer(ResourceManager* pManager);

	void addTile(bool isForeground, const utils::Vector2f& pos, TileId id);

	void render(sf::RenderWindow& window, Camera& camera);
};