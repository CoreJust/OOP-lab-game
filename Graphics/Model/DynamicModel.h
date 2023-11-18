// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "StaticModel.h"

/*
*	DynamicModel(.h/.cpp) contains a class that implements a complex dynami model.
*
*	A dynamic model is a model that consists of a central static model and some number of dynamic submodels.
*	Submodels' coordinates are relative to the parent model.
*/

namespace model {
	class DynamicModel : public StaticModel {
	private:
		std::vector<DynamicModel> m_submodels;

	public:
		void render(ModelShader& shader, const SceneObject& parentSO = SceneObject{ });

		void addSubModel(DynamicModel subModel);
	};
}