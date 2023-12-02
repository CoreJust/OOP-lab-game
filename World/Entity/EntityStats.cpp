// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityStats.h"
#include <format>

std::string EntityStats::toString(const float health) const {
    return std::format(
        "( health: {0}/{1}, defence: {2}, power: {3}, speed: {4}, agility: {5} )",
        int(health),
        int(maxHealth),
        int(defence),
        int(power),
        int(speed),
        int(agility)
    );
}
