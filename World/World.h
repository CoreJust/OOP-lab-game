#pragma once
#include "Tile/Tile.h"
#include "Entity/Player.h"
#include "Graphics/Render/RenderMaster.h"

// The game world
class World final {
private:
	Tile* m_field[2]; // Background and foreground tiles
	Tile* m_fieldCenter[2];

	utils::Vector2i m_size; // from the center to a corner
	uint32_t m_width;
	uint32_t m_height;

private:
	void initFor(const utils::Vector2u& worldSizeFromCenter);

public:
	World(const utils::Vector2u& worldSizeFromCenter); // Vector from the center to the corner
	~World();

	void update(Player& player, float deltaTime);
	void draw(RenderMaster& renderMaster, Camera& camera);

	void fillArea(const utils::Vector2i& from, const utils::Vector2i& to, bool isForeground, TileId id);

	bool isObstacleAt(const utils::Vector2i& pos);

	Tile& at(bool isForeground, const utils::Vector2i& pos);
	Tile& atBackground(const utils::Vector2i& pos);
	Tile& atForeground(const utils::Vector2i& pos);
};