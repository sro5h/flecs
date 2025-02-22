/**
 * @file block_allocator.h
 * @brief Allocator that returns memory objects of the same (chunk) size. 
 *        Multiple elements are stored in a single block.
 */

#ifndef FLECS_BLOCK_ALLOCATOR_H
#define FLECS_BLOCK_ALLOCATOR_H

#include "api_defines.h"

typedef struct ecs_block_allocator_block_t {
    void *memory;
    struct ecs_block_allocator_block_t *next;
} ecs_block_allocator_block_t;

typedef struct ecs_block_allocator_chunk_header_t {
    struct ecs_block_allocator_chunk_header_t *next;
} ecs_block_allocator_chunk_header_t;

typedef struct ecs_block_allocator_t {
    ecs_block_allocator_chunk_header_t *head;
    ecs_block_allocator_block_t *block_head;
    ecs_block_allocator_block_t *block_tail;
    int32_t chunk_size;
    int32_t data_size;
    int32_t chunks_per_block;
    int32_t block_size;
} ecs_block_allocator_t;

FLECS_DBG_API
void flecs_ballocator_init(
    ecs_block_allocator_t *ba,
    ecs_size_t size);

#define flecs_ballocator_init_t(ba, T)\
    flecs_ballocator_init(ba, ECS_SIZEOF(T))
#define flecs_ballocator_init_n(ba, T, count)\
    flecs_ballocator_init(ba, ECS_SIZEOF(T) * count)

FLECS_DBG_API
ecs_block_allocator_t* flecs_ballocator_new(
    ecs_size_t size);

FLECS_DBG_API
void flecs_ballocator_fini(
    ecs_block_allocator_t *ba);

FLECS_DBG_API
void flecs_ballocator_free(
    ecs_block_allocator_t *ba);

FLECS_DBG_API
void* flecs_balloc(
    ecs_block_allocator_t *allocator);

FLECS_DBG_API
void* flecs_bcalloc(
    ecs_block_allocator_t *allocator);

FLECS_DBG_API
void flecs_bfree(
    ecs_block_allocator_t *allocator, 
    void *memory);

FLECS_DBG_API
void* flecs_brealloc(
    ecs_block_allocator_t *dst, 
    ecs_block_allocator_t *src, 
    void *memory);

FLECS_DBG_API
void* flecs_bdup(
    ecs_block_allocator_t *ba, 
    void *memory);

#endif
