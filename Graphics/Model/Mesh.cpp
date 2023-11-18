// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Mesh.h"

#include <format>
#include <glm/gtx/rotate_vector.hpp>

#include "Math/Cmath.h"

model::Mesh& model::Mesh::optimize() {
    if (getVerticesCount() <= 1) {
        return *this; // Nothing to optimize
    }
    
    struct VertexNode { // Temporary struct
        float x, y, z; // The current vertex's coords
        float texX, texY; // The current vertex's texture coords
        GLuint newIndex; // The new index of the vertex
    };
     
    // Not the best algorithm, but pretty simple
    // We just find all the repetitive vertices and refer them to the first instance

    size_t verticesCount = getVerticesCount();
    std::vector<VertexNode> verticesRemap;
    bool needOptimizing = false; // It is set to true is we have any duplicates

    verticesRemap.reserve(verticesCount);

    for (size_t i = 0; i < verticesCount; i++) {
        size_t vertexIndex = i * 3;
        size_t texIndex = i * 2;

        verticesRemap.emplace_back(
            vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2],
            texCoords[texIndex], texCoords[texIndex + 1], i
        );
        
        // Looking for previous nodes that are duplicates to the current
        VertexNode& current = verticesRemap.back();
        for (size_t j = 0; j < i; j++) {
            VertexNode& node = verticesRemap[j];
            
            if (node.x == current.x && node.y == current.y && node.z == current.z
                && node.texX == current.texX && node.texY == current.texY) { // A hit!

                current.newIndex = node.newIndex;
                needOptimizing = true;
                break;
            }
        }
    }

    if (!needOptimizing) {
        return *this; // The mesh is already optimal
    }

    // Now we just have to apply the new indices

    for (auto& index : indices) {
        index = verticesRemap[index].newIndex;
    }

    vertices.clear();
    texCoords.clear();

    for (auto& node : verticesRemap) {
        vertices.push_back(node.x);
        vertices.push_back(node.y);
        vertices.push_back(node.z);

        texCoords.push_back(node.texX);
        texCoords.push_back(node.texY);
    }

    return *this;
}

model::Mesh& model::Mesh::mergeWith(const Mesh& other) {
    GLuint lastVertexIdx = getVerticesCount();
    size_t lastIndexIdx = indices.size();

    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());
    texCoords.insert(texCoords.end(), other.texCoords.begin(), other.texCoords.end());
    indices.insert(indices.end(), other.indices.begin(), other.indices.end());

    for (; lastIndexIdx < indices.size(); lastIndexIdx++) {
        indices[lastIndexIdx] += lastVertexIdx;
    }

    return *this;
}

model::Mesh& model::Mesh::setTexCoords(gl::Vertices texCoords) {
    this->texCoords = std::move(texCoords);

    return *this;
}

model::Mesh& model::Mesh::reverseIndices() {
    for (size_t i = 0; i < indices.size(); i += 3) {
        std::swap(indices[i + 2], indices[i + 1]);
    }

    return *this;
}

model::Mesh& model::Mesh::move(const glm::vec3& shift) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
        vertices[i] += shift.x;
        vertices[i + 1] += shift.y;
        vertices[i + 2] += shift.z;
    }

    return *this;
}

model::Mesh& model::Mesh::rotate(const glm::vec3& angles) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glm::vec3 tmp(vertices[i], vertices[i + 1], vertices[i + 2]);
        tmp = glm::rotateX(tmp, angles.x);
        tmp = glm::rotateY(tmp, angles.y);
        tmp = glm::rotateZ(tmp, angles.z);

        vertices[i] = tmp.x;
        vertices[i + 1] = tmp.y;
        vertices[i + 2] = tmp.z;
    }

    return *this;
}

model::Mesh& model::Mesh::rotateAround(const glm::vec3& center, const glm::vec3& angles) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glm::vec3 tmp(vertices[i], vertices[i + 1], vertices[i + 2]);

        tmp -= center; // So that the center is (0, 0, 0)

        tmp = glm::rotateX(tmp, angles.x);
        tmp = glm::rotateY(tmp, angles.y);
        tmp = glm::rotateZ(tmp, angles.z);

        tmp += center; // Translate back

        vertices[i] = tmp.x;
        vertices[i + 1] = tmp.y;
        vertices[i + 2] = tmp.z;
    }

    return *this;
}

model::Mesh& model::Mesh::scale(const float factor) {
    for (auto& vertex : vertices) {
        vertex *= factor;
    }

    return *this;
}

utils::Result<utils::Void> model::Mesh::validate() {
    if (vertices.size() % 3 != 0) {
        return utils::Failure("vertices are not 3D: each points must consist of 3 values, but there is not a valid number of values");
    } if (texCoords.size() % 2 != 0) {
        return utils::Failure("texture coords are not 2D: each points must consist of 2 values, but there is not a valid number of values");
    } if (vertices.size() / 3 != texCoords.size() / 2) {
        return utils::Failure("there must be exactly one texture coordinate for each vertex, but it is not so: sizes do not match");
    }

    for (auto index : indices) {
        if (index >= vertices.size()) {
            return utils::Failure(std::format(
                "one of indices is out of range: {}, but there are only {} vertices", 
                index, 
                vertices.size()
            ));
        }
    }

    for (auto vertexVal : vertices) {
        if (!math::Cmath::isFinite(vertexVal)) {
            return utils::Failure("one of the vertices is " + 
                                              (math::Cmath::isNan(vertexVal) 
                                               ? std::string("NaN") 
                                               : std::string("Inf"))
            );
        }
    }

    for (auto vertexVal : texCoords) {
        if (!math::Cmath::isFinite(vertexVal)) {
            return utils::Failure("one of the texture coords is " +
                                              (math::Cmath::isNan(vertexVal)
                                               ? std::string("NaN")
                                               : std::string("Inf"))
            );
        }
    }

    return utils::Success();
}
