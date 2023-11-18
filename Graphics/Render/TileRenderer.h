// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Math/Vector.h"
#include "Math/Direction.h"
#include "World/Tile/TileId.h"
#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Shader/TileShader.h"
#include "Graphics/Model/TileModel.h"
#include "Graphics/Camera.h"

/*
*	TileRenderer(.h/.cpp) contains a class that is the renderer for tiles.
*/

class TileRenderer final {
private:
	struct TileRenderInfo {
		TileId id;
		math::Vector2f pos;

		math::DirectionFlag VNSurroundings;
		bool hasVNS;
	};

	struct TileModelInfo {
		std::vector<model::TileModel> variants; // For tiles with several variants
	};

private:
	ResourceManager& m_pManager;
	TileShader m_shader;

	std::vector<TileModelInfo> m_models;
	std::vector<TileRenderInfo> m_tiles{ };

public:
	TileRenderer(ResourceManager& pManager);

	void addTile(const math::Vector2f& pos, const TileId id);
	void addTile(const math::Vector2f& pos, const TileId id, const math::DirectionFlag VNS);

	void render(sf::RenderWindow& window, Camera& camera);
};