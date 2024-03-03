#include "rng.h"

#include <random>
#include <unordered_map>

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

namespace Nebel
{
    RNG::RNG() : m_RNG(s_UniformDistribution(s_Engine)) {}
    RNG::RNG(uint64_t r_id) : m_RNG(r_id) {}
} // namespace Nebel