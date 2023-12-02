// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ModelShader.h"
#include "GlobalSettings.h"
#include "ModelShaderRegistry.h"

ModelShader::ModelShader(ModelShaderRegistry& msr, std::string_view vertexShaderFile, std::string_view fragmentShaderFile)
	: gl::Shader(vertexShaderFile, fragmentShaderFile) {
	msr.registerShader(*this);
}

ModelShader::ModelShader(ModelShaderRegistry& msr, std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile)
	: gl::Shader(vertexShaderFile, geometryShaderFile, fragmentShaderFile) {
	msr.registerShader(*this);
}

void ModelShader::setModelMatrix(const glm::mat4& value) {
	setVariable(m_modelMatrixLoc, value);
}

void ModelShader::setSceneObject(const model::SceneObject& value) {
	setModelMatrix(value.genMatrix());
}
