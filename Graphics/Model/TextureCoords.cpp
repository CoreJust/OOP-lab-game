// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TextureCoords.h"
#include "Graphics/Texture/Texture.h"

model::TextureCoords::TextureCoords() : m_unitSize(1.f) { }

model::TextureCoords::TextureCoords(const math::Vector2f& unitSize) : m_unitSize(unitSize) { }

model::TextureCoords::TextureCoords(const math::Vector2u& imageSize)
    : m_unitSize(
        Texture::TEXTURE_SIZE / imageSize.to<float>().x(),
        Texture::TEXTURE_SIZE / imageSize.to<float>().y()
    ) { }

model::TextureCoords& model::TextureCoords::addTextureRect(const math::Rectf& rect) {
    addFace(rect.multByCoords(m_unitSize));
    return *this;
}

model::TextureCoords& model::TextureCoords::addTextureBox(const math::Vector2f& pos, float bX, float bY, float bZ) {
    bX *= m_unitSize.x();
    bY *= m_unitSize.y();

    const float y1 = pos.y() * m_unitSize.y();
    const float x1 = pos.x() * m_unitSize.x();

    const float y2 = y1 + bZ * m_unitSize.y();

    bZ *= m_unitSize.x();
    const float x2 = x1 + bZ;

    const float y3 = y2 + bY;
    const float x3 = x2 + bX;
    const float x4 = x3 + bZ;
    const float x5 = x4 + bX;
    const float x4Down = x3 + bX;

    addFace(math::Rectf(x4, y2, x5, y3)); // back
    addFace(math::Rectf(x3, y1, x4Down, y2)); // bottom
    addFace(math::Rectf(x3, y2, x4, y3)); // left
    addFace(math::Rectf(x2, y1, x3, y2)); // top
    addFace(math::Rectf(x2, y2, x3, y3)); // front
    addFace(math::Rectf(x1, y2, x2, y3)); // right

    return *this;
}

model::TextureCoords& model::TextureCoords::addTextureRect(const math::Rectu& rect) {
    addFace((rect.to<float>() / Texture::TEXTURE_SIZE).multByCoords(m_unitSize));
    return *this;
}

model::TextureCoords& model::TextureCoords::addTextureBox(const math::Vector2u& pos, const uint32_t bX, const uint32_t bY, const uint32_t bZ) {
    return addTextureBox(
        pos.to<float>() / Texture::TEXTURE_SIZE,
        float(bX) / Texture::TEXTURE_SIZE, 
        float(bY) / Texture::TEXTURE_SIZE, 
        float(bZ) / Texture::TEXTURE_SIZE
    );
}

model::TextureCoords& model::TextureCoords::addFace(const math::Rectf& rect) {
    m_texCoords.insert(m_texCoords.end(), { 
        rect.left(),  rect.down(),
        rect.right(),  rect.down(),
        rect.right(), rect.top(),
        rect.left(), rect.top()
    });

    return *this;
}

model::TextureCoords& model::TextureCoords::repeat(uint8_t count) {
    if (count == 0) {
        m_texCoords.clear();
        return *this;
    } else if (count == 1) {
        return *this;
    }

    m_texCoords.reserve(m_texCoords.size() * count);
    size_t size = m_texCoords.size();
    while (count-- > 1) {
        m_texCoords.insert(m_texCoords.end(), m_texCoords.begin(), m_texCoords.begin() + size); // Fine because of reservation
    }

    return *this;
}

gl::Vertices&& model::TextureCoords::extract() {
    return std::move(m_texCoords);
}

const gl::Vertices& model::TextureCoords::get() const {
    return m_texCoords;
}
