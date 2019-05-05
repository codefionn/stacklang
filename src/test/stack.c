#include "stacklang/stack.h"

int main(int argsc, char * argsv[]) {
  if (argsc < 2)
    return EXIT_FAILURE;

  Stack *stack = newStack();
  if (!stack)
    return EXIT_FAILURE;

  uint64_t * integers = malloc(sizeof(uint64_t) * (argsc - 1));
  reserveStackData(stack, sizeof(uint64_t) * (argsc - 1));
  for (size_t i = 1; i < argsc; ++i) {
    integers[i - 1] = atol(argsv[i]);
    stack->size += sizeof(uint64_t);
    *u64_Stack(stack, 0) = reverse_u64(integers[i - 1]);
  }

  if (stack->size / sizeof(uint64_t) != argsc - 1) {
    fprintf(stderr, "Invalid stack size. Current: %l, Expected %l",
        stack->size / sizeof(uint64_t), argsc - 1);
    return EXIT_FAILURE;
  }

  // Check if integers are correct (in stack)
  for (size_t i = 0; i < argsc - 1; ++i) {
    uint64_t stackNum = reverse_u64(*u64_Stack(stack, i * sizeof(uint64_t)));
    uint64_t aNum = integers[argsc - 2 - i];
    if (stackNum != aNum) {
      fprintf(stderr, "Invalid numbers. %llu and %llu are not equal.",
          stackNum, aNum);
      return EXIT_FAILURE;
    }
  }

  free(integers);
  freeStack(stack);

  return EXIT_SUCCESS;
}
