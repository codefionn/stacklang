#include "stacklang/stack.h"

#include <limits.h>

#define HALF (uint64_t) 0x00000000FFFFFFFFL

int main(void) {
  return ((HALF | reverse_u64(HALF)) == ULLONG_MAX)
    ? EXIT_SUCCESS : EXIT_FAILURE;
}
