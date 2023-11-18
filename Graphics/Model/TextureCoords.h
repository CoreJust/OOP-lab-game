// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Rect.h"
#include "Graphics/GL/GLBufferObject.h"

/*
*	TextureCoords.h contains a class that allows to conveniently define texture coordinates.
* 
*	Texture box sketch (in an image):
* 
*					|----------||----------|
*					|		   ||		   |
*					|	TOP	   ||  BOTTOM  |
*					|		   ||		   |
*					|----------||----------|
*		|----------||----------||----------||----------|
*		|		   ||		   ||		   ||		   |
*		|	RIGHT  ||	FRONT  ||	LEFT   ||	BACK   |
*		|		   ||		   ||		   ||		   |
*		|----------||----------||----------||----------|
* 
*	Usage:
*		TextureCoords tc(-picture-size-);
*		auto texCoords = tc.addTextureRect(...).addTextureBox(...)....extract();
*/

namespace model {
	class TextureCoords final {
	private:
		math::Vector2f m_unitSize; // The size of a primary texture (TEXTURE_SIZE)
		gl::Vertices m_texCoords;

	public:
		TextureCoords(); // For a single-unit texture
		TextureCoords(const math::Vector2f& unitSize);
		TextureCoords(const math::Vector2u& imageSize);

		// Coords in units
		TextureCoords& addTextureRect(const math::Rectf& rect);
		TextureCoords& addTextureBox(const math::Vector2f& pos, float bX, float bY, float bZ); // (bX, bY, bZ) - box size

		// Coords in pixels
		TextureCoords& addTextureRect(const math::Rectu& rect);
		TextureCoords& addTextureBox(const math::Vector2u& pos, const uint32_t bX, const uint32_t bY, const uint32_t bZ); // (bX, bY, bZ) - box size

		TextureCoords& addFace(const math::Rectf& rect);

		// Repeats the current texCoords count times
		TextureCoords& repeat(uint8_t count);

		gl::Vertices&& extract();
		const gl::Vertices& get() const;
	};
}
