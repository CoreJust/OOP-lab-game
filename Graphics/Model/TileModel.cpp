// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TileModel.h"
#include "ModelDescription.h"
#include "TextureCoords.h"
#include "Graphics/Texture/TextureAtlas.h"

model::TileModel::TileModel(const TileId id, const math::DirectionFlag VNSurrounding) {
	TextureCoords coords = TextureAtlas().genTexCoordsGenerator();
	id.loadToTexCoords(coords);

	StaticModel::setMesh(id.getModelDescription().generateMesh(
		coords.extract(),
		VNSurrounding
	).move({ 0, id.isForeground() * 0.005f, 0 }));
}
