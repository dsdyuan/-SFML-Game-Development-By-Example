#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <array>
#include <fstream>
#include <sstream>
#include "utilities.h"
#include "sharedContext.h"
#include "baseState.h"

enum Sheet { TileSize = 32, SheetWidth = 256, SheetHeight = 256	};

using TileID = unsigned int;

struct TileInfo
{
	TileInfo(SharedContext* l_context, const std::string& l_texture = "", TileID l_id = 0)
		: m_context(l_context), m_id(0), m_deadly(false)
	{
		TextureManager* tmgr = l_context->m_textureManager;
		
		if (l_texture == "")
		{
			m_id = l_id;
			return;
		}

		if (!tmgr->RequireResource(l_texture))
			return;

		m_texture = l_texture;
		m_id = l_id;

		m_sprite.setTexture(*tmgr->GetResource(m_texture));

		sf::IntRect tileBoundaries(m_id % (Sheet::SheetWidth / Sheet::TileSize) * Sheet::TileSize,
								   m_id / (Sheet::SheetHeight / Sheet::TileSize) * Sheet::TileSize,
								   Sheet::TileSize, 
								   Sheet::TileSize);

		m_sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo()
	{
		if (m_texture == "")
			return;

		m_context->m_textureManager->ReleaseResource(m_texture);
	}

	sf::Sprite m_sprite;

	TileID m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;

	SharedContext* m_context;
	std::string m_texture;
};

struct Tile
{
	TileInfo* m_properties;
	bool m_warp;
};

using TileMap = std::unordered_map<TileID, Tile*>;
using TileSet = std::unordered_map<TileID, TileInfo*>;

class Map
{
public:
	Map(SharedContext* l_context, BaseState* l_currentState);
	~Map();

	Tile* GetTile(unsigned int l_x, unsigned int l_y);
	TileInfo* GetDefaultTile();
	float GetGravity() const;
	unsigned int GetTileSize() const;
	const sf::Vector2u& GetMapSize() const;
	const sf::Vector2f& GetPlayerStart() const;

	void LoadMap(const std::string& l_path);
	void LoadNext();
	void Update(float l_dT);
	void Draw();

private:
	unsigned int ConvertCoords(unsigned int l_x, unsigned int l_y);

	void LoadTiles(const std::string& l_path);
	void PurgeMap();
	void PurgeTileSet();

	TileSet m_tileSet;
	TileMap m_tileMap;
	TileInfo m_defaultTile;

	BaseState* m_currentState;
	SharedContext* m_context;
	
	sf::Sprite m_background;
	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	
	std::string m_nextMap;
	std::string m_backgroundTexture;

	unsigned int m_tileCount;
	unsigned int m_tileSetCount;
	float m_mapGravity;
	
	bool m_loadNextMap;
};