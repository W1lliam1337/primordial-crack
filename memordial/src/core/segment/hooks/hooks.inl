#pragma once
#include "hooks.hxx"

namespace dmpr::segment {
    _INLINE c_hooks::c_hooks( ) noexcept {
        utils::g_logger->info( "Creating hooks..." );

        static const auto string_encryption{ reinterpret_cast< void* >( native::g_base_address + 0xee20 ) },
            wolfssl_read_address{ reinterpret_cast< void* >( native::g_base_address + 0x19b8f0 ) },
            svg_data_render{ reinterpret_cast< void* >( native::g_base_address + 0x11d970 ) },
            init_logo{ reinterpret_cast< void* >( native::g_base_address + 0x11a960 ) };

        const auto mh_status{ MH_Initialize( ) };
        utils::g_logger->info(
            std::vformat( "MH init status: {}", std::make_format_args( MH_StatusToString( mh_status ) ) ) );

        HOOK( send, hk_send, m_send );
        HOOK( recv, hk_recv, m_recv );
        HOOK( connect, hk_connect, m_connect );

        HOOK( wolfssl_read_address, hk_wolfssl_read, m_wolfssl_read );
        HOOK( string_encryption, hk_string_encryption, m_string_encryption );
        HOOK( svg_data_render, hk_svg_data_render, m_svg_data_render );
        HOOK( init_logo, hk_init_logo, m_init_logo );
    }
} // namespace dmpr::segment