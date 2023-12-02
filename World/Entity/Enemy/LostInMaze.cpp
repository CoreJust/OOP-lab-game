// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "LostInMaze.h"

LostInMaze::LostInMaze(const math::Vector2f& pos, World& pWorld)
	: Enemy(1.f, 10.f, 15.f, EntityId::LOST_IN_MAZE, pos, pWorld) {

}
