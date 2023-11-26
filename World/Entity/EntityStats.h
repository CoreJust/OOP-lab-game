// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>

/*
*	EntityStats.h contains a struct that represents a set of characteristics common
*	for all the Entities.
*
*	Each entity contains these characteristics, they depend on the Entities Id and
*	(in the future) on its level, as well as the effects.
* 
*	List of the characteristics (stats):
*		1) max health - the maximal health an entity can have
*		2) defence - diminishes the incoming damage with a difficult scale (explained in the entity class)
*		3) power - increases the outgoing damage and (possibly, in the future) the ability to destroy things
*		4) speed - the movement speed base (then it is modified with the tiles' speed modifier)
*		5) hitbox - the "size" of the entity - from its center (position) to its bounds:
*		
*					-----------------------
*					|		   |		  |
*					|		hitbox 		  |
*					|		   | 		  |
*					|		    		  |
*					|--hitbox- X -hitbox--|			-		THE SQUARE REPRESENTS THE ENTITY
*					|		    		  |
*					|		   | 		  |
*					|		hitbox 		  |
*					|		   |		  |
*					-----------------------
*/

// Basic stats of an entity
struct EntityStats {
	float maxHealth;
	float defence;
	float power;
	float speed;
	
	float hitbox;

	std::string toString(const float health) const;
};