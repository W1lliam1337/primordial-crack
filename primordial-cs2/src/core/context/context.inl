#pragma once
#include "context.hxx"

namespace dmpr {
    _INLINE c_context::c_context( ) {
        utils::g_logger = std::make_unique< utils::c_logger_system >( "en1gma.tech" );

        const auto reviver{ std::make_unique< segment::c_reviver >( ) };
    }
} // namespace dmpr