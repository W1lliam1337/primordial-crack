#pragma once

#define _CDECL __attribute__( ( cdecl ) )
#define _STDCALL __attribute__( ( stdcall ) )
#define _THISCALL __attribute__( ( thiscall ) )
#define _FASTCALL __attribute__( ( fastcall ) )
#define _VECTORCALL __attribute__( ( vectorcall ) )
#define _HIDDEN __attribute__( ( visibility( "hidden" ) ) )
#define _NAKED __attribute__( ( naked ) )
#define _INLINE inline __attribute__( ( always_inline ) )
#define _NO_INLINE __attribute__( ( noinline ) )

#if defined( __has_builtin )
    #define _HAS_BUILTIN( feature ) __has_builtin( feature )
#else
    #define _HAS_BUILTIN( feature ) 0
#endif

#if _HAS_BUILTIN( __builtin_debugtrap )
    #define _DEBUG_BREAK( ) __builtin_debugtrap( )
#endif

#if defined( _DEBUG_BREAK )
    #if defined( _DEBUG )
        #define _ASSERT( expression ) \
            static_cast< void >( static_cast< bool >( expression ) || ( ( _DEBUG_BREAK( ), 0 ) != 0 ) )
    #elif _HAS_BUILTIN( __builtin_unreachable )
        #define _ASSERT( expression ) \
            static_cast< void >( static_cast< bool >( expression ) || ( __builtin_unreachable( ), 0 ) )
    #else
        #define _ASSERT( expression ) static_cast< void >( expression )
    #endif
#endif

#undef min
#undef max