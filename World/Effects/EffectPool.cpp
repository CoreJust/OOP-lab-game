// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EffectPool.h"
#include "ContinuousEffect.h"
#include "World/World.h"
#include "World/Entity/Entity.h"
#include "IO/Logger/Logger.h"
#include "GlobalSettings.h"

EffectPool::EffectPool(Entity& pEntity, World& pWorld) noexcept
	: m_pEntity(pEntity), m_pWorld(pWorld) {

}

EffectPool& EffectPool::operator=(const EffectPool& other) {
	m_effects = other.m_effects;

	return *this;
}

EffectPool& EffectPool::operator=(EffectPool&& other) {
	m_effects = std::move(other.m_effects);

	return *this;
}

void EffectPool::update(const float deltaTime) {
	for (id_t id = 0; id < EffectId::NUMBER_EFFECT_IDS; id++) {
		for (auto it = m_effects[id].begin(); it != m_effects[id].end(); ++it) {
			if ((*it)->update(m_pEntity, m_pWorld, deltaTime)) {
				it = m_effects[id].erase(it);

				if (it == m_effects[id].end()) {
					break;
				}
			}
		}
	}
}

void EffectPool::pushEffect(std::shared_ptr<Effect> effect) {
	const EffectId id = effect->getId();
	if (!id.isInstant()) {
		const float level = effect->getLevel();
		auto& lst = m_effects[id];
		ContinuousEffect* asCE = (ContinuousEffect*)effect.get();

		for (auto it = lst.begin(); it != lst.end(); it++) {
			ContinuousEffect* ce = (ContinuousEffect*)it->get();
			if (ce->getLevel() == level) {
				if (ce->getTimeLeft() < asCE->getTimeLeft()) {
					ce->setTime(asCE->getTimeLeft());
					return;
				}
			}
		}
	}

	if (GlobalSettings::get().isToLogEntitiesEffects()) {
		io::Logger::info("EffectPool: " + effect->toString() + " put on " + m_pEntity.toString());
		// MESSAGE
	}

	m_effects[id].push_front(std::move(effect));
}
