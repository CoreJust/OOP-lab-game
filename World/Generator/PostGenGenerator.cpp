// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PostGenGenerator.h"
#include "Math/WaveFrontWalker.h"
#include "IO/Logger.h"
#include "Utils/Random.h"
#include "Math/ChanceDistribution.h"

void PostGenGenerator::generateInitial() {
	assert(false && "Cannot start generation with postgen");
}

void PostGenGenerator::generate() {
	if (m_sets.flags == GenerationSettings::POSTGEN_PASSAGE_CREATOR) {
		createPassages();
	} else if (m_sets.flags == GenerationSettings::POSTGEN_BOUNDS_CREATOR) {
		createBounds();
	} else if (m_sets.flags == GenerationSettings::POSTGEN_DECORATOR) {
		createDecorations();
	}
}

constexpr int32_t UNMARKED_CLUSTER = 0; // for passable cluster that are yet to be marked
constexpr int32_t WALL_CLUSTER = -1; // for walls

void PostGenGenerator::createPassages() {
	const math::Mapper<>& mapper = m_pWorld.getMapper();
	std::vector<int32_t> map(mapper.getArea(), 0);

	// Marking walls and passables
	for (const math::Vector2i& pos : mapper.getRect()) {
		int32_t index = mapper.getIndex<math::Mapper<>::CORNER_COORDS, math::Mapper<>::CENTER_COORDS>(pos);
		if (m_pWorld.isObstacleAt(pos)) {
			map[index] = WALL_CLUSTER;
		} else {
			map[index] = UNMARKED_CLUSTER;
		}
	}

	uint32_t clustersCount = clusterWorldCavities(map);

	if (clustersCount > 1) {
		makePassages(map, clustersCount);
	}
}

void PostGenGenerator::createBounds() {
	const math::Vector2i size = m_pWorld.getSize();

	m_pWorld.fillArea({ -size, size.mirrorByX() }, 0, TileId::STONE_WALL);
	m_pWorld.fillArea({ -size, size.mirrorByY() }, 0, TileId::STONE_WALL);
	m_pWorld.fillArea({ size.mirrorByX(), size }, 0, TileId::STONE_WALL);
	m_pWorld.fillArea({ size.mirrorByY(), size }, 0, TileId::STONE_WALL);
}

constexpr float STONE_CHANCE = 0.05f;
constexpr float SPRINGS_CHANCE = 0.01f;
constexpr float POISON_CHANCE = 0.055f;
constexpr float PORTAL_CHANCE = 0.035f;

void PostGenGenerator::createDecorations() {
	utils::Random random;
	random.setSeed(m_sets.seed);

	math::ChanceDistribution<decltype(random)::RG, TileId> chanceDist(random, TileId::STONE_FLOOR);
	chanceDist.push(STONE_CHANCE, TileId::STONE);
	chanceDist.push(SPRINGS_CHANCE, TileId::SAINT_SPRINGS);
	chanceDist.push(POISON_CHANCE, TileId::POISON_CLOUD);
	size_t portalChanceIndex = chanceDist.push(PORTAL_CHANCE, TileId::STONE_PORTAL);

	const math::Vector2i size = m_pWorld.getSize();
	uint32_t portalsCount = 0;

	const math::Recti genRect { -size + 1, size - 1 };
	for (const math::Vector2i& pos : genRect) {
		Tile& tile = m_pWorld.atMutBackground(pos);
		Tile& tileFront = m_pWorld.atMutForeground(pos);

		if (!tile.isObstacle()) { // Floor
			TileId id = chanceDist.pick();
			if (id == TileId::STONE_PORTAL) {
				chanceDist.setChance(portalChanceIndex, PORTAL_CHANCE * (3.f / float(portalsCount++ + 3)));
			}

			if (id.isBackground()) {
				tile = Tile(id);
			} else {
				tile = Tile(TileId::STONE_FLOOR);
				tileFront = Tile(id);
			}
		} else { // Wall

		}
	}

	// Next level portal
	math::Vector2i nextLevelPortalPos = m_pWorld.getRandomPassableLocation();
	m_pWorld.atMut(1, nextLevelPortalPos) = Tile(TileId::NEXT_LEVEL_PORTAL);
	io::Logger::logInfo("Generated next level portal at: " + nextLevelPortalPos.toString());
}

uint32_t PostGenGenerator::clusterWorldCavities(std::vector<int32_t>& map) {
	// Clustering
	uint32_t count = 0;
	const math::Mapper<>& mapper = m_pWorld.getMapper();

	auto walkerCondition = [&mapper, &map](const math::Vector2i& pos) -> bool {
		if (!mapper.contains<math::Mapper<>::CORNER_COORDS>(pos)) {
			return false;
		}

		int32_t index = mapper.getCornerIndex(pos);
		return map[index] == UNMARKED_CLUSTER;
	};

	for (const math::Vector2i& pos : mapper.getActualRect().clip(1).to<int32_t>()) {
		int32_t index = mapper.getCornerIndex(pos);

		if (map[index] == UNMARKED_CLUSTER) {
			math::WaveFrontWalker<decltype(walkerCondition), false> walker(pos, walkerCondition);
			math::Vector2i walkerPos;

			++count;
			while (walker.next(walkerPos)) {
				int32_t index = mapper.getCornerIndex(walkerPos);
				map[index] = count;
			}
		}
	}

	return count;
}

void PostGenGenerator::makePassages(std::vector<int32_t>& map, uint32_t clusterCount) {
	constexpr static math::Recti s_NoRect = math::Recti({ -1, -1 }, { -1, -1 });

	// First we measure the clusters' size
	std::vector<math::Vector2i> clusterCenters;
	std::vector<math::Recti> clusterRects;
	clusterCenters.resize(clusterCount);
	clusterRects.resize(clusterCount, s_NoRect);

	const math::Mapper<>& mapper = m_pWorld.getMapper();
	for (const math::Vector2i& pos : mapper.getActualRect().clip(1).to<int32_t>()) {
		int32_t index = mapper.getCornerIndex(pos);
		if (map[index] > 0) { // Part of a cluster
			math::Recti& rect = clusterRects[map[index] - 1];

			if (rect == s_NoRect) {
				rect = math::Recti(pos.to<int32_t>(), pos.to<int32_t>());
			} else {
				rect.topLeft() = rect.topLeft().getMinByXY(pos);
				rect.downRight() = rect.downRight().getMaxByXY(pos);
			}
		}
	}

	// Now we look for clusters' centermost passable tile and connect them
	for (uint32_t clusterId = 0; clusterId < clusterCount; clusterId++) {
		clusterCenters[clusterId] = mapper.remapCoords<math::Mapper<>::CORNER_COORDS>(clusterRects[clusterId].getCenter());
		clusterCenters[clusterId] = m_pWorld.getNearestPassableLocation(clusterCenters[clusterId]);

		if (clusterId != 0) {
			m_pWorld.makeTunnel(clusterCenters[clusterId - 1], clusterCenters[clusterId], TileId::STONE_FLOOR);
		}
	}
}
