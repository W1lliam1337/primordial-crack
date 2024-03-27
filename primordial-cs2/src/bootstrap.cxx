#include "core/context/context.hxx"

bool _STDCALL DllMain( void* module, const std::uint8_t reason, [[maybe_unused]] void* const reserved ) {
    switch ( reason ) {
        case DLL_PROCESS_ATTACH:

        {
            auto context{ std::unique_ptr< dmpr::c_context >{} };
            if ( context )
                context.reset( );

            context = std::make_unique< dmpr::c_context >( );
            return static_cast< bool >( context );
        }
        default:
            break;
    }

    return false;
}
