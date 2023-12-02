#include "VenomousPlant.h"

VenomousPlant::VenomousPlant(const math::Vector2f& pos, World& pWorld)
	: Enemy(1.5f, 0.f, 0.f, EntityId::VENOMOUS_PLANT, pos, pWorld) {

}
