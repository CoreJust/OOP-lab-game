// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>

#include "Utils/Result.h"
#include "Math/Vector.h"

/*
*	Texture(.h/.cpp) contains a class that implements methods to load
*	and access textures.
*/

// Contains a single texture of something
class Texture {
protected:
	GLuint m_textureID;

public:
	// A single texture of a tile is 32x32 pixels - the standard used by the project
	constexpr static uint32_t TEXTURE_SIZE = 32;

public:
	Texture() = default;
	Texture(const std::string& filePath);
	~Texture();

	utils::Result<utils::Void> loadFromFile(const std::string& filePath);

	// A group of functions for using with OpenGL
	void setupForOpenGL();
	void setTextureBlock(GLenum block = GL_TEXTURE0);
	void bind();
	void unbind();
};