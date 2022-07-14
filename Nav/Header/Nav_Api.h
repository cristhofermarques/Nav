#ifndef NAV_API_H
#define NAV_API_H

#ifdef NAV_API_EXPORT

#ifdef __cplusplus

#define NAV_API extern "C" __declspec(dllexport)

#else 

#define NAV_API __declspec(dllexport)

#endif // __cplusplus

#else

#ifdef __cplusplus

#define NAV_API extern "C" __declspec(dllimport)

#else

#define NAV_API __declspec(dllimport)

#endif // __cplusplus

#endif // NAV_API_EXPORT

#endif // NAV_API_H