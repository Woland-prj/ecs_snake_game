#include "TextInputSystem.h"
#include "Components.h"
#include "Events.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

namespace game
{
struct TermiosGuard
{
	termios oldt{};
	TermiosGuard()
	{
		tcgetattr(STDIN_FILENO, &oldt);
		termios newt = oldt;
		// raw - отключаю буферизацию
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		// простой неблокирующий ввод
		fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	}
	~TermiosGuard()
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
};

void TextInputSystem::Init()
{
	static TermiosGuard guard;
	EventBus()->Subscribe<CollisionEvent>([this](const CollisionEvent& event) {
		OnCollide();
	});
}

void TextInputSystem::OnCollide()
{
	m_isPause = true;
}

uint8_t TextInputSystem::ReadRawBytes(const ssize_t count, char* buff)
{
	const ssize_t n = read(STDIN_FILENO, buff, count);
	if (n <= 0)
		return false;
	return n;
}

void TextInputSystem::Tick()
{
	if (m_isPause)
		return;
	char c;
	if (!ReadRawBytes(1, &c))
		return;

	Direction newDir{};
	wchar_t dirCh = HEAD_UP_CHAR;

	// Cтрелки (ANSI escape seq)
	if (c == Esc)
	{
		if (char seq[2]; ReadRawBytes(2, seq) == 2 && seq[0] == '[')
		{
			switch (seq[1])
			{
			case ARROW_UP:
				newDir = m_dirMap.at(Dir::UP);
				dirCh = HEAD_UP_CHAR;
				break;
			case ARROW_DOWN:
				newDir = m_dirMap.at(Dir::DOWN);
				dirCh = HEAD_DOWN_CHAR;
				break;
			case ARROW_RIGHT:
				newDir = m_dirMap.at(Dir::RIGHT);
				dirCh = HEAD_RIGHT_CHAR;
				break;
			case ARROW_LEFT:
				newDir = m_dirMap.at(Dir::LEFT);
				dirCh = HEAD_LEFT_CHAR;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		// WASD
		switch (c)
		{
		case WASD_UP:
			newDir = m_dirMap.at(Dir::UP);
			dirCh = HEAD_UP_CHAR;
			break;
		case WASD_DOWN:
			newDir = m_dirMap.at(Dir::DOWN);
			dirCh = HEAD_DOWN_CHAR;
			break;
		case WASD_RIGHT:
			newDir = m_dirMap.at(Dir::RIGHT);
			dirCh = HEAD_RIGHT_CHAR;
			break;
		case WASD_LEFT:
			newDir = m_dirMap.at(Dir::LEFT);
			dirCh = HEAD_LEFT_CHAR;
			break;
		default:
			break;
		}
	}

	if (newDir != zeroDir)
	{
		for (const auto id : Entities())
		{
			if (auto* currDir = ComponentManager()->GetComponent<Direction>(id))
			{
				if ((*currDir + newDir) == zeroDir)
					continue;
				*currDir = newDir;
				auto* headSymbol = ComponentManager()->GetComponent<Symbol>(id);
				headSymbol->ch = dirCh;
			}
		}
	}
}

} // namespace game
