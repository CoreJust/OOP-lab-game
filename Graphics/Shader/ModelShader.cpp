// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ModelShader.h"
#include "IO/Logger.h"
#include "GlobalSettings.h"

ModelShader::ModelShader(std::string_view vertexShaderFile, std::string_view fragmentShaderFile) 
	: gl::Shader(vertexShaderFile, fragmentShaderFile),
	m_modelMatrixLoc(getVariableLocation("model_matrix").expect("A model shader must contain a uniform variable mat4 model_matrix")),
	m_projViewMatrixLoc(getVariableLocation("proj_view_matrix").expect("A model shader must contain a uniform variable mat4 proj_view_matrix")),
	m_playerPosLoc(getVariableLocation("player_pos").expect("A model shader must contain a uniform variable vec3 player_pos")),
	m_fogPowerLoc(getVariableLocation("fog_power").expect("A model shader must contain a uniform variable int fog_power")) {
	
}

ModelShader::ModelShader(std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile) 
	: gl::Shader(vertexShaderFile, geometryShaderFile, fragmentShaderFile),
	m_modelMatrixLoc(getVariableLocation("model_matrix").expect("A model shader must contain a uniform variable mat4 model_matrix")),
	m_projViewMatrixLoc(getVariableLocation("proj_view_matrix").expect("A model shader must contain a uniform variable mat4 proj_view_matrix")),
	m_playerPosLoc(getVariableLocation("player_pos").expect("A model shader must contain a uniform variable vec3 player_pos")),
	m_fogPowerLoc(getVariableLocation("fog_power").expect("A model shader must contain a uniform variable int fog_power")) {
	
}

void ModelShader::setProjViewMatrix(const glm::mat4& value) {
	setVariable(m_projViewMatrixLoc, value);
}

void ModelShader::setModelMatrix(const glm::mat4& value) {
	setVariable(m_modelMatrixLoc, value);
}

void ModelShader::setSceneObject(const model::SceneObject& value) {
	setModelMatrix(value.genMatrix());
}

void ModelShader::setPlayerPos(const glm::vec3& pos) {
	setVariable(m_playerPosLoc, pos);
}

void ModelShader::setPlayerPos(const math::Vector2f& pos) {
	setPlayerPos({ pos.x(), 0.5f, pos.y() });
}

void ModelShader::setFogPower(GLint value) {
	if (value > 4) {
		value = 4;
	} else if (value < 0) {
		value = 0;
	}

	setVariable(m_fogPowerLoc, value);
}

void ModelShader::loadDefaultFogPower() {
	setFogPower(GlobalSettings::get().getFogPower());
}
