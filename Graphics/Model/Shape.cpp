// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Shape.h"

model::Mesh model::Shape::createMesh() {
    if (m_id == ShapeId::EMPTINESS) {
        return Mesh();
    } else if (m_id == ShapeId::FLAT_FLOOR || m_id == ShapeId::FLAT_FLOOR_OBJECT) {
        return Mesh {
            { // Vertices
                0.f, 0.f, 0.f,
                0.f, 0.f, 1.f,
                1.f, 0.f, 1.f,
                1.f, 0.f, 0.f
            },
            {}, // Tex coords
            { // Indices
                0, 1, 2,
                2, 3, 0
            }
        }.setTexCoords(std::move(m_texCoords));
    }
    
    assert(false && "wrong shape id");
#ifdef NDEBUG
    std::terminate();
#endif // NDEBUG
}

model::Mesh model::Shape::createMesh(const glm::vec3& from, const glm::vec3& to) {
    if (m_id == ShapeId::QUAD) { // One of the coords of from and to must be the same
        if (from.x == to.x) {
            return Mesh {
                { // Vertices
                    from.x, from.y, from.z,
                    from.x, from.y, to.z,
                    from.x, to.y,   to.z,
                    from.x, to.y,   from.z,
                },
                {}, // Tex coords
                { // Indices
                    0, 1, 2,
                    2, 3, 0
                }
            }.setTexCoords(std::move(m_texCoords));
        } else if (from.y == to.y) {
            return Mesh {
                { // Vertices
                    from.x, from.y, from.z,
                    from.x, from.y, to.z,
                    to.x,   from.y, to.z,
                    to.x,   from.y, from.z,
                },
                {}, // Tex coords
                { // Indices
                    0, 1, 2,
                    2, 3, 0
                }
            }.setTexCoords(std::move(m_texCoords));
        } else if (from.z == to.z) {
            return Mesh {
                { // Vertices
                    from.x, from.y, from.z,
                    to.x,   from.y, from.z,
                    to.x,   to.y,   from.z,
                    from.x, to.y,   from.z,
                },
                { }, // Tex coords
                { // Indices
                    0, 1, 2,
                    2, 3, 0
                }
            }.setTexCoords(std::move(m_texCoords));
        } else {
            assert(false && "one of the coordinates must be the same for from and to");
        }
    } else if (m_id == ShapeId::BOX) {
        return Shape(ShapeId::QUAD).createMesh(from, { to.x, to.y, from.z }).reverseIndices() // back
            .mergeWith(Shape(ShapeId::QUAD).createMesh(from, { to.x, from.y, to.z }).reverseIndices()) // bottom
            .mergeWith(Shape(ShapeId::QUAD).createMesh(from, { from.x, to.y, to.z })) // left
            .mergeWith(Shape(ShapeId::QUAD).createMesh({ from.x, to.y, from.z }, to)) // top
            .mergeWith(Shape(ShapeId::QUAD).createMesh({ from.x, from.y, to.z }, to)) // front
            .mergeWith(Shape(ShapeId::QUAD).createMesh({ to.x, from.y, from.z }, to).reverseIndices()) // right
            .setTexCoords(std::move(m_texCoords))
            .optimize();
    }
        
    assert(false && "wrong shape id");
#ifdef NDEBUG
    std::terminate();
#endif // NDEBUG
}

model::Mesh model::Shape::createMesh(const math::DirectionFlag flags) {
    assert(m_id == ShapeId::SIMPLE_WALL);

    Mesh result;

    if (flags & math::DirectionFlag::UP) {
        result.mergeWith(Shape(ShapeId::QUAD).createMesh({ 0, 0, 0 }, { 1, 2, 0 }).reverseIndices());
    } if (flags & math::DirectionFlag::DOWN) {
        result.mergeWith(Shape(ShapeId::QUAD).createMesh({ 0, 0, 1 }, { 1, 2, 1 }));
    } if (flags & math::DirectionFlag::LEFT) {
        result.mergeWith(Shape(ShapeId::QUAD).createMesh({ 0, 0, 0 }, { 0, 2, 1 }));
    } if (flags & math::DirectionFlag::RIGHT) {
        result.mergeWith(Shape(ShapeId::QUAD).createMesh({ 1, 0, 0 }, { 1, 2, 1 }).reverseIndices());
    }

    return result
        .setTexCoords(std::move(m_texCoords))
        .optimize();
}

model::Mesh model::Shape::createMesh(const float width, const float height, const float depth) {
    assert(m_id == ShapeId::FLOOR_BOX);

    glm::vec3 from(0.5f - width / 2.f, 0, 0.5f - depth / 2.f);
    glm::vec3 to(0.5f + width / 2.f, height, 0.5f + depth / 2.f);
    return Shape(ShapeId::BOX, std::move(m_texCoords)).createMesh(from, to);
}
