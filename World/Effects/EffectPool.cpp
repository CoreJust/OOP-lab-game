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
	for (auto it = m_effects.begin(); it != m_effects.end(); ++it) {
		if ((*it)->update(m_pEntity, m_pWorld, deltaTime)) {
			it = m_effects.erase(it);

			if (it == m_effects.end()) {
				break;
			}
		}
	}
}

void EffectPool::pushEffect(std::shared_ptr<Effect> effect) {
	if (effect->getId() == EffectId::IMMORTALITY 
		|| effect->getId() == EffectId::SPIRITUAL_FORM 
		|| effect->getId() == EffectId::INVISIBILITY) {
		for (auto& e : m_effects) {
			if (e->getId() == effect->getId()) {
				((ContinuousEffect*)e.get())->updateTime(*(ContinuousEffect*)effect.get());

				return;
			}
		}
	}

	if (GlobalSettings::get().isToLogEntitiesEffects()) {
		io::Logger::info("EffectPool: " + effect->toString() + " put on " + m_pEntity.toString());
		// MESSAGE
	}

	m_effects.push_front(std::move(effect));
}
