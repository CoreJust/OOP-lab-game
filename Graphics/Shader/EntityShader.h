// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "ModelShader.h"

/*
*	EntityShader(.h/.cpp) contains a class that implements the shaders for the entities in the game.
*/

class EntityShader final : public ModelShader {
public:
	EntityShader(ModelShaderRegistry& msr);
};