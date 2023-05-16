#include "allocator.h"
#include "aliases.h"
#include <stdbool.h>
#include <stdlib.h>

#define HEADER_MAGIC_01 76329872
#define HEADER_MAGIC_02 120830238
#define FOOTER_MAGIC_01 2783946
#define FOOTER_MAGIC_02 878512284

struct block_boundary {
  u64 size;
  bool free;
  u64 magic_01;
  u64 magic_02;
};

typedef struct block_boundary block_header;
typedef struct block_boundary block_footer;

struct allocator {
  u8 *buf;
  u64 size;
  u64 used;
  u64 block_count;
  u64 free_max_size;
  u64 free_count;
  block_header **free_blocks; // Array of pointers
};

allocator_t *init_allocator(u64 size) {
  allocator_t *allocator = (allocator_t *)malloc(sizeof(allocator_t));

  if (!allocator) {
    deinit_allocator(&allocator);
    return NULL;
  }

  allocator->buf = (u8 *)malloc(size);

  if (!(allocator->buf)) {
    deinit_allocator(&allocator);
    return NULL;
  }

  allocator->size = size;
  allocator->used = 0;
  allocator->block_count = allocator->free_count = 1;

  // Each memory block has a header and footer, so the maximum number of blocks
  // that can be added to the buffer can be calculated by assuming blocks of
  // size 0 (i.e. only containing a header and a footer)
  allocator->free_max_size =
      size / (sizeof(block_header) + sizeof(block_footer));

  allocator->free_blocks = (block_header **)malloc(allocator->free_max_size);

  if (!(allocator->free_blocks)) {
    deinit_allocator(&allocator);
    return NULL;
  }

  block_header *header = (block_header *)allocator->buf;
  block_footer *footer =
      (block_footer *)(allocator->buf + size - sizeof(block_footer));

  header->size = size;
  footer->size = size - sizeof(block_footer);
  header->free = footer->free = true;

  header->magic_01 = HEADER_MAGIC_01;
  header->magic_02 = HEADER_MAGIC_02;

  footer->magic_01 = FOOTER_MAGIC_01;
  footer->magic_02 = FOOTER_MAGIC_02;

  allocator->free_blocks[0] = header;

  return allocator;
}

void deinit_allocator(allocator_t **allocator) {
  if (*allocator != NULL) {
    if ((*allocator)->free_blocks != NULL) {
      free((*allocator)->free_blocks);
      (*allocator)->free_blocks = NULL;
    }

    if ((*allocator)->buf != NULL) {
      free((*allocator)->buf);
      (*allocator)->buf = NULL;
    }

    free(*allocator);
    *allocator = NULL;
  }
}

// void *alloc(allocator_t *allocator, u64 size) {
//   ++size;
//   return NULL;
// }
