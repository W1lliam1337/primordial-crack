#pragma once
#include "../../common.hxx"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/wincolor_sink.h>
#include <spdlog/spdlog.h>

namespace dmpr::utils {
    class c_logger_system {
    public:
        explicit _INLINE c_logger_system( const std::string_view title ) noexcept;

        template < typename... args_t >
        constexpr void trace( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void trace( const str_t& txt ) noexcept;

        template < typename... args_t >
        constexpr void debug( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void debug( const str_t& txt ) noexcept;

        template < typename... args_t >
        constexpr void info( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void info( const str_t& txt ) noexcept;

        template < typename... args_t >
        constexpr void warning( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void warning( const str_t& txt ) noexcept;

        template < typename... args_t >
        constexpr void error( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void error( const str_t& txt ) noexcept;

        template < typename... args_t >
        constexpr void critical( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void critical( const str_t& txt ) noexcept;
    private:
        struct file_destructor_t {
            static void operator( )( std::FILE* file ) noexcept { std::fclose( file ); }
        };

        std::unique_ptr< std::FILE, file_destructor_t > m_stream{ };
        std::unique_ptr< spdlog::logger > m_logger{ };
        bool m_allocated{ };
    };

    inline auto g_logger{ std::unique_ptr< c_logger_system >{} };
} // namespace dmpr::utils

#include "logger.inl"