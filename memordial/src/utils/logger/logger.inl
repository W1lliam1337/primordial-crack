#pragma once
#include "logger.hxx"

namespace dmpr::utils {
    _INLINE c_logger_system::c_logger_system( const std::string_view title ) noexcept {
        _ASSERT( !title.empty( ) );

        // Allocating and initializing console for logging.
        _ASSERT( this->m_allocated = ( ::AllocConsole( ) != 0 ) );

        this->m_stream.reset( std::freopen( "CONOUT$", "w", stdout ) );
        _ASSERT( this->m_stream != nullptr );

        _ASSERT( ::SetConsoleTitleA( title.data( ) ) != 0 );

        // Implementation of log level methods.
        const auto win_color_sink{ std::make_shared< spdlog::sinks::wincolor_stdout_sink_mt >( ) };
        win_color_sink->set_color( spdlog::level::debug, FOREGROUND_RED | FOREGROUND_GREEN );
        win_color_sink->set_color( spdlog::level::trace, FOREGROUND_INTENSITY );
        win_color_sink->set_color( spdlog::level::info,
                                   FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
        win_color_sink->set_color( spdlog::level::warn, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        win_color_sink->set_color( spdlog::level::err, FOREGROUND_RED | FOREGROUND_INTENSITY );
        win_color_sink->set_color( spdlog::level::critical, FOREGROUND_RED );

        const auto sinks{ std::to_array< spdlog::sink_ptr >( {
            std::make_shared< spdlog::sinks::basic_file_sink_mt >( "engine.log", true ),
#ifndef _DEBUG
            win_color_sink,
#endif
        } ) };

        this->m_logger = std::make_unique< spdlog::logger >( title.data( ), sinks.begin( ), sinks.end( ) );
        this->m_logger->set_pattern( "%^[%H:%M:%S][%t][%l] %v%$" );

#ifndef _DEBUG
        this->m_logger->set_level( spdlog::level::trace );
#endif
    }

    template < typename... args_t >
    constexpr void c_logger_system::trace( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept {
        m_logger->trace( fmt, std::forward< args_t >( args_list )... );
    }

    template < typename str_t > constexpr void c_logger_system::trace( const str_t& txt ) noexcept {
        m_logger->trace( txt );
    }

    template < typename... args_t >
    constexpr void c_logger_system::debug( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept {
        m_logger->debug( fmt, std::forward< args_t >( args_list )... );
    }

    template < typename str_t > constexpr void c_logger_system::debug( const str_t& txt ) noexcept {
        m_logger->debug( txt );
    }

    template < typename... args_t >
    constexpr void c_logger_system::info( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept {
        m_logger->info( fmt, std::forward< args_t >( args_list )... );
    }

    template < typename str_t > constexpr void c_logger_system::info( const str_t& txt ) noexcept {
        m_logger->info( txt );
    }

    template < typename... args_t >
    constexpr void c_logger_system::warning( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept {
        m_logger->warn( fmt, std::forward< args_t >( args_list )... );
    }

    template < typename str_t > constexpr void c_logger_system::warning( const str_t& txt ) noexcept {
        m_logger->warn( txt );
    }

    template < typename... args_t >
    constexpr void c_logger_system::error( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept {
        m_logger->error( fmt, std::forward< args_t >( args_list )... );
    }

    template < typename str_t > constexpr void c_logger_system::error( const str_t& txt ) noexcept {
        m_logger->error( txt );
    }

    template < typename... args_t >
    constexpr void c_logger_system::critical( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept {
        m_logger->critical( fmt, std::forward< args_t >( args_list )... );
    }

    template < typename str_t > constexpr void c_logger_system::critical( const str_t& txt ) noexcept {
        m_logger->critical( txt );
    }
} // namespace dmpr::utils