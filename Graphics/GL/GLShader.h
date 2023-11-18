// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string_view>
#include <glm/glm.hpp>

#include "Utils/Result.h"
#include "Math/Vector.h"
#include "GLObject.h"

/*
*	GLShader(.h/.cpp) contains a class that manages opengl shaders.
*
*	Shader is a program that is employed on the model in the GPU and allows to 
*	manage the way it is rendered, e.g. applying some effects.
*/

namespace gl {
	// Basic class for all the shaders
	class Shader : public Object {
	protected:
		// Contains a temporary shader object during the shader's initialization
		class ShaderObject {
		private:
			GLuint m_id;

		public:
			ShaderObject(GLenum shaderType);
			ShaderObject(ShaderObject&& other) noexcept;
			ShaderObject(const ShaderObject&) = delete;

			~ShaderObject();

			constexpr operator GLuint() const {
				return m_id;
			}

			GLuint* get();
		};

	public:
		Shader(std::string_view vertexShaderFile, std::string_view fragmentShaderFile);
		Shader(std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile);
		~Shader();

		void create() override final;
		void release() override final;

		void bind() override final;
		void unbind() override final;

		// Access to shader's variables
		utils::Result<GLint> getVariableLocation(const char* name) const;

		void setVariable(const GLint id, const GLint value);
		void setVariable(const GLint id, const GLfloat value);
		void setVariable(const GLint id, const GLdouble value);
		void setVariable(const GLint id, const math::Vector2f& value);
		void setVariable(const GLint id, const math::Vector2i& value);
		void setVariable(const GLint id, const math::Vector2u& value);
		void setVariable(const GLint id, const glm::vec2& value);
		void setVariable(const GLint id, const glm::vec3& value);
		void setVariable(const GLint id, const glm::vec4& value);
		void setVariable(const GLint id, const glm::mat4& value);

	private:
		ShaderObject compileShader(std::string_view shaderFile, const GLenum shaderType) const;
		void compileProgram(const GLuint vertexShader, const GLuint geometryShader, const GLuint fragmentShader);
	};
}