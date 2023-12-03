// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EnemyBase.h"
#include "World/Effects/ContinuousEffect.h"
#include "World/Effects/PeriodicalEffect.h"
#include "Audio/AudioMaster.h"

EnemyBase::EnemyBase(EnemyBehaviour behaviour, const EntityId id, const math::Vector2f& pos, World& pWorld) noexcept 
	: Entity(pos, id, pWorld), m_behaviour(std::move(behaviour)) { }

void EnemyBase::onAttack(World& world, Player& player) {
	player.dealDamageToPlayer(m_stats.power, m_id);
	audio::AudioMaster::playSound(audio::SoundId::SOUND_HIT);

	switch (getBehaviour().getInteractionPolicy()) {
		case EnemyPlayerInteractionPolicy::NORMAL_HIT:
			return;
		case EnemyPlayerInteractionPolicy::POISONING:
			player.getEffectPoolMut().pushEffect(std::make_shared<PeriodicalEffect>(EffectId::CONTINUOUS_DAMAGE, 2.f, 25.f, 3.5f));
			audio::AudioMaster::playSound(audio::SoundId::SOUND_POISONING);
			return;
		case EnemyPlayerInteractionPolicy::SHOCKING:
			player.getEffectPoolMut().pushEffect(std::make_shared<ContinuousEffect>(EffectId::DECCELERATION, 3.f, 5.f));
			player.getEffectPoolMut().pushEffect(std::make_shared<ContinuousEffect>(EffectId::BLINDNESS, 1.f, 5.f));
			audio::AudioMaster::playSound(audio::SoundId::SOUND_SHOCK);
			return;
		case EnemyPlayerInteractionPolicy::SELF_DESTRUCT:
			player.dealDamageToPlayer(m_health, m_id);
			player.getEffectPoolMut().pushEffect(std::make_shared<ContinuousEffect>(EffectId::BLINDNESS, 1.f, 20.f));

			audio::AudioMaster::playSound(audio::SoundId::SOUND_HIT);
			audio::AudioMaster::playSound(audio::SoundId::SOUND_EVIL_SPIRIT_EXPLOSION);

			m_health = 0.f;
			return;
	default: return;
	}
}
