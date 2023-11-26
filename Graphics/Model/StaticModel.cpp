// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "StaticModel.h"

#include "Graphics/GL/GLVBO.h"
#include "Graphics/GL/GLEBO.h"

model::StaticModel::StaticModel() : m_sceneObject { .pos = { 0, 0, 0 }, .rot = { 0, 0, 0 } } {
    m_vao.create();
}

model::StaticModel::StaticModel(StaticModel&& other) noexcept
    : m_sceneObject(std::move(other.m_sceneObject)),
    m_buffers(std::move(other.m_buffers)),
    m_vao(std::move(other.m_vao)),
    m_vboCount(other.m_vboCount),
    m_indicesCount(other.m_indicesCount)
{
    
}

model::StaticModel::~StaticModel() {
    clear();
}

void model::StaticModel::render(ModelShader& shader) {
    shader.setSceneObject(m_sceneObject);

    bind();
    glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    unbind();
}

void model::StaticModel::clear() {
    for (auto& buffer : m_buffers) {
        buffer->releaseIfNotEmpty();
    }

    m_buffers.clear();
    m_vao.releaseIfNotEmpty();

    m_vboCount = 0;
    m_indicesCount = 0;
}

void model::StaticModel::setSceneObject(const SceneObject& value) {
    m_sceneObject = value;
}

void model::StaticModel::setMesh(const Mesh& mesh) {
    clear();

    m_vao.create();
    m_vao.bind();

    addVBO(mesh.vertices, 3);
    addVBO(mesh.texCoords, 2);
    addEBO(mesh.indices);

    m_vao.unbind();
}

void model::StaticModel::addVBO(const gl::Vertices& vertices, const GLint dims) {
    gl::VBO vbo;
    vbo.create();
    vbo.bind();

    vbo.setData(vertices);
    vbo.setVertexAttribute(m_vboCount++, dims);

    m_buffers.emplace_back(std::make_unique<gl::VBO>(std::move(vbo)));
}

void model::StaticModel::addEBO(const gl::Indices& indices) {
    gl::EBO ebo;
    ebo.create();
    ebo.bind();

    ebo.setData(indices);

    m_indicesCount += indices.size();
    m_buffers.emplace_back(std::make_unique<gl::EBO>(std::move(ebo)));
}

void model::StaticModel::bind() {
    m_vao.bind();
}

void model::StaticModel::unbind() {
    m_vao.unbind();
}

const model::SceneObject& model::StaticModel::getSceneObject() const noexcept {
    return m_sceneObject;
}

const gl::VAO& model::StaticModel::getVAO() const noexcept {
    return m_vao;
}

GLuint model::StaticModel::getIndicesCount() const noexcept {
    return m_indicesCount;
}
