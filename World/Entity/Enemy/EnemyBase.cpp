// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EnemyBase.h"
#include "World/Effects/ContinuousEffect.h"
#include "World/Effects/PeriodicalEffect.h"
#include "Audio/AudioMaster.h"

EnemyBase::EnemyBase(EnemyBehaviour behaviour, const EntityId id, const math::Vector2f& pos, World& pWorld) noexcept 
	: Entity(pos, id, pWorld), m_behaviour(std::move(behaviour)) { }

void EnemyBase::onAttack(World& world, Player& player) {
	player.dealDamage(m_stats.power);
	audio::AudioMaster::playSound(audio::SoundId::SOUND_HIT);

	switch (getBehaviour().getInteractionPolicy()) {
		case EnemyPlayerInteractionPolicy::NORMAL_HIT:
			return;
		case EnemyPlayerInteractionPolicy::POISONING:
			player.getEffectPoolMut().pushEffect(std::make_shared<PeriodicalEffect>(EffectId::CONTINUOUS_DAMAGE));
			audio::AudioMaster::playSound(audio::SoundId::SOUND_POISONING);
			return;
		case EnemyPlayerInteractionPolicy::SHOCKING:
			player.getEffectPoolMut().pushEffect(std::make_shared<ContinuousEffect>(EffectId::DECCELERATION, 3.f, 5.f));
			player.getEffectPoolMut().pushEffect(std::make_shared<ContinuousEffect>(EffectId::BLINDNESS, 1.f, 5.f));
			audio::AudioMaster::playSound(audio::SoundId::SOUND_SHOCK);
			return;
	default: return;
	}
}
