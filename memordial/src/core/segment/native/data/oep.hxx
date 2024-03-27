#pragma once
#include "../../../../common.hxx"
#include <cstdint>

namespace dmpr::segment::inline native {
    static inline constexpr std::uintptr_t g_oep{ 0x255c44 };
    typedef void( _STDCALL* dll_main_t )( HMODULE, std::uintptr_t, void* );
} // namespace dmpr::segment::inline native