// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Graphics/GL/GLShader.h"
#include "Graphics/Model/SceneObject.h"

/*
*	ModelShader(.h/.cpp) contains a class that is base for all the model shaders.
*	A model shader allows to render Models.
*/

class ModelShaderRegistry;

class ModelShader : public gl::Shader {
	friend class ModelShaderRegistry;

protected:
	GLint m_modelMatrixLoc = -1;

public:
	ModelShader(ModelShaderRegistry& msr, std::string_view vertexShaderFile, std::string_view fragmentShaderFile);
	ModelShader(ModelShaderRegistry& msr, std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile);

	void setModelMatrix(const glm::mat4& value);
	void setSceneObject(const model::SceneObject& value); // Unites the previous 2
};