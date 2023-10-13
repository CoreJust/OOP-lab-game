// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string_view>

#include "GLObject.h"

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

		void create() override;
		void release() override;

		void bind() override;
		void unbind() override;

	private:
		ShaderObject compileShader(std::string_view shaderFile, const GLenum shaderType) const;
		void compileProgram(const GLuint vertexShader, const GLuint geometryShader, const GLuint fragmentShader);
	};
}