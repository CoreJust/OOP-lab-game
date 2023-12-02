// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Graphics/GL/GLContextManager.h"
#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Camera.h"
#include "EntityRenderer.h"
#include "TileRenderer.h"
#include "GameGUIRenderer.h"

/*
*	RenderMaster(.h/.cpp) contains the main class for graphics.
*
*	It manages the graphics module and incapsulates it.
*	
*	Usage:
*		1. Create a RenderMaster on the high-level:
*			RenderMaster renderMaster;
* 
*		2. Pass it on through the game's classes hierarchy
*		   via the draw(renderMaster, ...) calls.
*			<some object that is rendered in the game>.draw(renderMaster, ...);
*			<another such object>.draw(renderMaster, ...);
* 
*		3. In all the renderable objects push the information about them
*		   to the renderMaster via its corresponding drawXXX(...) method:
*		   renderMaster.drawXXX(<some information required by the method>);
* 
*		4. Finally, trigger the actual rendering on the high level:
*		   renderMaster.render();
*			
*	Notes about the class's work:
*		 The general idea of the RenderMaster is that you load into it all the information 
*		about the rendered objects in the representation that is used by the game.
*		 The RenderMaster than distributes it to the corresponding XXXRenderers
*		and on the render() call, all the renderers are called in the required order
*		while the RenderMaster sets the requiered graphic settings.
*		 Like this, you do not need to worry about how the objects are actually rendered
*		from the outside - you just have to inform the RenderMaster of their existance.
*		The RenderMaster then renders them on its own, and it may very well by the 2D, 3D,
*		or even mere console graphics.
*/

class Player;

namespace gamegui {
	class Minimap;
	class PlayTime;
}

class RenderMaster final {
private:
	ResourceManager m_resources;
	ModelShaderRegistry m_modelShaders;

	EntityRenderer m_entityRenderer;
	TileRenderer m_tileRenderer;
	GameGUIRenderer m_guiRenderer;

	gl::ContextManager m_contextManager;
	gl::ContextManager::ContextRef m_tileContext;
	gl::ContextManager::ContextRef m_entityContext;

	gamegui::Minimap* m_minimap;
	gamegui::PlayTime* m_playtime;

public:
	RenderMaster();

	void setPlayerData(const Player& player);
	void drawEntity(model::EntityModel& entityModel);
	void drawTile(const TileId id, const math::Vector2f& position, const math::DirectionFlag VNS);

	void render(sf::RenderWindow& window, Camera& camera);

	GameGUIRenderer& getGameGuiRenderer() noexcept;
	ResourceManager& getResources() noexcept;

	constexpr gamegui::PlayTime* getPlayTime() noexcept {
		return m_playtime;
	}
};