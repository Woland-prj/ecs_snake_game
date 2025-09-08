#ifndef POOLALREADYEXISTERROR_H
#define POOLALREADYEXISTERROR_H
#include <stdexcept>
#include <string>

namespace ecs_engine::component
{
class PoolAlreadyExistsError final : public std::runtime_error
{
public:
	explicit PoolAlreadyExistsError(const std::string& type)
		: std::runtime_error(std::string("Pool already allocated for ") + type)
	{
	}
};
}

#endif //POOLALREADYEXISTERROR_H
