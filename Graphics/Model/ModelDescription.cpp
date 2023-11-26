// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ModelDescription.h"
#include "Shape.h"

#include "IO/Logger/Logger.h"

model::Mesh model::ModelDescription::generateMesh(gl::Vertices texCoords, const math::DirectionFlag VNSurroundings) const {
	if (m_id == ShapeId::SIMPLE_WALL) {
		texCoords = getTexCoordsForVNS(texCoords, math::DirectionFlag(m_asDirectionFlags & ~VNSurroundings)); // So that the walls have correct texture
	}

    Shape shape(m_id, std::move(texCoords));
	Mesh result;

	switch (m_id) {
		case ShapeId::EMPTINESS: break;
		case ShapeId::QUAD:
		case ShapeId::BOX: result = shape.createMesh(m_asFromTo[0], m_asFromTo[1]); break;
		case ShapeId::FLAT_FLOOR: result = shape.createMesh(); break;
		case ShapeId::FLAT_FLOOR_OBJECT: result = shape.createMesh().move({ 0, 0.001f, 0 }); break;
		case ShapeId::SIMPLE_WALL: result = shape.createMesh(math::DirectionFlag(m_asDirectionFlags & ~VNSurroundings)); break;
		case ShapeId::FLOOR_BOX: result = shape.createMesh(m_asWHD.x, m_asWHD.y, m_asWHD.z); break;
	default: break;
	}

	if (auto validation = result.validate(); !validation.isOk()) {
		io::Logger::error("ModelDescription: failure while generating mesh for a model: " + validation.error());
		return Mesh { };
	}

	return result;
}

gl::Vertices model::ModelDescription::getTexCoordsForVNS(const gl::Vertices& texCoords, const math::DirectionFlag VNSurroundings) const {
	if (VNSurroundings == math::DirectionFlag::ALL_DIRECTIONS) {
		return texCoords;
	}

	size_t faceSize = texCoords.size() / 4;
	gl::Vertices result;
	if (VNSurroundings & math::DirectionFlag::UP) {
		result.insert(result.end(), texCoords.begin(), texCoords.begin() + faceSize);
	} if (VNSurroundings & math::DirectionFlag::DOWN) {
		result.insert(result.end(), texCoords.begin() + faceSize, texCoords.begin() + 2 * faceSize);
	} if (VNSurroundings & math::DirectionFlag::RIGHT) {
		result.insert(result.end(), texCoords.begin() + 2 * faceSize, texCoords.begin() + 3 * faceSize);
	} if (VNSurroundings & math::DirectionFlag::LEFT) {
		result.insert(result.end(), texCoords.begin() + 3 * faceSize, texCoords.begin() + 4 * faceSize);
	}

	return result;
}
