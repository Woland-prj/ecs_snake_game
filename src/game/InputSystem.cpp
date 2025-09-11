#include "InputSystem.h"
#include "Components.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

namespace game
{
struct TermiosGuard
{
	termios oldt;
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

void InputSystem::Init()
{
	static TermiosGuard guard;
}

void InputSystem::Tick()
{
	constexpr char Esc = '\033';
	char c;
	ssize_t n = read(STDIN_FILENO, &c, 1);
	if (n <= 0)
		return;

	int dx = 0, dy = 0;

	// Cтрелки (ANSI escape seq)
	if (c == Esc)
	{
		char seq[2];
		if (read(STDIN_FILENO, &seq, 2) == 2 && seq[0] == '[')
		{
			switch (seq[1])
			{
			case 'A':
				dx = 0;
				dy = -1;
				break; // вверх
			case 'B':
				dx = 0;
				dy = 1;
				break; // вниз
			case 'C':
				dx = 1;
				dy = 0;
				break; // вправо
			case 'D':
				dx = -1;
				dy = 0;
				break; // влево
			}
		}
	}
	else
	{
		// WASD
		switch (c)
		{
		case 'w':
			dx = 0;
			dy = -1;
			break;
		case 's':
			dx = 0;
			dy = 1;
			break;
		case 'd':
			dx = 1;
			dy = 0;
			break;
		case 'a':
			dx = -1;
			dy = 0;
			break;
		}
	}

	if (dx != 0 || dy != 0)
	{
		for (auto id : Entities())
		{
			auto* dir = ComponentManager()->GetComponent<Direction>(id);
			if (dir)
			{
				if (dir->dx + dx == 0 && dir->dy + dy == 0)
					continue;
				dir->dx = dx;
				dir->dy = dy;
			}
		}
	}
}

} // namespace game
