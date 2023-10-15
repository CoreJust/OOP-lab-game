// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PostGenGenerator.h"
#include "Math/WaveFrontWalker.h"

void PostGenGenerator::generateInitial() {
	assert(false && "Cannot start generation with postgen");
}

void PostGenGenerator::generate() {
	if (m_sets.flags == GenerationSettings::POSTGEN_PASSAGE_CREATOR) {
		createPassages();
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
