#ifndef NAV_FUNCTION_POINTER_H
#define NAV_FUNCTION_POINTER_H


#define NAV_FUNCTION_POINTER_DEFINE(returnType, functionName, ...) returnType (* functionName)(__VA_ARGS__)
#define NAV_FUNCTION_POINTER_CALL(function, ...) (* function)(__VA_ARGS__)


#endif // NAV_FUNCTION_POINTER_H