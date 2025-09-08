#include "system/SystemManager.h"
#include "system/ISystem.h"

namespace ecs_engine::system
{

SystemManager::SystemManager(component::ComponentManager* componentManager, entity::EntityManager* entityManager)
	: m_componentManager(componentManager), m_entityManager(entityManager)
{
}

void SystemManager::InitAll() const
{
	for (const auto& sys : m_systems)
	{
		sys->Init();
	}
}

void SystemManager::TickAll() const
{
	for (const auto& sys : m_systems)
	{
		sys->Tick();
	}
}

}