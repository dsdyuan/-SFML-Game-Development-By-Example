#include "entityManager.h"
#include "systemManager.h"

EntityManager::EntityManager(SystemManager* l_sysMgr, TextureManager* l_textureMgr) : m_idCounter(0), m_systems(l_sysMgr), m_textureManager(l_textureMgr)
{
	AddComponentType<CPosition>(Component::Position);
	
	// Not yet implemented:
	AddComponentType<CSpriteSheet>(Component::SpriteSheet);
	AddComponentType<CState>(Component::State);
	AddComponentType<CMovable>(Component::Movable);
	AddComponentType<CController>(Component::Controller);
	AddComponentType<CCollidable>(Component::Collidable);
}

EntityManager::~EntityManager() { 
	Purge(); 
}

int EntityManager::AddEntity(const Bitmask& l_mask)
{
	unsigned int entity = m_idCounter;

	if (!m_entities.emplace(entity, EntityData(0, ComponentContainer())).second)
		return -1;

	++m_idCounter;

	for (unsigned int i = 0; i < N_COMPONENT_TYPES; ++i)
	{
		if (l_mask.GetBit(i))
			AddComponent(entity, (Component)i);
	}

	m_systems->EntityModified(entity, l_mask);
	m_systems->AddEvent(entity, (EventID)EntityEvent::Spawned);

	return entity;
}

int EntityManager::AddEntity(const std::string& l_entityFile)
{
	int EntityId = -1;

	std::ifstream file;

	file.open(Utils::GetWorkingDirectory() + "media/Entities/" + l_entityFile + ".entity");

	if (!file.is_open())
	{
		std::cout << "! Failed to load entity: " << l_entityFile << std::endl;
		return -1;
	}

	std::string line;

	while (std::getline(file, line))
	{
		if (line[0] == '|') 
			continue;

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Name")
		{

		}
		else if (type == "Attributes")
		{
			if (EntityId != -1) { continue; }
			Bitset set = 0;
			Bitmask mask;
			keystream >> set;
			mask.SetMask(set);
			EntityId = AddEntity(mask);
			if (EntityId == -1) { return -1; }
		}
		else if (type == "Component")
		{
			if (EntityId == -1) { continue; }
			unsigned int c_id = 0;
			keystream >> c_id;
			CBase* component = GetComponent<CBase>(EntityId, (Component)c_id);
			if (!component) { continue; }
			keystream >> *component;
			if (component->GetType() == Component::SpriteSheet)
			{
				CSpriteSheet* sheet = (CSpriteSheet*)component;
				sheet->Create(m_textureManager);
			}
		}
	}
	file.close();
	return EntityId;
}

bool EntityManager::RemoveEntity(const EntityId& l_id)
{
	auto itr = m_entities.find(l_id);
	if (itr == m_entities.end()) 
		return false;
	
	while (itr->second.second.begin() != itr->second.second.end())
	{
		delete itr->second.second.back();
		itr->second.second.pop_back();
	}

	m_entities.erase(itr);
	m_systems->RemoveEntity(l_id);

	return true;
}

bool EntityManager::AddComponent(const EntityId& l_entity, const Component& l_component)
{
	auto itr = m_entities.find(l_entity);

	if (itr == m_entities.end()) 
		return false;
	
	if (itr->second.first.GetBit((unsigned int)l_component)) 
		return false;

	auto itr2 = m_cFactory.find(l_component);
	if (itr2 == m_cFactory.end()) { return false; }

	CBase* component = itr2->second();
	itr->second.second.emplace_back(component);
	itr->second.first.TurnOnBit((unsigned int)l_component);
	
	m_systems->EntityModified(l_entity, itr->second.first);

	return true;
}

bool EntityManager::RemoveComponent(const EntityId& l_entity, const Component& l_component)
{
	auto itr = m_entities.find(l_entity);
	if (itr == m_entities.end()) 
		return false;
	
	if (!itr->second.first.GetBit((unsigned int)l_component))
		return false;
	
	auto& container = itr->second.second;
	auto component = std::find_if(container.begin(), container.end(), [&l_component](CBase* c) { return c->GetType() == l_component; });
	
	if (component == container.end()) 
		return false;

	delete (*component);
	container.erase(component);
	itr->second.first.ClearBit((unsigned int)l_component);

	m_systems->EntityModified(l_entity, itr->second.first);

	return true;
}

bool EntityManager::HasComponent(const EntityId& l_entity, const Component& l_component)
{
	auto itr = m_entities.find(l_entity);
	
	if (itr == m_entities.end()) 
		return false;
	
	return itr->second.first.GetBit((unsigned int)l_component);
}

void EntityManager::Purge()
{
	m_systems->PurgeEntities();

	for (auto& entity : m_entities)
	{
		for (auto &component : entity.second.second) 
			delete component;

		entity.second.second.clear();
		entity.second.first.Clear();
	}

	m_entities.clear();
	m_idCounter = 0;
}