// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EffectGiverTileData.h"

EffectGiverTileData::EffectGiverTileData(std::vector<std::shared_ptr<Effect>> effects, const float activationRadius)
	: m_effects(std::move(effects)), m_activationRadius(activationRadius) {

}

void EffectGiverTileData::update(math::Vector2f pos, World& world, Player& player) {
	if (pos.distance(player.getPos()) <= m_activationRadius) {
		for (auto& e : m_effects) {
			player.getEffectPoolMut().pushEffect(e->copy());
		}
	}
}

std::unique_ptr<TileData> EffectGiverTileData::copy() {
	return std::make_unique<EffectGiverTileData>(m_effects, m_activationRadius);
}
