// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "World/Entity/EntityController.h"
#include "EnemyBase.h"

/*
*	EnemyController(.h/.cpp) contains a class that is responsible for controlling an enemy.
*/

class Player;

class EnemyController : public EntityController {
private:
	math::Vector2f m_attractionPoint; // The current destination of the enemy
	float m_attackCooldown = 0.f;

public:
	EnemyController(std::unique_ptr<EnemyBase> enemy, World& pWorld);

	void update(const float deltaTime, Player& player);
	void draw(RenderMaster& renderMaster) override;

	EnemyBase& getEnemy();
	EnemyBehaviour& getBehaviour();

private:
	void attackPlayer(const float deltaTime, Player& player);
};