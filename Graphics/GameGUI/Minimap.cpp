// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Minimap.h"
#include "TextAdapter.h"

gamegui::Minimap::Minimap(const math::Vector2f& pos) 
	: m_playerPos(0, 0) {
	// The minimap
	sf::Sprite* minimap = emplaceDrawable<sf::Sprite>();
	minimap->setPosition(pos.toSfml());
	minimap->setScale(MINIMAP_SCALE_BASE * 0.6f, MINIMAP_SCALE_BASE);

	// Bounds of the minimap
	const uint32_t boundingImageSize = 2 + MINIMAP_SIZE;
	const sf::Color boundsColor = sf::Color(0xff, 0xd8, 0x70);

	m_minimap.create(
		boundingImageSize,
		boundingImageSize,
		sf::Color::Black // Transparent by default
	);

	for (uint32_t i = 0; i < boundingImageSize; i++) {
		m_minimap.setPixel(i,					  0,					 boundsColor);
		m_minimap.setPixel(i,					  boundingImageSize - 1, boundsColor);
		m_minimap.setPixel(0,					  i,					 boundsColor);
		m_minimap.setPixel(boundingImageSize - 1, i,					 boundsColor);
	}

	m_minimapTexture.loadFromImage(m_minimap);
	minimap->setTexture(m_minimapTexture);
}

void gamegui::Minimap::setPlayerPos(const math::Vector2f& pos) {
	m_playerPos = pos.roundFloor().to<int32_t>();

	// Clearing the minimap
	for (auto pos : math::Rectu(1, 1, MINIMAP_SIZE, MINIMAP_SIZE)) {
		m_minimap.setPixel(pos.x(), pos.y(), sf::Color::Black);
	}
}

void gamegui::Minimap::setTile(const TileId id, const math::Vector2i& pos) {
	math::Vector2i relPos = m_playerPos - pos + MINIMAP_SIZE / 2 + 1;
	if (!relPos.isToDownRightFrom({ 1, 1 }) || !relPos.isToUpLeftFrom(MINIMAP_SIZE)) {
		return; // Out of minimap
	}

	relPos.y() = MINIMAP_SIZE - relPos.y() + 1; // Inversion

	const TileCategory cat = id.getCategory();
	switch (cat) {
		case TileCategory::EMPTINESS: m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color::Black); break;
		case TileCategory::FLOOR: m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color(0xDA, 0xDA, 0xDA)); break;
		case TileCategory::WALL: m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color(0xA8, 0xA8, 0xA8)); break;
		case TileCategory::FLOOR_OBJECT: m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color::Blue); break;
		case TileCategory::WALL_OBJECT: m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color::Yellow); break;
	default: m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color::Black); break;
	}
}

void gamegui::Minimap::addEnemy(const math::Vector2i& pos) {
	math::Vector2i relPos = m_playerPos - pos + MINIMAP_SIZE / 2 + 1;
	if (!relPos.isToDownRightFrom({ 1, 1 }) || !relPos.isToUpLeftFrom(MINIMAP_SIZE)) {
		return; // Out of minimap
	}

	relPos.y() = MINIMAP_SIZE - relPos.y() + 1; // Inversion

	m_minimap.setPixel(relPos.x(), relPos.y(), sf::Color::Red);
}

void gamegui::Minimap::update() {
	m_minimap.setPixel(MINIMAP_SIZE / 2 + 1, MINIMAP_SIZE / 2 + 1, sf::Color::Green); // The player

	sf::Sprite* minimap = (sf::Sprite*)m_drawables[0].get();
	m_minimapTexture.loadFromImage(m_minimap);
	minimap->setTexture(m_minimapTexture);
}
