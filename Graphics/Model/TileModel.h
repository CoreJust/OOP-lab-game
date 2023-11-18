// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "StaticModel.h"
#include "Shape.h"
#include "World/Tile/TileId.h"

/*
*	TileModel.h contains a class that implements the 3D models of tiles.
*/

namespace model {
	class TileModel final : public StaticModel {
	public:
		TileModel(const TileId id, const math::DirectionFlag VNSurrounding = math::DirectionFlag::NONE);
	};
}