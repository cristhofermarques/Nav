#ifndef NAV_STACK_ARENA_H
#define NAV_STACK_ARENA_H

#include <Nav_Api.h>
#include <Math/Nav_Value_Type.h>

struct Nav_Memory_StackArenaAllocationType
{
    UInt64 allocSize;
    void* fieldPtr;
};

typedef struct Nav_Memory_StackArenaAllocationType Nav_Memory_StackArenaAllocation;

struct Nav_Memory_StackArenaType
{
    UInt64 size;
    UInt64 peek;
    void* arena;
};

typedef struct Nav_Memory_StackArenaType Nav_Memory_StackArena;

NAV_API Nav_Memory_StackArena* Nav_Memory_StackArena_Create(UInt64 arenaSize);

#endif