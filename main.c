#include "aliases.h"
#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 10 * 1024 * 1024

i32 main(void) {
  allocator_t *alloc = init_allocator(BUF_SIZE);

  if (!alloc) {
    return EXIT_FAILURE;
  }

  deinit_allocator(&alloc);

  return EXIT_SUCCESS;
}
