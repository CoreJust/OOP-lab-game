// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "DynamicModel.h"

void model::DynamicModel::render(ModelShader& shader, const SceneObject& parentSO) {
	SceneObject realSO = m_sceneObject.combinedWith(parentSO);
	shader.setSceneObject(realSO);

	bind();
	glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	unbind();

	for (auto& submodel : m_submodels) {
		submodel.render(shader, realSO);
	}
}

void model::DynamicModel::addSubModel(DynamicModel subModel) {
	m_submodels.emplace_back(std::move(subModel));
}
