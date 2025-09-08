#ifndef COMPONENT_H
#define COMPONENT_H
#include "IComponent.h"

namespace ecs_engine::component
{


class Component : IComponent
{
private:
	ComponentId m_ComponentId;
	bool m_Active;
	void SetEntityId(entity::EntityId id) override;

public:
	Entity();
};
}

#endif //COMPONENT_H
