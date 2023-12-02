// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ModelShaderRegistry.h"

void ModelShaderRegistry::registerShader(ModelShader& shader) {
	ShaderRegistry<ModelShader>::registerShader(shader);

	if (m_uniforms.empty()) {
		registerVariable(shader, UniformVariable::MATRIX_4F, "proj_view_matrix");
		registerVariable(shader, UniformVariable::VEC_3F, "player_pos");
		registerVariable(shader, UniformVariable::INT, "fog_power");
		registerVariable(shader, UniformVariable::BOOL, "is_blind");
	}

	shader.m_modelMatrixLoc = shader.getVariableLocation("model_matrix").expect("A model shader must contain a uniform variable mat4 model_matrix");
}
