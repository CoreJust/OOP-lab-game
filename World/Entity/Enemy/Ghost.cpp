// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Ghost.h"

Ghost::Ghost(const math::Vector2f& pos, World& pWorld) 
	: Enemy(1.f, 10.f, 16.f, EntityId::GHOST, pos, pWorld) {
	setSpiritualMode(true);
}
