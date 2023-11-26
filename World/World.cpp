// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "World.h"
#include "IO/Logger/Logger.h"
#include "Utils/Random.h"
#include "Math/Rasterizer/LineRasterizer.h"
#include "GlobalSettings.h"
#include "Entity/Player.h"
#include "Generator/WorldGenerationMaster.h"

constexpr math::Vector2i MINIMAL_WORLD_SIZE { 1, 1 }; // 3x3

World::World() : World(WorldLevelId::BASIC_LEVEL) { }

World::World(const math::Vector2i& size) : m_mapper(size) {
	if (!MINIMAL_WORLD_SIZE.isToUpLeftFrom(size)) {
		io::Logger::error("World: too small of a size for a world: " + size.toString());
	}

	// Initializing field
	m_field[0] = new Tile[m_mapper.getArea()];
	m_field[1] = new Tile[m_mapper.getArea()];

	m_fieldCenter[0] = m_field[0] + m_mapper.getActualCenterIndex();
	m_fieldCenter[1] = m_field[1] + m_mapper.getActualCenterIndex();

	fillArea({ -m_mapper.getSize(), m_mapper.getSize() }, 0, TileId::EMPTINESS);
	fillArea({ -m_mapper.getSize(), m_mapper.getSize() }, 1, TileId::EMPTINESS);
}

World::World(WorldLevelId id) : World(id.getWorldSize()) {
	// Generation
	WorldGenerationMaster generationMaster(*this);
	id.loadGenerationSettingsTo(generationMaster);
	generationMaster.generate();
}

World::World(const World& other) : World(other.getSize()) {
	for (const math::Vector2i& pos : m_mapper.getRect()) {
		atMut(0, pos) = other.at(0, pos);
		atMut(1, pos) = other.at(1, pos);
	}
}

World::World(World&& other) noexcept {
	if (other.m_field[0] != m_field[0]) { // Not the same/broken world
		memmove(this, &other, sizeof(World));
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

World& World::operator=(const World& other) {
	if (this == &other) {
		return *this;
	}

	this->~World();

	m_mapper.setSize(other.getSize());

	if (!MINIMAL_WORLD_SIZE.isToUpLeftFrom(getSize())) {
		io::Logger::error("World: too small of a size for a world: " + getSize().toString());
	}

	// Initializing field
	m_field[0] = new Tile[m_mapper.getArea()];
	m_field[1] = new Tile[m_mapper.getArea()];

	m_fieldCenter[0] = m_field[0] + m_mapper.getActualCenterIndex();
	m_fieldCenter[1] = m_field[1] + m_mapper.getActualCenterIndex();

	fillArea({ -m_mapper.getSize(), m_mapper.getSize() }, 0, TileId::EMPTINESS);
	fillArea({ -m_mapper.getSize(), m_mapper.getSize() }, 1, TileId::EMPTINESS);

	// Copying the tiles
	for (const math::Vector2i& pos : m_mapper.getRect()) {
		atMut(0, pos) = other.at(0, pos);
		atMut(1, pos) = other.at(1, pos);
	}

	return *this;
}

World& World::operator=(World&& other) noexcept {
	if (other.m_field[0] != m_field[0]) { // Not the same/broken world
		this->~World();

		memmove(this, &other, sizeof(World));
		memset(&other, 0, sizeof(World));
	}

	return *this;
}

void World::update(Player& player, float deltaTime) {
	math::Vector2i updateFrom = (-m_mapper.getSize()).getMaxByXY(player.getPos().roundFloor().template to<int32_t>() - GlobalSettings::get().getUpdateDistance());
	math::Vector2i updateTo = m_mapper.getSize().getMinByXY(player.getPos().roundFloor().template to<int32_t>() + GlobalSettings::get().getUpdateDistance());
	math::Recti updateRect { updateFrom, updateTo };

	for (uint8_t layer = 0; layer <= 1; layer++) {
		for (const math::Vector2i& pos : updateRect) {
			if (at(layer, pos).isInteractive()) {
				atMut(layer, pos).getTileData()->update(pos.to<float>(), *this, player, deltaTime);
			}
		}
	}
}

void World::draw(RenderMaster& renderMaster, Camera& camera) {
	math::Vector2i from = math::Vector2i(camera.viewTopLeft().roundFloor()).getMaxByXY(-m_mapper.getSize());
	math::Vector2i to = math::Vector2i(camera.viewDownRight().roundCeil()).getMinByXY(m_mapper.getSize());

	if (!from.isToUpLeftFrom(to)) {
		return;
	}

	math::Recti drawRect { from, to };
	for (uint8_t layer = 0; layer <= 1; layer++) {
		for (const math::Vector2i& pos : drawRect) {
			if (const Tile& tile = at(layer, pos); tile.isVisible()) {
				renderMaster.drawTile(tile.getId(), pos.to<float>(), getVNSFor(pos));
			}
		}
	}
}

void World::fillArea(const math::Recti& rect, bool isForeground, TileId id) {
	const math::Vector2i& from = rect.topLeft();
	const math::Vector2i& to = rect.downRight();

	assert(from.isToDownRightFrom(-m_mapper.getSize()));
	assert(to.isToUpLeftFrom(m_mapper.getSize()));

	math::Recti fillRect { from, to };
	for (const math::Vector2i& pos : fillRect) {
		atMut(isForeground, pos) = Tile(id);
	}
}

void World::fillAreaBounds(const math::Recti& rect, bool isForeground, TileId id) {
	math::Vector2i topRight { rect.right(), rect.top() };
	math::Vector2i downLeft { rect.left(), rect.down() };

	fillArea({ rect.topLeft(), topRight },							isForeground, id);
	fillArea({ rect.topLeft() + math::Vector2i(0, 1), downLeft },	isForeground, id);
	fillArea({ topRight + math::Vector2i(0, 1), rect.downRight() }, isForeground, id);
	fillArea({ downLeft + math::Vector2i(1, 0),
			 rect.downRight() + math::Vector2i(-1, 0) },			isForeground, id);
}

void World::makeTunnel(const math::Vector2i& from, const math::Vector2i& to, TileId floorId) {
	math::LineRasterizer rasterizer(from.to<float>(), to.to<float>());

	while (rasterizer.hasMore()) {
		for (int32_t x = rasterizer.leftX(); x <= rasterizer.rightX(); x++) {
			makePassable({ x, rasterizer.getY() }, floorId);
		}

		rasterizer.nextRow();
	}
}

void World::makePassable(const math::Vector2i& pos, TileId floorId) {
	if (at(1, pos).isObstacle()) {
		atMut(1, pos) = Tile(TileId::EMPTINESS);
	}

	if (at(0, pos).isObstacle()) {
		atMut(0, pos) = Tile(floorId);
	}
}

const math::Vector2i& World::getSize() const {
	return m_mapper.getSize();
}

const math::Vector2u& World::getActualSize() const {
	return m_mapper.getActualSize();
}

const math::Mapper<>& World::getMapper() const {
	return m_mapper;
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

	const int32_t sizeX = m_mapper.getSize().x();
	const int32_t sizeY = m_mapper.getSize().y();

	while (topLeft.isToDownRightFrom<true>(-m_mapper.getSize()) || downRight.isToUpLeftFrom<true>(m_mapper.getSize())) {
		if (topLeft.x() > -sizeX) {
			--topLeft.x();
			if (math::Vector2i to { topLeft.x(), downRight.y() }; tryLookInRange(topLeft, to, { 0, 1 })) {
				return to;
			}
		} if (topLeft.y() > -sizeY) {
			--topLeft.y();
			if (math::Vector2i to { downRight.x(), topLeft.y() }; tryLookInRange(topLeft, to, { 1, 0 })) {
				return to;
			}
		}

		if (downRight.x() < sizeX) {
			++downRight.x();
			if (math::Vector2i to { topLeft.x(), downRight.y() }; tryLookInRange(downRight, to, { -1, 0 })) {
				return to;
			}
		} if (downRight.y() < sizeY) {
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
		utils::Random<>::rand(-m_mapper.getSize().x() + 1, m_mapper.getSize().x() - 1),
		utils::Random<>::rand(-m_mapper.getSize().y() + 1, m_mapper.getSize().y() - 1)
	};
}

math::Vector2i World::getRandomPassableLocation() const noexcept {
	return getNearestPassableLocation(getRandomLocation());
}

math::DirectionFlag World::getVNSFor(const math::Vector2i& pos) {
	// A note: in regard of the walls, the out-of-bounds-area is considered not as emptiness but something
	// It is made this way because otherwise the bounding walls would have been rendered, thus looking unnatural

	if (pos.isToDownRightFrom((m_mapper.getSize() + 1).abs())) { // Out of bounds
		return math::DirectionFlag::ALL_DIRECTIONS;
	}

	uint8_t result = math::DirectionFlag::ALL_DIRECTIONS;
	auto check = [&result, &pos, this](math::DirectionFlag flag) {
		math::Vector2i offset = math::Direction<int32_t>::getDirectionVector(flag);
		if ((m_mapper.contains(pos + offset) && at(false, pos + offset).getCategory() != TileCategory::WALL)) {
			result ^= flag;
		}
	};

	check(math::DirectionFlag::UP);
	check(math::DirectionFlag::DOWN);
	check(math::DirectionFlag::RIGHT);
	check(math::DirectionFlag::LEFT);

	assert(result <= math::DirectionFlag::ALL_DIRECTIONS);

	return math::DirectionFlag(result);
}

bool World::isObstacleAt(const math::Vector2i& pos) const {
	return at(0, pos).isObstacle() || at(1, pos).isObstacle();
}

const Tile& World::at(bool isForeground, const math::Vector2i& pos) const {
	static Tile s_emptyTile = Tile(TileId::EMPTINESS);

	if (m_mapper.contains(pos)) {
		return m_fieldCenter[isForeground][m_mapper.getIndex(pos)];
	} else {
		return s_emptyTile;
	}
}

Tile& World::atMut(bool isForeground, const math::Vector2i& pos) {
	return m_fieldCenter[isForeground][m_mapper.getIndex(pos)];
}

Tile& World::atMutBackground(const math::Vector2i& pos) {
	return atMut(0, pos);
}

Tile& World::atMutForeground(const math::Vector2i& pos) {
	return atMut(1, pos);
}
