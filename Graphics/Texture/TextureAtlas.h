// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "Math/Vector.h"
#include "Texture.h"
#include "Graphics/Model/TextureCoords.h"

/*
*	TextureAtlas(.h/.cpp) contains a class that provides API
*	to work with a texture atlas (a certain one - of tiles).
*/

// Contains a pack of textures
class TextureAtlas {
public:
	constexpr static inline uint32_t TEXTURES_IN_ROW = 8;
	constexpr static inline uint32_t ATLAS_SIZE = Texture::TEXTURE_SIZE * TEXTURES_IN_ROW;
	constexpr static inline float UNIT_SIZE = 1.f / TEXTURES_IN_ROW;

private:
	Texture m_texture;

public:
	TextureAtlas() = default;
	TextureAtlas(const std::string& fileName);

	model::TextureCoords genTexCoordsGenerator() const; // Fills in the info that allows to make tex coords
	void loadFrom(const std::string& fileName);

	void bind();
	void unbind();

	const Texture& getTexture() const;
	math::Vector2u getSize() const;
};