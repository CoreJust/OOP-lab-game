#pragma once

// Basic stats of an entity
struct EntityStats {
	float maxHealth;
	float defence;
	float power;
	float speed;
	
	float hitbox;

	constexpr EntityStats(float maxHealth, float defence, float power, float speed, float hitbox) noexcept
		: maxHealth(maxHealth), defence(defence), power(power), speed(speed), hitbox(hitbox) { }
};