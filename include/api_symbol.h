#define SHAROM_SYMBOL
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define SHAROM_SYMBOL_IMPORT __declspec(dllimport)
  #define SHAROM_SYMBOL_EXPORT __declspec(dllexport)
  #define SHAROM_SYMBOL_LOCAL
#else
  #if __GNUC__ >= 4
    #define SHAROM_SYMBOL_IMPORT __attribute__ ((visibility ("default")))
    #define SHAROM_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
    #define SHAROM_SYMBOL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define SHAROM_SYMBOL_IMPORT
    #define SHAROM_SYMBOL_EXPORT
    #define SHAROM_SYMBOL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define SHAROM_API and SHAROM_LOCAL.
// SHAROM_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// SHAROM_LOCAL is used for non-api symbols.
//inspired by https://gcc.gnu.org/wiki/Visibility

#ifdef SHAROM_SYMBOL // defined if SHAROM is compiled as a shared library
  #ifdef SHAROM_SYMBOL_EXPORTS // defined if we are building the SHAROM_SYMBOL (instead of using it)
    #define SHAROM_API SHAROM_SYMBOL_EXPORT
  #else
    #define SHAROM_API SHAROM_SYMBOL_IMPORT
  #endif // SHAROM_SYMBOL_EXPORTS
  #define SHAROM_LOCAL SHAROM_SYMBOL_LOCAL
#else // SHAROM_SYMBOL is not defined: this means SHAROM is a static library
  #define SHAROM_LOCAL
#endif // SHAROM_SYMBOL