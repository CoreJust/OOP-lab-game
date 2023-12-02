// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EvilSpirit.h"
#include "World/Effects/ContinuousEffect.h"
#include "Audio/AudioMaster.h"

EvilSpirit::EvilSpirit(const math::Vector2f& pos, World& pWorld)
	: Enemy(1.5f, 3.f, 4.f, EntityId::EVIL_SPIRIT, pos, pWorld) {
	setSpiritualMode(true);
}

void EvilSpirit::onAttack(World& world, Player& player) {
	player.dealDamage(m_health);
	player.getEffectPoolMut().pushEffect(std::make_shared<ContinuousEffect>(EffectId::BLINDNESS, 1.f, 20.f));

	audio::AudioMaster::playSound(audio::SoundId::SOUND_HIT);
	audio::AudioMaster::playSound(audio::SoundId::SOUND_EVIL_SPIRIT_EXPLOSION);

	m_health = 0.f;
}
