// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Graphics/GL/GLShader.h"
#include "Graphics/Model/SceneObject.h"

/*
*	ModelShader(.h/.cpp) contains a class that is base for all the model shaders.
*	A model shader allows to render Models.
*/

class ModelShader : public gl::Shader {
protected:
	GLint m_modelMatrixLoc;
	GLint m_projViewMatrixLoc;
	GLint m_playerPosLoc;
	GLint m_fogPowerLoc;

public:
	ModelShader(std::string_view vertexShaderFile, std::string_view fragmentShaderFile);
	ModelShader(std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile);

	void setProjViewMatrix(const glm::mat4& value);
	void setModelMatrix(const glm::mat4& value);
	void setSceneObject(const model::SceneObject& value); // Unites the previous 2

	void setPlayerPos(const glm::vec3& pos);
	void setPlayerPos(const math::Vector2f& pos);

	void setFogPower(GLint value);
	void loadDefaultFogPower(); // From global settings
};