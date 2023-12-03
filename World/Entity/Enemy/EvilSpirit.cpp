// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EvilSpirit.h"
#include "World/Effects/ContinuousEffect.h"
#include "Audio/AudioMaster.h"

EvilSpirit::EvilSpirit(const math::Vector2f& pos, World& pWorld)
	: Enemy(1.5f, 3.f, 4.f, EntityId::EVIL_SPIRIT, pos, pWorld) {
	setSpiritualMode(true);
}
