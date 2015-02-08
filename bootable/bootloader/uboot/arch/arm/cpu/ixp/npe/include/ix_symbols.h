

#if !defined(__IX_SYMBOLS_H__)
#define __IX_SYMBOLS_H__


#if defined(__cplusplus)
extern "C"
{
#endif /* end defined(__cplusplus) */

#if (_IX_OS_TYPE_ == _IX_OS_WIN32_)
#    if defined(_IX_LIB_INTERFACE_IMPLEMENTATION_)
#        define IX_EXPORT_FUNCTION __declspec( dllexport )
#    elif defined(_IX_LIB_INTERFACE_IMPORT_DLL_)
#        define IX_EXPORT_FUNCTION __declspec( dllimport )
#    else
#        define IX_EXPORT_FUNCTION extern 
#    endif
#elif (_IX_OS_TYPE_ == _IX_OS_WINCE_)
#    define IX_EXPORT_FUNCTION __declspec(dllexport)
#else
#    define IX_EXPORT_FUNCTION  extern
#endif


#define _IX_MULTI_THREADED_     1
    

/* #define _IX_RM_EXPLICIT_SINGLE_THREADED_    1  */

#if defined(__cplusplus)
}
#endif /* end defined(__cplusplus) */

#endif /* end !defined(__IX_SYMBOLS_H__) */
