#include "reviver.hxx"
#include "../native/native.hxx"
#include "../native/primo_segment.hxx"

namespace dmpr::segment {
    void c_reviver::extract_segment( ) noexcept {
        // Allocate memory.
        const auto allocation{ ::VirtualAlloc( reinterpret_cast< void* >( native::g_base_address ),
                                               native::g_segment_size, m_alloc_params.at( e_alloc_params::e_type ),
                                               m_alloc_params.at( e_alloc_params::e_protect ) ) };

        _ASSERT( allocation );

        // Copy segment data.
        std::memcpy( reinterpret_cast< void* >( native::g_base_address ), g_primo_segment.data( ),
                     native::g_segment_size );

        utils::g_logger->info(
            std::vformat( "Successfully extracted segment at {} with alloc params: [{} | {}]",
                          std::make_format_args( reinterpret_cast< void* >( native::g_base_address ),
                                                 m_alloc_params.at( e_alloc_params::e_type ),
                                                 m_alloc_params.at( e_alloc_params::e_protect ) ) ) );
    }

    void c_reviver::resolve_imports( ) noexcept {
        _ASSERT( !native::g_imports.empty( ) );

        utils::g_logger->info( std::vformat( "Resolving imports... [{}]", std::make_format_args( __FUNCTION__ ) ) );

        // Base address for importing functions.
        static constexpr auto iat_start{ native::g_iat_base_address };

        for ( const auto& [ address, module_name, function_name ] : native::g_imports ) {
            // @Todo: _ASSERT >>>
            const auto module_handle{ ::LoadLibraryA( module_name.data( ) ) };
            if ( !module_handle ) [[unlikely]] {
                utils::g_logger->error( "Failed to get module handle" );
                continue;
            }

            // Get the address of the function.
            const auto function_address{ reinterpret_cast< std::uint64_t >(
                ::GetProcAddress( module_handle, function_name.data( ) ) ) };
            if ( !function_address ) [[unlikely]] {
                utils::g_logger->error( "Failed to get function address" );
                continue;
            }

            // Set the address.
            *reinterpret_cast< std::uint64_t* const >( iat_start + address ) = function_address;
        }
    }

    void c_reviver::setup_patches( ) noexcept {
        [[maybe_unused]] auto patch_memory = [ = ]( void* address, const void* data, const std::size_t size ) {
            DWORD old_protect{ };
            VirtualProtect( address, size, m_alloc_params.at( e_alloc_params::e_protect ), &old_protect );
            std::memcpy( address, data, size );
            VirtualProtect( address, size, old_protect, &old_protect );
        };

        std::memset( reinterpret_cast< void* >( native::g_base_address + native::g_wolfssl_patch ), 0x90, 0x6 );
        std::memset( reinterpret_cast< void* >( native::g_base_address + native::g_second_wolfssl_patch ), 0x90, 0x2 );
    }

    void c_reviver::invoke_oep( ) noexcept {
        const auto oep{ reinterpret_cast< native::dll_main_t >( native::g_base_address + native::g_oep ) };
        _ASSERT( oep );

        utils::g_logger->info( std::vformat( "Invoking OEP... [{}]", std::make_format_args( __FUNCTION__ ) ) );

        oep( nullptr, DLL_PROCESS_ATTACH, reinterpret_cast< void* >( native::g_base_address ) );

        utils::g_logger->info( "https://en1gma.tech" );
    }
} // namespace dmpr::segment