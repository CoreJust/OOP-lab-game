// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TileShader.h"
#include "ModelShaderRegistry.h"

TileShader::TileShader(ModelShaderRegistry& msr) : ModelShader(msr, "tile_vertex", "tile_fragment") { }
