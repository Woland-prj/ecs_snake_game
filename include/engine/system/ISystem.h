#ifndef ISYSTEM_H
#define ISYSTEM_H
#include "core/EventBus.h"
#include "entity/EntityManager.h"

namespace ecs_engine::system
{
class ISystem
{
	friend class SystemManager;

protected:
	virtual void InitSystem(component::ComponentManager* componentManager, entity::EntityManager* entityManager, core::EventBus* eventBus) = 0;

public:
	virtual ~ISystem() = default;
	virtual void Init() = 0;
	virtual void Tick() = 0;
};
} // namespace ecs_engine::system

#endif // ISYSTEM_H
