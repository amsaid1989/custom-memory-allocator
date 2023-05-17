#include "aliases.h"
#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 10 * 1024 * 1024

i32 main(void) {
  allocator_t *allocator = init_allocator(BUF_SIZE);

  if (!allocator) {
    return EXIT_FAILURE;
  }

  i32 *num = (i32 *)allocate(allocator, sizeof(i32));
  *num = 25;

  deinit_allocator(&allocator);

  return EXIT_SUCCESS;
}
