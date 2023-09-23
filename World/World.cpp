#include "World.h"

void World::initFor(const utils::Vector2u& worldSizeFromCenter) {
	m_size = utils::Vector2i(worldSizeFromCenter);
	m_width = 2 * m_size.x() + 1;
	m_height = 2 * m_size.y() + 1;

	m_field[0] = new Tile[size_t(m_width) * m_height];
	m_field[1] = new Tile[size_t(m_width) * m_height];

	m_fieldCenter[0] = m_field[0] + m_size.y() * m_width + m_size.x();
	m_fieldCenter[1] = m_field[1] + m_size.y() * m_width + m_size.x();
}

World::World(const utils::Vector2u& worldSizeFromCenter) {
	initFor(worldSizeFromCenter);

	fillArea(-m_size + 1, m_size - 1, false, TileId::STONE_FLOOR);

	fillArea(-m_size, m_size.mirrorByX(), false, TileId::STONE_WALL);
	fillArea(-m_size, m_size.mirrorByY(), false, TileId::STONE_WALL);
	fillArea(m_size.mirrorByX(), m_size, false, TileId::STONE_WALL);
	fillArea(m_size.mirrorByY(), m_size, false, TileId::STONE_WALL);
}

World::~World() {
	if (m_field[0]) {
		delete[] m_field[0];
		delete[] m_field[1];

		m_field[0] = m_field[1] = nullptr;
	}
}

void World::update(Player& player, float deltaTime) {
	for (int layer = 0; layer <= 1; layer++) {
		for (int32_t y = -m_size.y(); y <= m_size.y(); y++) {
			for (int32_t x = -m_size.x(); x <= m_size.x(); x++) {
				if (at(layer, { x, y }).isInteractive()) {
					at(layer, { x, y }).getTileData()->update(utils::Vector2f(x, y), this, &player);
				}
			}
		}
	}
}

void World::draw(RenderMaster& renderMaster, Camera& camera) {
	utils::Vector2i from = utils::Vector2i(camera.viewTopLeft()).getMaxByXY(-m_size);
	utils::Vector2i to = utils::Vector2i(camera.viewDownRight() + 1).getMinByXY(m_size);

	if (!from.isToLeftUpFrom(to)) {
		return;
	}

	for (int layer = 0; layer <= 1; layer++) {
		for (int32_t y = from.y(); y <= to.y(); y++) {
			for (int32_t x = from.x(); x <= to.x(); x++) {
				if (Tile& tile = at(layer, { x, y }); tile.isVisible()) {
					renderMaster.drawTile(tile.getId(), layer, utils::Vector2f(x, y));
				}
			}
		}
	}
}

void World::fillArea(const utils::Vector2i& from, const utils::Vector2i& to, bool isForeground, TileId id) {
	assert(from.isToDownRightFrom(-m_size));
	assert(to.isToLeftUpFrom(m_size));

	if (!from.isToLeftUpFrom(to)) {
		return;
	}

	for (int32_t y = from.y(); y <= to.y(); y++) {
		for (int32_t x = from.x(); x <= to.x(); x++) {
			at(isForeground, { x, y }) = Tile(id);
		}
	}
}

bool World::isObstacleAt(const utils::Vector2i& pos) {
	if (pos.abs().isToDownRightFrom<true>(m_size)) {
		return false;
	}

	return atBackground(pos).isObstacle() || atForeground(pos).isObstacle();
}

Tile& World::at(bool isForeground, const utils::Vector2i& pos) {
	assert(pos.abs().isToLeftUpFrom(m_size));

	return m_fieldCenter[isForeground][pos.y() * int32_t(m_width) + pos.x()];
}

Tile& World::atBackground(const utils::Vector2i& pos) {
	return at(0, pos);
}

Tile& World::atForeground(const utils::Vector2i& pos) {
	return at(1, pos);
}
