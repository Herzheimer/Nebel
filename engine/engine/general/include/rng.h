#pragma once
#include <cstdint>

namespace Nebel
{
    struct RNG
    {
        RNG();
        RNG(uint64_t r_id);
        RNG(const RNG&) = default;

        operator uint64_t() const { return m_RNG; }
    private:
        uint64_t m_RNG;
    };
} // namespace Nebel

namespace std {
template <typename T> struct hash;

template<>
struct hash<Nebel::RNG>
{
    size_t operator()(const Nebel::RNG& r_id) const
    {
        return (uint64_t)r_id;
    }
};
}