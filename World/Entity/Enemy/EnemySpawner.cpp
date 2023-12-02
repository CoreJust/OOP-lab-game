// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EnemySpawner.h"
#include "Ghost.h"
#include "EvilSpirit.h"
#include "LostInMaze.h"
#include "VenomousPlant.h"

EnemySpawner::EnemySpawner(World& pWorld) noexcept
	: m_pWorld(pWorld) {

}

std::unique_ptr<EnemyController> EnemySpawner::spawn(const EntityId id, const math::Vector2f& pos) {
	std::unique_ptr<EnemyBase> enemy;
	switch (id) {
		case EntityId::GHOST: enemy = std::make_unique<Ghost>(pos, m_pWorld); break;
		case EntityId::EVIL_SPIRIT: enemy = std::make_unique<EvilSpirit>(pos, m_pWorld); break;
		case EntityId::LOST_IN_MAZE: enemy = std::make_unique<LostInMaze>(pos, m_pWorld); break;
		case EntityId::VENOMOUS_PLANT: enemy = std::make_unique<VenomousPlant>(pos, m_pWorld); break;
		default: return nullptr;
	}

	return std::make_unique<EnemyController>(std::move(enemy), m_pWorld);
}
