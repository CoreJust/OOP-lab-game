// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "World.h"
#include "IO/Logger.h"
#include "Utils/Random.h"
#include "GlobalSettings.h"
#include "Entity/Player.h"
#include "Generator/WorldGenerationMaster.h"

constexpr math::Vector2u DEFAULT_WORLD_SIZE { 10, 10 }; // 21x21
constexpr math::Vector2u MINIMAL_WORLD_SIZE { 1, 1 }; // 3x3

constexpr size_t DEFAULT_SEED = 1;

void World::initFor(const math::Vector2u& worldSizeFromCenter) {
	m_size = math::Vector2i(worldSizeFromCenter);
	m_width = 2 * m_size.x() + 1;
	m_height = 2 * m_size.y() + 1;

	m_field[0] = new Tile[size_t(m_width) * m_height];
	m_field[1] = new Tile[size_t(m_width) * m_height];

	m_fieldCenter[0] = m_field[0] + int64_t(m_size.y()) * m_width + m_size.x();
	m_fieldCenter[1] = m_field[1] + int64_t(m_size.y()) * m_width + m_size.x();

	fillArea({ -m_size, m_size }, false, TileId::EMPTINESS);
	fillArea({ -m_size, m_size }, true, TileId::EMPTINESS);
}

World::World() : World(DEFAULT_WORLD_SIZE) { }

World::World(const math::Vector2u& worldSizeFromCenter) {
	if (!MINIMAL_WORLD_SIZE.isToUpLeftFrom(worldSizeFromCenter)) {
		io::Logger::logError("Too small of a size for a world: " + worldSizeFromCenter.toString());
	}

	initFor(worldSizeFromCenter);

	// Generation
	WorldGenerationMaster generationMaster(*this);
	generationMaster.pushInitialGenerator(GenerationSettings(
		DEFAULT_SEED, 
		GenerationSettings::NOISE_PERLIN_BASIC,
		GenerationSettings::NoiseGenerationSettings{ .octaves = 4, .frequency = 0.1f, .persistance = 0.5f }
	));

	generationMaster.generate();
}

World::World(World&& other) noexcept {
	if (other.m_field[0] != m_field[0]) { // Not the same/broken world
		memcpy(this, &other, sizeof(World));
		memset(&other, 0, sizeof(World));
	}
}

World::~World() {
	if (m_field[0]) {
		delete[] m_field[0];
		delete[] m_field[1];

		m_field[0] = m_field[1] = nullptr;
	}
}

World& World::operator=(World&& other) noexcept {
	if (other.m_field[0] != m_field[0]) { // Not the same/broken world
		this->~World();

		memcpy(this, &other, sizeof(World));
		memset(&other, 0, sizeof(World));
	}

	return *this;
}

void World::update(Player& player, float deltaTime) {
	math::Vector2i updateFrom = (-m_size).getMaxByXY(player.getPos().roundFloor().template to<int32_t>() - GlobalSettings::get().getUpdateDistance());
	math::Vector2i updateTo = m_size.getMinByXY(player.getPos().roundFloor().template to<int32_t>() + GlobalSettings::get().getUpdateDistance());

	for (uint8_t layer = 0; layer <= 1; layer++) {
		for (int32_t y = updateFrom.y(); y <= updateTo.y(); y++) {
			for (int32_t x = updateFrom.x(); x <= updateTo.x(); x++) {
				if (at(layer, { x, y }).isInteractive()) {
					atMut(layer, { x, y }).getTileData()->update(math::Vector2f(x, y), *this, player);
				}
			}
		}
	}
}

void World::draw(RenderMaster& renderMaster, Camera& camera) {
	math::Vector2i from = math::Vector2i(camera.viewTopLeft()).getMaxByXY(-m_size);
	math::Vector2i to = math::Vector2i(camera.viewDownRight() + 1).getMinByXY(m_size);

	if (!from.isToUpLeftFrom(to)) {
		return;
	}

	for (uint8_t layer = 0; layer <= 1; layer++) {
		for (int32_t y = from.y(); y <= to.y(); y++) {
			for (int32_t x = from.x(); x <= to.x(); x++) {
				if (const Tile& tile = at(layer, { x, y }); tile.isVisible()) {
					renderMaster.drawTile(tile.getId(), layer, math::Vector2f(x, y));
				}
			}
		}
	}
}

void World::fillArea(const math::Recti& rect, bool isForeground, TileId id) {
	const math::Vector2i& from = rect.topLeft();
	const math::Vector2i& to = rect.downRight();

	assert(from.isToDownRightFrom(-m_size));
	assert(to.isToUpLeftFrom(m_size));

	for (int32_t y = from.y(); y <= to.y(); y++) {
		for (int32_t x = from.x(); x <= to.x(); x++) {
			atMut(isForeground, { x, y }) = Tile(id);
		}
	}
}

const math::Vector2i& World::getSize() const {
	return m_size;
}

math::Vector2i World::getNearestPassableLocation(const math::Vector2i& from) const noexcept {
	if (!isObstacleAt(from)) {
		return from;
	}

	auto tryLookInRange = [this](const math::Vector2i& from, math::Vector2i& to, const math::Vector2i& step) -> bool {
		while (to != from) {
			if (!isObstacleAt(to)) {
				return true;
			}

			to -= step;
		}

		return false;
	};

	math::Vector2i topLeft = from;
	math::Vector2i downRight = from;

	while (topLeft.isToDownRightFrom<true>(-m_size) || downRight.isToUpLeftFrom<true>(m_size)) {
		if (topLeft.x() > -m_size.x()) {
			--topLeft.x();
			if (math::Vector2i to { topLeft.x(), downRight.y() }; tryLookInRange(topLeft, to, { 0, 1 })) {
				return to;
			}
		} if (topLeft.y() > -m_size.y()) {
			--topLeft.y();
			if (math::Vector2i to { downRight.x(), topLeft.y() }; tryLookInRange(topLeft, to, { 1, 0 })) {
				return to;
			}
		}

		if (downRight.x() < m_size.x()) {
			++downRight.x();
			if (math::Vector2i to { topLeft.x(), downRight.y() }; tryLookInRange(downRight, to, { -1, 0 })) {
				return to;
			}
		} if (downRight.y() < m_size.y()) {
			++downRight.y();
			if (math::Vector2i to { downRight.x(), topLeft.y() }; tryLookInRange(downRight, to, { 0, -1 })) {
				return to;
			}
		}
	}

	return from;
}

math::Vector2i World::getRandomLocation() const noexcept {
	return math::Vector2i {
		utils::Random<>::rand(-m_size.x() + 1, m_size.x() - 1), 
		utils::Random<>::rand(-m_size.y() + 1, m_size.y() - 1) 
	};
}

math::Vector2i World::getRandomPassableLocation() const noexcept {
	return getNearestPassableLocation(getRandomLocation());
}

bool World::isObstacleAt(const math::Vector2i& pos) const {
	return at(0, pos).isObstacle() || at(1, pos).isObstacle();
}

const Tile& World::at(bool isForeground, const math::Vector2i& pos) const {
	static Tile s_emptyTile = Tile(TileId::EMPTINESS);

	if (pos.abs().isToUpLeftFrom(m_size)) {
		return m_fieldCenter[isForeground][pos.y() * int32_t(m_width) + pos.x()];
	} else {
		return s_emptyTile;
	}
}

Tile& World::atMut(bool isForeground, const math::Vector2i& pos) {
	assert(pos.abs().isToUpLeftFrom(m_size));

	return m_fieldCenter[isForeground][pos.y() * int32_t(m_width) + pos.x()];
}

Tile& World::atMutBackground(const math::Vector2i& pos) {
	return atMut(0, pos);
}

Tile& World::atMutForeground(const math::Vector2i& pos) {
	return atMut(1, pos);
}
