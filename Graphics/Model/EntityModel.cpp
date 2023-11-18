// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityModel.h"

model::EntityModel::EntityModel(const EntityId id)
	: DynamicModel(generateModelFor(id)), m_id(id) {

}

model::DynamicModel model::EntityModel::generateModelFor(const EntityId id) {
	const DynamicModelDescription& DMD = id.getDynamicModelDescription();

	return DMD.forEach<DynamicModel>(
		[](std::vector<DynamicModel> submodels, const SceneObject& SO, const ModelDescription& MD, const TextureCoords& TC) -> DynamicModel {
			DynamicModel result;
			result.setMesh(MD.generateMesh(TC.get(), math::DirectionFlag::NONE).rotate({ 0.f, std::numbers::pi, 0.f }));
			result.setSceneObject(SO);

			for (auto& submodel : submodels) {
				result.addSubModel(std::move(submodel));
			}

			return result;
		}
	);
}
