// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLShader.h"

#include <string>

#include "IO/File/FileLoader.h"
#include "IO/Logger.h"
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

	compileProgram(vertexShader, 0, vertexShader);
}

gl::Shader::Shader(std::string_view vertexShaderFile, std::string_view geometryShaderFile, std::string_view fragmentShaderFile) {
	auto vertexShader = compileShader(vertexShaderFile, GL_VERTEX_SHADER);
	auto geometryShader = compileShader(geometryShaderFile, GL_GEOMETRY_SHADER);
	auto fragmentShader = compileShader(fragmentShaderFile, GL_FRAGMENT_SHADER);

	compileProgram(vertexShader, geometryShader, vertexShader);
}

void gl::Shader::create() {
	assert(m_isEmpty);

	m_id = glCreateProgram();
	m_isEmpty = false;
}

void gl::Shader::release() {
	assert(!m_isEmpty);

	glDeleteProgram(m_id);
	m_isEmpty = true;
}

void gl::Shader::bind() {
	assert(!m_isEmpty);

	glUseProgram(m_id);
}

void gl::Shader::unbind() {
	glUseProgram(0);
}

gl::Shader::ShaderObject gl::Shader::compileShader(std::string_view shaderFile, const GLenum shaderType) const {
	static GLchar s_infoLog[1024];

	io::FileLoader fileLoader(GlobalSettings::get().getShadersLocation(), ".glsl");
	ShaderObject id(shaderType);

	GLint compilationResult;
	std::string shaderText = fileLoader.loadFile(shaderFile);
	const char* data = shaderText.data();

	glShaderSource(id, 1, &data, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);
	if (!compilationResult) { // Shader compilation failed
		glGetShaderInfoLog(id, 1024, nullptr, s_infoLog);
		io::Logger::logError(std::string("Shader compilation error: ") + s_infoLog + "\nShader file: " + fileLoader.getFullPath(shaderFile));
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
		io::Logger::logError(std::string("Shader program linking error: ") + s_infoLog);
	}
}
