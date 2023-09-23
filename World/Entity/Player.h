#pragma once
#include "Entity.h"

class Player final : public Entity {
public:
	Player(utils::Vector2f pos);
};