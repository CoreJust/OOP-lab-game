// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EffectGiverTileData.h"

EffectGiverTileData::EffectGiverTileData(std::vector<std::shared_ptr<Effect>> effects, const float coolDown)
	: m_effects(std::move(effects)), m_coolDown(coolDown) {

}

void EffectGiverTileData::update(math::Vector2f pos, World& world, Player& player, const float deltaTime) {
	if (m_coolDownTimer > 0.f) {
		m_coolDownTimer -= deltaTime;
	}
}

void EffectGiverTileData::onStep(math::Vector2f pos, World& world, Entity& entity) {
	if (m_coolDownTimer <= 0.f) {
		for (auto& e : m_effects) {
			entity.getEffectPoolMut().pushEffect(e->copy());
			m_coolDownTimer = m_coolDown;
		}
	}
}

std::unique_ptr<TileData> EffectGiverTileData::copy() {
	return std::make_unique<EffectGiverTileData>(m_effects, m_coolDown);
}
