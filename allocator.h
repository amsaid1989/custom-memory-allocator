#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "aliases.h"
#include <stdbool.h>

typedef struct allocator allocator_t;

allocator_t *init_allocator(u64 size);
void deinit_allocator(allocator_t **allocator);
void *alloc(allocator_t *allocator, u64 size);

#endif // !ALLOCATOR_H
