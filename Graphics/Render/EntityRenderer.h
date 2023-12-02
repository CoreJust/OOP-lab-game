// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Utils/NoNullptr.h"
#include "Math/Vector.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Shader/EntityShader.h"
#include "Graphics/Shader/ModelShaderRegistry.h"
#include "Graphics/Model/EntityModel.h"

/*
*	EntityRenderer(.h/.cpp) contains a class that implements a renderer
*	responsible for rendering the entities - the player, the enemies, etc.
*/

class EntityRenderer final {
private:
	std::vector<utils::NoNullptr<model::EntityModel>> m_entities;

	ModelShaderRegistry& m_pMSR;
	EntityShader m_shader;

public:
	EntityRenderer(ModelShaderRegistry& msr);

	void addEntity(utils::NoNullptr<model::EntityModel> model);

	void render(sf::RenderWindow& window, Camera& camera, ResourceManager& resources);
};