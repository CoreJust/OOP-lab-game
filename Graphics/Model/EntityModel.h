// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "DynamicModel.h"
#include "World/Entity/EntityId.h"

/*
*	EntityModel(.h/.cpp) contains a class that implements a model of an entity.
*/

namespace model {
	class EntityModel final : public DynamicModel {
	private:
		EntityId m_id;

	public:
		EntityModel(const EntityId id);

		constexpr EntityId getEntityID() const noexcept {
			return m_id;
		}

	private:
		DynamicModel generateModelFor(const EntityId id);
	};
}