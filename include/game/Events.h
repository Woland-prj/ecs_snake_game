#ifndef EVENTS_H
#define EVENTS_H
#include <SFML/Graphics.hpp>

namespace game
{

struct CollisionEvent
{
};

struct GrowingEvent
{
};

struct WindowCreatedEvent
{
	sf::RenderWindow& window;
};

} // namespace game

#endif // EVENTS_H
