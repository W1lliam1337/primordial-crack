#pragma once
#include "reviver.hxx"

namespace dmpr::segment {
    _INLINE c_reviver::c_reviver( ) noexcept {
        utils::g_logger->info( "Running a routine..." );
        {
            extract_segment( );
            setup_patches( );
            resolve_imports( );
        }

        const auto hooks{ std::make_unique< segment::c_hooks >( ) };
        invoke_oep( );        
    }
} // namespace dmpr::segment