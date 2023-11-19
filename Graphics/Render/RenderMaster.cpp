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

	m_contextManager.setClearColor(0.6f, 0.46f, 0.46f);
	m_contextManager.addContext(m_generalContext)
		.enableTerminationUponErrors()
		.enableDepthTest()
		.enableMultisampling()
		.enableCullFace()
		.enableBlending();
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
	// Core OpenGL using code

	m_contextManager.newFrame();
	m_contextManager.forContext(m_generalContext, [this, &window, &camera]() {
		m_entityRenderer.render(window, camera, m_resources);
		m_tileRenderer.render(window, camera);
	});

	m_contextManager.endFrame();

	// SFML using code
	// Note: SFML uses some legacy OpenGL functions, so it cannot be mixed up with the core OpenGL

	window.resetGLStates();
	m_guiRenderer.render(window, camera);
}

GameGUIRenderer& RenderMaster::getGameGuiRenderer() noexcept {
	return m_guiRenderer;
}

ResourceManager& RenderMaster::getResources() noexcept {
	return m_resources;
}
