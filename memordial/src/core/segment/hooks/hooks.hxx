#pragma once
#include "../../../common.hxx"
#include "../../../utils/logger/logger.hxx"
#include "../native/native.hxx"

#include <minhook/MinHook.h>

// clang-format off
#include <winsock.h>
#include <windows.h>
// clang-format on

#pragma comment( lib, "ws2_32.lib" )

#define HOOK( target, detour, og )                                                                       \
    if ( MH_CreateHook( target, detour, reinterpret_cast< void** >( &( og ) ) ) == MH_OK                 \
         && MH_EnableHook( target ) == MH_OK ) {                                                         \
        utils::g_logger->info( std::vformat( "Created target: {}", std::make_format_args( #target ) ) ); \
    }

namespace dmpr::segment {
    class c_hooks {
    public:
        explicit _INLINE c_hooks( ) noexcept;
    private:
        /**
         * @brief Hook for string encryption function.
         *
         * This function intercepts calls to string encryption function and logs the input string
         * until it matches the string "signatures".
         *
         * @param a1 Function argument 1.
         * @param a2 Input string.
         * @param a3 Function argument 3.
         * @param a4 Function argument 4.
         * @param a5 Function argument 5.
         * @param a6 Function argument 6.
         * @param a7 Function argument 7.
         * @param a8 Function argument 8.
         * @param a9 Function argument 9.
         * @return Returns the result of the original string encryption function.
         */
        static void* _FASTCALL hk_string_encryption( void* a1, const char* a2, std::uintptr_t a3, int a4, int a5,
                                                     std::int64_t a6, std::int64_t a7, std::int64_t a8,
                                                     std::int64_t a9 ) noexcept;
        /**
         * @brief Hook for rendering svg data.
         *
         * This function is hooked to render svg data.
         * @param rcx The rcx parameter.
         * @return Returns the result of the data render.
         */
        static bool _FASTCALL hk_svg_data_render( void* rcx );

        /**
         * @brief Hook for initializing the logo.
         *
         * This function is hooked to initialize the logo.
         * @param a1 Parameter a1.
         * @param a2 Parameter a2.
         * @param a3 Parameter a3.
         * @param a4 Parameter a4.
         * @return Returns a pointer.
         */
        static void* _FASTCALL hk_init_logo( int a1, int a2, void* a3, int a4 );

        /**
         * @brief Hook for send function.
         *
         * This function intercepts calls to send function and returns immediately
         * if the socket matches a predefined value.
         *
         * @param s Socket.
         * @param buf Buffer.
         * @param len Length.
         * @param flags Flags.
         * @return Returns the result of the original send function.
         */
        static int hk_send( SOCKET s, const char* buf, int len, int flags ) noexcept;

        /**
         * @brief Hook for receive function.
         *
         * This function intercepts calls to receive function and returns data
         * from a predefined buffer if the socket matches a predefined value.
         *
         * @param s Socket.
         * @param buf Buffer to receive data.
         * @param len Length.
         * @param flags Flags.
         * @return Returns the result of the original receive function.
         */
        static int hk_recv( SOCKET s, char* buf, int len, int flags ) noexcept;

        /**
         * @brief Hook for connect function.
         *
         * This function intercepts calls to connect function and sets a specific socket
         * value if the return address falls within a specific memory range.
         *
         * @param s Socket.
         * @param name Address.
         * @param namelen Length.
         * @return Returns the result of the original connect function.
         */
        static BOOL hk_connect( SOCKET s, const sockaddr* name, int namelen ) noexcept;

        /**
         * @brief Hook for wolfssl read function.
         *
         * This function intercepts calls to wolfssl read function and returns data
         * from a predefined buffer.
         *
         * @param sockfd Socket.
         * @param buf Buffer to receive data.
         * @param count Length.
         * @return Returns the result of the original wolfssl read function.
         */
        static int hk_wolfssl_read( int sockfd, void* buf, std::size_t count ) noexcept;

        static inline decltype( &hk_string_encryption ) m_string_encryption{ };
        static inline decltype( &hk_send ) m_send{ };
        static inline decltype( &hk_recv ) m_recv{ };
        static inline decltype( &hk_connect ) m_connect{ };
        static inline decltype( &hk_wolfssl_read ) m_wolfssl_read{ };
        static inline decltype( &hk_svg_data_render ) m_svg_data_render{ };
        static inline decltype( &hk_init_logo ) m_init_logo{ };
    };
} // namespace dmpr::segment

#include "hooks.inl"
#undef HOOK