// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "../TileData.h"
#include "World/World.h"
#include "World/Entity/Player.h"

// Gives some effect and goes inactive
class EffectGiverTileData : public TileData {
private:
	std::vector<std::shared_ptr<Effect>> m_effects;
	float m_activationRadius;

public:
	EffectGiverTileData(std::vector<std::shared_ptr<Effect>> effects, const float activationRadius);

	void update(math::Vector2f pos, World& world, Player& player) override;

	std::unique_ptr<TileData> copy() override;
};