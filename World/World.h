// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Rect.h"
#include "Math/Mapper.h"
#include "Tile/Tile.h"
#include "WorldLevelId.h"
#include "Graphics/Render/RenderMaster.h"

class Player;

// The game world
class World final {
private:
	Tile* m_field[2]; // Background and foreground tiles
	Tile* m_fieldCenter[2];

	math::Mapper<> m_mapper; // Maps the 2D coordinates to 1D array index

public:
	World();
	World(const math::Vector2i& size); // An empty world of the size
	World(WorldLevelId id);

	World(const World& other);
	World(World&& other) noexcept;

	~World();

	World& operator=(const World& other);
	World& operator=(World&& other) noexcept;

	void update(Player& player, float deltaTime);
	void draw(RenderMaster& renderMaster, Camera& camera);

	void fillArea(const math::Recti& rect, bool isForeground, TileId id);
	void fillAreaBounds(const math::Recti& rect, bool isForeground, TileId id);
	void makeTunnel(const math::Vector2i& from, const math::Vector2i& to, TileId floorId); // Makes a passable tunnel
	void makePassable(const math::Vector2i& pos, TileId floorId);

	const math::Vector2i& getSize() const; // size from the center of the world
	const math::Vector2u& getActualSize() const; // (width, height)
	const math::Mapper<>& getMapper() const;

	math::Vector2i getNearestPassableLocation(const math::Vector2i& from) const noexcept; // returns from if no passable location found
	math::Vector2i getRandomLocation() const noexcept;
	math::Vector2i getRandomPassableLocation() const noexcept;

	bool isObstacleAt(const math::Vector2i& pos) const;

	const Tile& at(bool isForeground, const math::Vector2i& pos) const;
	Tile& atMut(bool isForeground, const math::Vector2i& pos);
	Tile& atMutBackground(const math::Vector2i& pos);
	Tile& atMutForeground(const math::Vector2i& pos);
};