#include "allocator.h"
#include "aliases.h"
#include <stdbool.h>
#include <stdlib.h>

#define HEADER_MAGIC_01 76329872
#define HEADER_MAGIC_02 120830238
#define FOOTER_MAGIC_01 2783946
#define FOOTER_MAGIC_02 878512284

struct allocator {
  u8 *buf;
  u64 size;
  u64 used;
};

struct block_boundary {
  u64 size;
  bool free;
  u64 magic_01;
  u64 magic_02;
};

typedef struct block_boundary block_header;
typedef struct block_boundary block_footer;

typedef struct {
  block_header header;
  u8 *data;
  block_footer footer;
} block_t;

allocator_t *init_allocator(u64 size) {
  allocator_t *allocator = (allocator_t *)malloc(sizeof(allocator_t));

  if (!allocator) {
    return NULL;
  }

  allocator->buf = (u8 *)malloc(size);

  if (!(allocator->buf)) {
    free(allocator);
    return NULL;
  }

  allocator->size = size;
  allocator->used = 0;

  return allocator;
}

void deinit_allocator(allocator_t **allocator) {
  if (*allocator != NULL) {
    if ((*allocator)->buf != NULL) {
      free((*allocator)->buf);
      (*allocator)->buf = NULL;
    }

    free(*allocator);
    *allocator = NULL;
  }
}

void *alloc(allocator_t *allocator, u64 size) {}
