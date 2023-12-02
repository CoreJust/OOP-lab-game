// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>
#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>

#include "Math/Vector.h"

/*
*	UniformVariable(.h/.cpp) contains a class that manages opengl shader's
*	uniform variables.
* 
*	Uniform variable can contain the shader's variable value until it is binded,
*	and then store the value there.
*/

namespace gl {
	class Shader;
}

class UniformVariable final {
public:
	enum Type : uint8_t {
		VOID = 0,

		BOOL,
		INT,
		UINT,
		FLOAT,
		DOUBLE,
		VEC_2F,
		VEC_2I,
		VEC_2U,
		VEC_2D,
		VEC_3F,
		VEC_4F,
		MATRIX_4F,

		NUMBER_TYPES
	};

private:
	GLint m_id;
	Type m_type;
	union {
		bool m_asBool;
		GLint m_asInt;
		GLuint m_asUint;
		GLfloat m_asFloat;
		GLdouble m_asDouble;
		math::Vector2f m_asVec2f;
		math::Vector2d m_asVec2d;
		math::Vector2i m_asVec2i;
		math::Vector2u m_asVec2u;
		glm::vec3 m_asVec3;
		glm::vec4 m_asVec4;
		glm::mat4 m_asMat4;
	};

public:
	constexpr UniformVariable() noexcept : m_id(-1), m_type(Type::VOID), m_asBool(false) { }
	UniformVariable(gl::Shader& shader, const Type type, const std::string& name);
	UniformVariable(const UniformVariable& other);

	UniformVariable& operator=(const UniformVariable& other);

	UniformVariable& operator=(const bool value);
	UniformVariable& operator=(const GLint value);
	UniformVariable& operator=(const GLuint value);
	UniformVariable& operator=(const GLfloat value);
	UniformVariable& operator=(const GLdouble value);
	UniformVariable& operator=(const math::Vector2f& value);
	UniformVariable& operator=(const math::Vector2i& value);
	UniformVariable& operator=(const math::Vector2u& value);
	UniformVariable& operator=(const math::Vector2d& value);
	UniformVariable& operator=(const glm::vec2& value);
	UniformVariable& operator=(const glm::vec3& value);
	UniformVariable& operator=(const glm::vec4& value);
	UniformVariable& operator=(const glm::mat4 value);

	void initVariable(gl::Shader& shader, Type type, const std::string& name);
	void loadToShader(gl::Shader& shader);

	const std::string& toString() const noexcept;
};