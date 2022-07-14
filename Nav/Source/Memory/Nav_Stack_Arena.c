#include <Memory/Nav_Stack_Arena.h>
#include <Memory/Nav_Allocation.h>

Nav_Memory_StackArenaAllocation Nav_Memory_StackArena_Allocate(Nav_Memory_StackArena* stackArena, UInt64 size)
{
    Nav_Memory_StackArenaAllocation stackArenaAlloc = NullStruct;

    if(stackArena == NullPtr){return stackArenaAlloc;}

    if(stackArena->peek + size > stackArena->size){return stackArenaAlloc;}

    char* stackArenaBufferPtr = &stackArena->arena;

    stackArenaAlloc.fieldPtr = &(stackArenaBufferPtr[stackArena->peek]);
    stackArenaAlloc.allocSize = size;

    return stackArenaAlloc;
}

Nav_Memory_StackArena* Nav_Memory_StackArena_Create(UInt64 arenaSize)
{
    UInt64 totalArenaSize = sizeof(UInt64) * 2 + arenaSize;

    Nav_Memory_StackArena* stackArena = NAV_MEMORY_ALLOCATE(totalArenaSize);

    stackArena->size = totalArenaSize;
    stackArena->peek = 0L;

    return 
}