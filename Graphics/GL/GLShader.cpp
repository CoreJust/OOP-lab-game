// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLShader.h"

#include <string>
#include <glm\gtc\type_ptr.hpp>

#include "IO/File/FileLoader.h"
#include "IO/Logger/Logger.h"
#include "GlobalSettings.h"

gl::Shader::ShaderObject::ShaderObject(GLenum shaderType) {
	m_id = glCreateShader(shaderType);
}

gl::Shader::ShaderObject::ShaderObject(ShaderObject&& other) noexcept : m_id(other.m_id) {
	other.m_id = 0;
}

gl::Shader::ShaderObject::~ShaderObject() {
	if (m_id) {
		glDeleteShader(m_id);
		m_id = 0;
	}
}

GLuint* gl::Shader::ShaderObject::get() {
	return &m_id;
}


gl::Shader::Shader(std::string_view vertexShaderFile, std::string_view fragmentShaderFile) {
	auto vertexShader = compileShader(vertexShaderFile, GL_VERTEX_SHADER);
	auto fragmentShader = compileShader(fragmentShaderFile, GL_FRAGMENT_SHADER);

	compileProgram(vertexShader, 0, fragmentShader);

	io::Logger::debug("GLShader: compiled shader from " + std::string(vertexShaderFile) + " and " + std::string(fragmentShaderFile));
}

gl::Shader::Shader(std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile) {
	auto vertexShader = compileShader(vertexShaderFile, GL_VERTEX_SHADER);
	auto geometryShader = compileShader(geometryShaderFile, GL_GEOMETRY_SHADER);
	auto fragmentShader = compileShader(fragmentShaderFile, GL_FRAGMENT_SHADER);

	compileProgram(vertexShader, geometryShader, fragmentShader);

	io::Logger::debug("GLShader: compiled shader from " 
					  + std::string(vertexShaderFile) 
					  + ", "
					  + std::string(geometryShaderFile)
					  + " and " 
					  + std::string(fragmentShaderFile));
}

gl::Shader::~Shader() {
	if (!isEmpty()) {
		release();
	}
}

void gl::Shader::create() {
	assert(isEmpty());

	m_id = glCreateProgram();
}

void gl::Shader::release() {
	assert(!isEmpty());

	glDeleteProgram(m_id);
	m_id = 0;
}

void gl::Shader::bind() {
	assert(!isEmpty());

	glUseProgram(m_id);
}

void gl::Shader::unbind() {
	glUseProgram(0);
}

utils::Result<GLint> gl::Shader::getVariableLocation(const char* name) const {
	GLint location = glGetUniformLocation(m_id, name);
	if (location == -1) {
		io::Logger::warning("GLShader: failed to find variable " + std::string(name));

		return utils::Failure("Variable not found: " + std::string(name));
	}

	return location;
}

void gl::Shader::setVariable(const GLint id, const GLint value) {
	glUniform1i(id, value);
}

void gl::Shader::setVariable(const GLint id, const GLfloat value) {
	glUniform1f(id, value);
}

void gl::Shader::setVariable(const GLint id, const GLdouble value) {
	glUniform1d(id, value);
}

void gl::Shader::setVariable(const GLint id, const math::Vector2f& value) {
	glUniform2f(id, value.x(), value.y());
}

void gl::Shader::setVariable(const GLint id, const math::Vector2i& value) {
	glUniform2i(id, value.x(), value.y());
}

void gl::Shader::setVariable(const GLint id, const math::Vector2u& value) {
	glUniform2ui(id, value.x(), value.y());
}

void gl::Shader::setVariable(const GLint id, const glm::vec2& value) {
	glUniform2f(id, value.x, value.y);
}

void gl::Shader::setVariable(const GLint id, const glm::vec3& value) {
	glUniform3f(id, value.x, value.y, value.z);
}

void gl::Shader::setVariable(const GLint id, const glm::vec4& value) {
	glUniform4f(id, value.x, value.y, value.z, value.w);
}

void gl::Shader::setVariable(const GLint id, const glm::mat4& value) {
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

gl::Shader::ShaderObject gl::Shader::compileShader(std::string_view shaderFile, const GLenum shaderType) const {
	static GLchar s_infoLog[1024];

	io::FileLoader fileLoader(GlobalSettings::get().getShadersLocation(), ".glsl");
	ShaderObject id(shaderType);

	GLint compilationResult;
	std::string shaderText = fileLoader.loadFile(shaderFile);
	const char* data = shaderText.data();

	glShaderSource(id, 1, &data, NULL);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);
	if (!compilationResult) { // Shader compilation failed
		glGetShaderInfoLog(id, 1024, nullptr, s_infoLog);
		io::Logger::error(std::string("Shader compilation error: ") + s_infoLog + "\nShader file: " + fileLoader.getFullPath(shaderFile));
	}

	return id;
}

void gl::Shader::compileProgram(const GLuint vertexShader, const GLuint geometryShader, const GLuint fragmentShader) {
	static GLchar s_infoLog[1024];

	GLint compilationResult;

	create();

	glAttachShader(m_id, vertexShader);
	if (geometryShader) {
		glAttachShader(m_id, geometryShader);
	}

	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &compilationResult);
	if (!compilationResult) {
		glGetProgramInfoLog(m_id, 1024, nullptr, s_infoLog);
		io::Logger::error(std::string("Shader program linking error: ") + s_infoLog);
	}

	glDetachShader(m_id, vertexShader);
	if (geometryShader) {
		glDetachShader(m_id, geometryShader);
	}

	glDetachShader(m_id, fragmentShader);
}
