#ifndef SIGNATURE_H
#define SIGNATURE_H
#define MAX_COMPONENTS 32
#include <bitset>

namespace ecs_engine::core
{
using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif // SIGNATURE_H
