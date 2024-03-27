#pragma once
#include "hooks.hxx"

namespace dmpr::segment {
    c_hooks::c_hooks( ) noexcept {
        utils::g_logger->info( "Creating hooks..." );

        const auto string_encryption{ reinterpret_cast< void* >( native::g_base_address + 0xee20 ) },
            wolfssl_read_address{ reinterpret_cast< void* >( native::g_base_address + 0x19b8f0 ) };

        _ASSERT( MH_Initialize( ) );

        HOOK( send, hk_send, m_send );
        HOOK( recv, hk_recv, m_recv );
        HOOK( connect, hk_connect, m_connect );

        HOOK( wolfssl_read_address, hk_wolfssl_read, m_wolfssl_read );
        HOOK( string_encryption, hk_string_encryption, m_string_encryption );
    }
} // namespace dmpr::segment