#pragma once
#include "data/iat.hxx"
#include "data/network.hxx"
#include "data/oep.hxx"

namespace dmpr::segment::inline native {
    static inline constexpr std::uintptr_t g_base_address{ 0x236f9330000 }, g_segment_size{ 0xa13000 };
} // namespace dmpr::segment::inline native