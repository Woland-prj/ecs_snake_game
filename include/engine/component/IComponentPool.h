#ifndef ICOMPONENTPOOL_H
#define ICOMPONENTPOOL_H
#include "entity/EntityIdPool.h"


namespace ecs_engine::component
{
class IComponentPool
{
public:
	virtual void Deallocate(entity::EntityId entityId) = 0;
	virtual ~IComponentPool() = default;
};
}

#endif //ICOMPONENTPOOL_H
