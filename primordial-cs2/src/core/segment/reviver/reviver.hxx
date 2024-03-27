#pragma once
#include "../../../common.hxx"
#include "../../../utils/logger/logger.hxx"
#include "../hooks/hooks.hxx"

namespace dmpr::segment {
    class c_reviver {
    public:
        explicit _INLINE c_reviver( ) noexcept;
    private:
        enum e_alloc_params : std::uint8_t { e_type, e_protect, e_size };

        static inline constexpr std::array< int, e_alloc_params::e_size > m_alloc_params{ MEM_COMMIT | MEM_RESERVE,
                                                                                          PAGE_EXECUTE_READWRITE };

        /**
         * @brief Extracts segment.
         *
         * This function allocates memory and copies the segment data into it.
         */
        static void extract_segment( );

        /**
         * @brief Resolves addresses of imported functions.
         *
         * This function iterates through the list of imported functions, validates the module name,
         * resolves their addresses using GetProcAddress and LoadLibraryA, and sets the addresses.
         */
        static void resolve_imports( ) noexcept;

        /**
         * @brief Sets up patches.
         *
         * This function sets up memory patches.
         */
        static void setup_patches( );

        /**
         * @brief Invokes original entry point.
         *
         * This function invokes the original entry point of the segment.
         */
        static void invoke_oep( ) noexcept;
    };
} // namespace dmpr::segment

#include "reviver.inl"