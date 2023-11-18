// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RenderMaster.h"

#include "Graphics/Texture/ResourceRegisterer.h"

#include "Graphics/Model/EntityModel.h"
#include "Graphics/Shader/EntityShader.h"

RenderMaster::RenderMaster() 
	: m_tileRenderer(m_resources) {
	ResourceRegisterer registerer(m_resources);
	registerer.registerAll();
}

void RenderMaster::drawEntity(model::EntityModel& entityModel) {
	m_entityRenderer.addEntity(&entityModel);
}

void RenderMaster::drawTile(const TileId id, const math::Vector2f& position, const math::DirectionFlag VNS) {
	if (id.getCategory() == TileCategory::WALL) {
		m_tileRenderer.addTile(position, id, VNS);
	} else {
		m_tileRenderer.addTile(position, id);
	}
}

void RenderMaster::render(sf::RenderWindow& window, Camera& camera) {
	glClearColor(0.6f, 0.46f, 0.46f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_entityRenderer.render(window, camera, m_resources);
	m_tileRenderer.render(window, camera);

	window.pushGLStates();
	window.resetGLStates();

	m_guiRenderer.render(window, camera);

	window.popGLStates();
}

GameGUIRenderer& RenderMaster::getGameGuiRenderer() noexcept {
	return m_guiRenderer;
}

ResourceManager& RenderMaster::getResources() noexcept {
	return m_resources;
}
