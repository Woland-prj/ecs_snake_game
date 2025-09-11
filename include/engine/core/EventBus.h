#ifndef EVENTBUS_H
#define EVENTBUS_H
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ecs_engine::core
{
class EventBus
{
public:
	template <typename EventType>
	using Handler = std::function<void(const EventType&)>;

	EventBus() = default;

	template <typename EventType>
	void Subscribe(Handler<EventType> handler)
	{
		auto& handlers = m_subscribers[typeid(EventType)];
		handlers.push_back([handler = std::move(handler)](const void* event) {
			handler(*static_cast<const EventType*>(event));
		});
	}

	template <typename EventType>
	void Publish(const EventType& event)
	{
		auto it = m_subscribers.find(typeid(EventType));
		if (it != m_subscribers.end())
		{
			for (auto& h : it->second)
			{
				h(&event);
			}
		}
	}

private:
	using RawHandler = std::function<void(const void*)>;
	std::unordered_map<std::type_index, std::vector<RawHandler>> m_subscribers;
};
} // namespace ecs_engine::core

#endif // EVENTBUS_H
