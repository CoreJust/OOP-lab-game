// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityShader.h"
#include "ModelShaderRegistry.h"

EntityShader::EntityShader(ModelShaderRegistry& msr) : ModelShader(msr, "entity_vertex", "entity_fragment") { }
