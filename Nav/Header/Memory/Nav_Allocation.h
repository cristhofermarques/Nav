#ifndef NAV_ALLOC_H
#define NAV_ALLOC_H

#include <stdlib.h>

#define NAV_MEMORY_ALLOCATE(bufferSize) malloc(bufferSize)

#define NAV_MEMORY_DEALLOCATE(bufferPointer) free(bufferPointer)

#define NAV_MEMORY_REALLOCATE(bufferPointer, newBufferSize) realloc(bufferPointer, newBufferSize)

#endif // NAV_ALLOC_H