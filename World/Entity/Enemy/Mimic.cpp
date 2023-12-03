// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Mimic.h"

Mimic::Mimic(const math::Vector2f& pos, World& pWorld)
	: Enemy(1.f, 1.5f, 2.f, EntityId::MIMIC, pos, pWorld) {
	setImmortalMode(true);
}
