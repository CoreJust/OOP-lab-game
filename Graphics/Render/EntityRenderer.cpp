// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityRenderer.h"

void EntityRenderer::addEntity(utils::NoNullptr<model::EntityModel> model) {
	m_entities.push_back(model);
}

void EntityRenderer::render(sf::RenderWindow& window, Camera& camera, ResourceManager& resources) {
	m_shader.bind();
	m_shader.loadDefaultFogPower();
	m_shader.setPlayerPos(camera.getPos());
	m_shader.setProjViewMatrix(camera.genProjViewMatrix());

	for (auto& model : m_entities) {
		resources.getEntityTexture(model->getEntityID()).bind();
		model->render(m_shader);
	}

	m_shader.unbind();

	m_entities.clear();
}
