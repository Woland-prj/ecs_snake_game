#include "GraphicsInputSystem.h"
#include "Components.h"
#include "Events.h"
#include <csignal>

namespace game
{

void GraphicsInputSystem::Init()
{
	EventBus()->Subscribe<WindowCreatedEvent>([this](const WindowCreatedEvent& evt) {
		OnWindowCreated(evt);
	});
	EventBus()->Subscribe<CollisionEvent>([this](const CollisionEvent& evt) {
		OnCollide();
	});
}

void GraphicsInputSystem::OnWindowCreated(const WindowCreatedEvent& evt)
{
	m_window = &evt.window;
}

void GraphicsInputSystem::OnCollide()
{
	m_isPause = true;
}

void GraphicsInputSystem::Tick()
{
	if (m_window == nullptr)
		return;

	while (const std::optional event = m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window->close();
			std::raise(SIGINT);
			return;
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			Direction newDir{ 0, 0 };
			wchar_t dirCh = 0;

			switch (keyPressed->scancode)
			{
			case sf::Keyboard::Scancode::Up:
			case sf::Keyboard::Scancode::W:
				newDir = m_dirMap.at(Dir::UP);
				dirCh = HEAD_UP_CHAR;
				break;

			case sf::Keyboard::Scancode::Down:
			case sf::Keyboard::Scancode::S:
				newDir = m_dirMap.at(Dir::DOWN);
				dirCh = HEAD_DOWN_CHAR;
				break;

			case sf::Keyboard::Scancode::Left:
			case sf::Keyboard::Scancode::A:
				newDir = m_dirMap.at(Dir::LEFT);
				dirCh = HEAD_LEFT_CHAR;
				break;

			case sf::Keyboard::Scancode::Right:
			case sf::Keyboard::Scancode::D:
				newDir = m_dirMap.at(Dir::RIGHT);
				dirCh = HEAD_RIGHT_CHAR;
				break;

			default:
				break;
			}

			if (newDir != zeroDir)
			{
				for (auto id : Entities())
				{
					if (auto* currDir = ComponentManager()->GetComponent<Direction>(id))
					{
						if ((*currDir + newDir) == zeroDir)
							continue;
						*currDir = newDir;
						if (auto* headSym = ComponentManager()->GetComponent<Symbol>(id))
						{
							headSym->ch = dirCh;
						}
					}
				}
			}
		}
	}
}

} // namespace game