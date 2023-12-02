// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "ShaderRegistry.h"
#include "ModelShader.h"

/*
*	ModelShaderRegistry(.h/.cpp) contains a class that inherits
*	the ShaderRegistry and is supposed to be used with the model
*	shader. In addition to the common ShaderRegistry's functions,
*	it loads the variable locations into the shader.
*/

class ModelShaderRegistry final : public ShaderRegistry<ModelShader> {
public:
	void registerShader(ModelShader& shader) override;
};