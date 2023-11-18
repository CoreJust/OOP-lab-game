// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "DynamicModelDescription.h"

model::DynamicModelDescription::DynamicModelDescription(SceneObject SO, ModelDescription MD) noexcept
    : m_sceneObject(std::move(SO)),
    m_modelDescription(std::move(MD)), 
    m_texCoords(TextureAtlas().genTexCoordsGenerator()) {

}

model::DynamicModelDescription model::DynamicModelDescription::makeBox(
    SceneObject SO, 
    const glm::vec3& from, 
    const glm::vec3& size, 
    const math::Vector2f& texCoordsFrom
) {
    return DynamicModelDescription(
            std::move(SO), ModelDescription(ShapeId::BOX, from, from + size)
        ).forTexCoords(
            [&texCoordsFrom, &size](TextureCoords& texCoords) { 
                texCoords.addTextureBox(texCoordsFrom, size.x, size.y, size.z); 
            })
        .move();
}

model::DynamicModelDescription& model::DynamicModelDescription::addSubModelDesc(DynamicModelDescription DMD) {
    m_submodelDescriptions.emplace_back(std::move(DMD));

    return *this;
}
