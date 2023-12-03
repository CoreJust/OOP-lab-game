// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Chest.h"
#include "Audio/AudioMaster.h"

Chest::Chest(const math::Vector2f& pos, World& pWorld)
	: Enemy(1.f, 0.f, 0.f, EntityId::CHEST, pos, pWorld) {
	setImmortalMode(true);
}

void Chest::onAttack(World& world, Player& player) {
	player.stats().maxHealth += m_stats.maxHealth;
	player.stats().defence += m_stats.defence;
	player.stats().speed += m_stats.speed;
	player.stats().agility += m_stats.agility;
	player.stats().power += m_stats.power;

	player.heal(m_stats.maxHealth * 5.f);

	audio::AudioMaster::playSound(audio::SoundId::SOUND_SAINT_SPRINGS_BUFF);

	m_health = 0.f;
}
