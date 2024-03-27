#include "hooks.hxx"
#include <regex>

namespace dmpr::segment {
    void* _FASTCALL c_hooks::hk_string_encryption( void* a1,
                                                   const char* a2,
                                                   const std::uintptr_t a3,
                                                   const int a4,
                                                   const int a5,
                                                   const std::int64_t a6,
                                                   const std::int64_t a7,
                                                   const std::int64_t a8,
                                                   const std::int64_t a9 ) {
        /* @Note:
         * Ducari and his xor technology is a bit silly, and passes strings in bare form.
         * Thanks dukari for recording the progress of initializing the cheat in init_log.txt.
         */

        // Log the input string.
        // utils::g_logger->info( std::vformat( "{}", std::make_format_args( a2 ) ) );

        return m_string_encryption( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
    }

    int PASCAL FAR c_hooks::hk_send( _In_ const SOCKET s,
                                     _In_reads_bytes_( len ) const char FAR* buf,
                                     _In_ const int len,
                                     _In_ const int flags ) {
        return s == native::g_primo_socket ? len
                                           : m_send( s, buf, len, flags ); // Return immediately for a specific socket.
    }

    int PASCAL FAR c_hooks::hk_recv( _In_ const SOCKET s,
                                     _Out_writes_bytes_to_( len, return ) __out_data_source( NETWORK ) char FAR* buf,
                                     _In_ const int len,
                                     _In_ const int flags ) {
        /*
         * @Note: was used to dump the necessary data.
            std::printf( "[ recv %d ] checking buf: 0x", len );
            for ( int i = 0; i < len; i++ ) {
                if ( i > 0 )
                    printf( ", 0x" );
                std::printf( "%02X", ( unsigned char ) ( buf[ i ] ) );
            }
            std::printf( "\n" );
        */

        static int counter{ };
        if ( s == native::g_primo_socket ) {
            if ( counter < native::g_recv_data.size( ) ) {
                // Return data from a predefined buffer.
                std::memcpy(
                    buf, native::g_recv_data.at( counter ).data( ), native::g_recv_data.at( counter ).size( ) );
                counter++;
                return len;
            }

            // All data from the buffer has been read, reset the counter.
            counter = 0;
        }

        return m_recv( s, buf, len, flags );
    }

    BOOL PASCAL c_hooks::hk_connect( _In_ const SOCKET s,
                                     _In_reads_bytes_( namelen ) const struct sockaddr FAR* name,
                                     _In_ const int namelen ) {

        /*
         * Client also connecting to 198.251.83.148
         * Thanks ducari for not hiding the IP address the cheat connects to, lol.
         * seg000:00000236F9628280 a19825183148    db '198.251.83.148',0
         * seg000:00000236F962828F                 align 10h
         */

        const auto return_address{ __builtin_extract_return_addr( __builtin_return_address( 0 ) ) };
        if ( return_address >= reinterpret_cast< void* >( native::g_base_address )
             && return_address < reinterpret_cast< void* >( native::g_base_address + native::g_segment_size ) ) {
            native::g_primo_socket = s; // Set a specific socket value.
            return true;
        }

        return m_connect( s, name, namelen );
    }

    int c_hooks::hk_wolfssl_read( int sockfd, void* buf, std::size_t count ) {
        static int current_stage{ };

        // Return data from a predefined buffer.
        if ( current_stage < static_cast< int >( native::g_wolfssl_buf_data.size( ) ) ) {
            std::memcpy( buf,
                         native::g_wolfssl_buf_data.at( current_stage ).data( ),
                         native::g_wolfssl_buf_data.at( current_stage ).size( ) );

            const auto result{ native::g_wolfssl_results.at( current_stage ) };
            current_stage++;

            return result;
        }

        // All stages of reading data from the buffer have been completed, reset the counter.
        current_stage = 0;

        return m_wolfssl_read( sockfd, buf, count );
    }
} // namespace dmpr::segment