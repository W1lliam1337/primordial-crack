#pragma once
#include "../../common.hxx"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/wincolor_sink.h>
#include <spdlog/spdlog.h>

namespace dmpr::utils {
    class c_logger_system {
    public:
        /**
         * @brief Constructs a c_logger_system object.
         *
         * @param title The title for the logger.
         */
        explicit _INLINE c_logger_system( const std::string_view title ) noexcept;

        /**
         * @brief Logs a trace message.
         *
         * @tparam args_t The argument types for formatting.
         * @param fmt The format string.
         * @param args_list The arguments for formatting.
         */
        template < typename... args_t >
        constexpr void trace( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void trace( const str_t& txt ) noexcept;

        /**
         * @brief Logs a debug message.
         *
         * @tparam args_t The argument types for formatting.
         * @param fmt The format string.
         * @param args_list The arguments for formatting.
         */
        template < typename... args_t >
        constexpr void debug( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void debug( const str_t& txt ) noexcept;

        /**
         * @brief Logs an info message.
         *
         * @tparam args_t The argument types for formatting.
         * @param fmt The format string.
         * @param args_list The arguments for formatting.
         */
        template < typename... args_t >
        constexpr void info( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void info( const str_t& txt ) noexcept;

        /**
         * @brief Logs a warning message.
         *
         * @tparam args_t The argument types for formatting.
         * @param fmt The format string.
         * @param args_list The arguments for formatting.
         */
        template < typename... args_t >
        constexpr void warning( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void warning( const str_t& txt ) noexcept;

        /**
         * @brief Logs an error message.
         *
         * @tparam args_t The argument types for formatting.
         * @param fmt The format string.
         * @param args_list The arguments for formatting.
         */
        template < typename... args_t >
        constexpr void error( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void error( const str_t& txt ) noexcept;

        /**
         * @brief Logs a critical message.
         *
         * @tparam args_t The argument types for formatting.
         * @param fmt The format string.
         * @param args_list The arguments for formatting.
         */
        template < typename... args_t >
        constexpr void critical( std::format_string< args_t... > fmt, args_t&&... args_list ) noexcept;

        template < typename str_t > constexpr void critical( const str_t& txt ) noexcept;
    private:
        /**
         * @brief Struct for file destructor.
         */
        struct file_destructor_t {
            static void operator( )( std::FILE* file ) noexcept { std::fclose( file ); }
        };

        std::unique_ptr< std::FILE, file_destructor_t > m_stream{ }; ///< The file stream for logging.
        std::unique_ptr< spdlog::logger > m_logger{ };               ///< The logger instance.
        bool m_allocated{ };                                         ///< Flag indicating if the console is allocated.
    };

    inline auto g_logger{ std::unique_ptr< c_logger_system >{} };
} // namespace dmpr::utils

#include "logger.inl"