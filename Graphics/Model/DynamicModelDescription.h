// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Graphics/Texture/TextureAtlas.h"
#include "SceneObject.h"
#include "ModelDescription.h"
#include "TextureCoords.h"

/*
*	DynamicModelDescription(.h/.cpp) contains a class that is allows
*	conveniently define a complex model.
* 
*	Unlike the ModelDesciption, this one is used for the DynamicModel
*	with a number of Meshes.
*/

namespace model {
	class DynamicModelDescription final {
	private:
		SceneObject m_sceneObject;
		ModelDescription m_modelDescription;
		TextureCoords m_texCoords;

		std::vector<DynamicModelDescription> m_submodelDescriptions;

	public:
		DynamicModelDescription(SceneObject SO, ModelDescription MD) noexcept;
		constexpr DynamicModelDescription(DynamicModelDescription&& other) noexcept = default;

		static DynamicModelDescription makeBox(
			SceneObject SO,
			const glm::vec3& from,
			const glm::vec3& size,
			const math::Vector2f& texCoordsFrom
		);

		constexpr DynamicModelDescription&& move() {
			return std::move(*this);
		}

		DynamicModelDescription& addSubModelDesc(DynamicModelDescription DMD);

		template<utils::Callable<void, TextureCoords&> Func>
		DynamicModelDescription& forTexCoords(Func func) {
			func(m_texCoords);
			return *this;
		}
		
		// Calls func for each submodel and the very model
		// The first argument of the func is its results for the current model's submodels
		template<class Res, utils::Callable<Res, std::vector<Res>, SceneObject&, ModelDescription&, TextureCoords&> Func>
		Res forEach(Func func) {
			std::vector<Res> vec;

			for (auto& submodel : m_submodelDescriptions) {
				vec.push_back(submodel.forEach<Res>(func));
			}

			return func(std::move(vec), m_sceneObject, m_modelDescription, m_texCoords);
		}

		// Calls func for each submodel and the very model
		// The first argument of the func is its results for the current model's submodels
		template<class Res, utils::Callable<Res, std::vector<Res>, const SceneObject&, const ModelDescription&, const TextureCoords&> Func>
		Res forEach(Func func) const {
			std::vector<Res> vec;

			for (auto& submodel : m_submodelDescriptions) {
				vec.push_back(submodel.forEach<Res>(func));
			}

			return func(std::move(vec), m_sceneObject, m_modelDescription, m_texCoords);
		}

		constexpr TextureCoords& texCoords() noexcept {
			return m_texCoords;
		}

		constexpr SceneObject& sceneObject() noexcept {
			return m_sceneObject;
		}
	};
}