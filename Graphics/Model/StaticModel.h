// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <memory>

#include "Graphics/GL/GLVAO.h"
#include "Graphics/GL/GLBufferObject.h"
#include "Graphics/Shader/ModelShader.h"
#include "SceneObject.h"
#include "Mesh.h"

/*
*	StaticModel(.h/.cpp) contains a class that implements some static model.
* 
*	A model is a visual object with a mesh.
*	A texture if there is can be provided externally.
* 
*	Static means that the model's mesh is fixed, you can only move/rotate the model as a whole.
*	A part of a dynamic model.
*/

namespace model {
	class StaticModel {
	protected:
		SceneObject m_sceneObject; // Represents the model's position and rotation

		std::vector<std::unique_ptr<gl::BufferObject>> m_buffers; // both VBOs and EBOs
		gl::VAO m_vao;

		GLuint m_vboCount = 0;
		GLuint m_indicesCount = 0;

	public:
		StaticModel();
		StaticModel(const StaticModel&) = delete;
		StaticModel(StaticModel&& other) noexcept;
		~StaticModel();

		// Renders the model, but the shader must be already binded
		void render(ModelShader& shader);

		void clear();

		void setSceneObject(const SceneObject& value);
		void setMesh(const Mesh& mesh);
		void addVBO(const gl::Vertices& vertices, const GLint dims); // dims is the number of dimensions of a vertex
		void addEBO(const gl::Indices& indices);

		void bind();
		void unbind();

		// Allows moving the model around via model.sceneObject().<some scene-object method>
		constexpr SceneObject& sceneObject() noexcept {
			return m_sceneObject;
		}

		const SceneObject& getSceneObject() const noexcept;
		const gl::VAO& getVAO() const noexcept;
		GLuint getIndicesCount() const noexcept;
	};
}