#pragma once
#include <cstdint>

class RNG
{
public:
    RNG();
    RNG(uint64_t r_id);
    RNG(const RNG&) = default;

    operator uint64_t() const { return m_RNG; }
private:
    uint64_t m_RNG;
};

namespace std {
template <typename T> struct hash;

template<>
struct hash<RNG>
{
    size_t operator()(const RNG& r_id) const
    {
        return (uint64_t)r_id;
    }
};
}