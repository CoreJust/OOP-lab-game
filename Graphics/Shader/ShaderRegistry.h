// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <map>

#include "Utils/Concepts.h"
#include "Graphics/GL/GLShader.h"
#include "Graphics/Shader/UniformVariable.h"

/*
*	ShaderRegistry.h contains a class that is used for
*	registering a shader's instances and then conveniently
*	access uniform variables of them all (or just do something 
*	for all of them).
*/

template<class Shader>
	requires std::is_base_of_v<gl::Shader, Shader>
class ShaderRegistry {
protected:
	std::vector<Shader*> m_shaders;
	std::map<std::string, UniformVariable> m_uniforms;

public:
	ShaderRegistry() = default;

	virtual void registerShader(Shader& shader) {
		m_shaders.push_back(&shader);
	}

	void registerVariable(Shader& shader, UniformVariable::Type type, const std::string& name) {
		m_uniforms.emplace(name, UniformVariable(shader, type, name));
	}
	
	void storeToShader(Shader& shader) {
		for (auto& [key, val] : m_uniforms) {
			val.loadToShader(shader);
		}
	}

	UniformVariable& operator[](const std::string& name) {
		assert(m_uniforms.contains(name));

		return m_uniforms.at(name);
	}
	
	template<class... Args>
	auto operator->*(void (Shader::* method)(Args...)) {
		return [&](Args... args) {
			for (auto& shader : m_shaders) {
				(shader->*method)(std::forward<Args...>(args)...);
			}
		};
	};
};