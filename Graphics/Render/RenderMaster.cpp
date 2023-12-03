// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RenderMaster.h"
#include "IO/Logger/Logger.h"
#include "Graphics/Texture/ResourceRegisterer.h"
#include "Graphics/GameGUI/Minimap.h"
#include "Graphics/GameGUI/PlayTime.h"
#include "World/Entity/Player.h"
#include "GlobalSettings.h"

RenderMaster::RenderMaster() 
	: m_tileRenderer(m_resources, m_modelShaders), m_entityRenderer(m_modelShaders) {
	m_contextManager.setClearColor(0.6f, 0.46f, 0.46f);
	m_contextManager.addContext(m_tileContext)
		.enableTerminationUponErrors()
		.enableDepthTest()
		.enableMultisampling()
		.enableCullFace()
		.enableBlending();

	m_contextManager.addContext(m_entityContext)
		.enableTerminationUponErrors()
		.enableDepthTest()
		.enableMultisampling()
		.enableBlending();

	io::Logger::debug("RenderMaster: created OpenGL contexts");

	m_modelShaders["fog_power"] = GlobalSettings::get().getFogPower();

	ResourceRegisterer registerer(m_resources);
	registerer.registerAll();
	io::Logger::debug("RenderMaster: loaded resources");

	m_minimap = m_guiRenderer.registerGameGUI<gamegui::Minimap>(math::Vector2f(0.7f, -1.f + 0.05f));
	io::Logger::debug("RenderMaster: created minimap");

	m_playtime = m_guiRenderer.registerGameGUI<gamegui::PlayTime>(math::Vector2f(0.7f, 0.85f));
	io::Logger::debug("RenderMaster: created playtime");
	io::Logger::trace("RenderMaster: initialized");
}

void RenderMaster::setPlayerData(const Player& player) {
	m_minimap->setPlayerPos(player.getPos());
	m_modelShaders["is_blind"] = player.isBlind();
	m_modelShaders["player_pos"] = glm::vec3(player.getPos().x(), 0.5f, player.getPos().y());

	if (player.isBlind()) {
		m_contextManager.setClearColor(1.f, 1.f, 1.f);
	} else {
		m_contextManager.setClearColor(0.6f, 0.46f, 0.46f);
	}
}

void RenderMaster::drawEntity(const EntityId id, model::EntityModel& entityModel) {
	m_entityRenderer.addEntity(&entityModel);

	if (id != EntityId::PLAYER) {
		m_minimap->addEnemy(math::Vector2f(
			entityModel.getSceneObject().pos.x, 
			entityModel.getSceneObject().pos.z
		).roundFloor().to<int32_t>());
	}
}

void RenderMaster::drawTile(const TileId id, const math::Vector2f& position, const math::DirectionFlag VNS) {
	if (id.getCategory() == TileCategory::WALL) {
		m_tileRenderer.addTile(position, id, VNS);
	} else {
		m_tileRenderer.addTile(position, id);
	}

	m_minimap->setTile(id, position.roundFloor().to<int32_t>());
}

void RenderMaster::render(sf::RenderWindow& window, Camera& camera) {
	// Core OpenGL using code

	m_modelShaders["proj_view_matrix"] = camera.genProjViewMatrix();

	m_contextManager.newFrame();
	m_contextManager.forContext(m_entityContext, [this, &window, &camera]() {
		m_entityRenderer.render(window, camera, m_resources);
	});

	m_contextManager.forContext(m_tileContext, [this, &window, &camera]() {
		m_tileRenderer.render(window, camera);
	});

	m_contextManager.endFrame();

	// SFML using code
	// Note: SFML uses some legacy OpenGL functions, so it cannot be mixed up with the core OpenGL

	window.resetGLStates();

	m_minimap->update();
	m_playtime->update();
	m_guiRenderer.render(window, camera);
}

GameGUIRenderer& RenderMaster::getGameGuiRenderer() noexcept {
	return m_guiRenderer;
}

ResourceManager& RenderMaster::getResources() noexcept {
	return m_resources;
}
