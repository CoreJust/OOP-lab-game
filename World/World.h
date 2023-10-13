// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Rect.h"
#include "Tile/Tile.h"
#include "Graphics/Render/RenderMaster.h"

class Player;

// The game world
class World final {
private:
	Tile* m_field[2]; // Background and foreground tiles
	Tile* m_fieldCenter[2];

	math::Vector2i m_size; // from the center to a corner
	uint32_t m_width;
	uint32_t m_height;

private:
	void initFor(const math::Vector2u& worldSizeFromCenter);

public:
	World();
	World(const math::Vector2u& worldSizeFromCenter); // Vector from the center to the corner
	World(const World& other) = delete;
	World(World&& other) noexcept;
	~World();

	World& operator=(const World& other) = delete;
	World& operator=(World&& other) noexcept;

	void update(Player& player, float deltaTime);
	void draw(RenderMaster& renderMaster, Camera& camera);

	void fillArea(const math::Recti& rect, bool isForeground, TileId id);

	const math::Vector2i& getSize() const;

	math::Vector2i getNearestPassableLocation(const math::Vector2i& from) const noexcept; // returns from if no passable location found
	math::Vector2i getRandomLocation() const noexcept;
	math::Vector2i getRandomPassableLocation() const noexcept;

	bool isObstacleAt(const math::Vector2i& pos) const;

	const Tile& at(bool isForeground, const math::Vector2i& pos) const;
	Tile& atMut(bool isForeground, const math::Vector2i& pos);
	Tile& atMutBackground(const math::Vector2i& pos);
	Tile& atMutForeground(const math::Vector2i& pos);
};