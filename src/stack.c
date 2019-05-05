#include "stacklang/stack.h"

Stack *newStack(void) {
  Stack *result = (Stack*) malloc(sizeof(Stack));
  if (!result)
    return NULL;

  result->size = 0;
  result->allocSize = 1024;
  result->data = (uint8_t*) malloc(result->allocSize);
  if (!result->data) {
    free(result);
    return NULL;
  }

  return result;
}

void freeStack(Stack *stack) {
  if (stack->data)
    free(stack->data);

  free(stack);
}

bool reserveStackData(Stack *stack, size_t size) {
  if (stack->size + size > stack->allocSize) {
    stack->allocSize = stack->size + size;
    stack->allocSize += 1024; // additional bytes to prevent the realloc
                              // instruction from being called to frequent
    stack->data = (uint8_t*) realloc((void*) stack->data, stack->allocSize);
    if (!stack->data)
      return false;

    return true;
  }

  return true;
}

#define type_Stack(type, stack, offset) \
  return (type*) stack->data[stack->size - sizeof(type) - offset]

int8_t *i8_Stack(Stack *stack, size_t offset) {
  type_Stack(int8_t, stack, offset);
}

uint8_t *u8_Stack(Stack *stack, size_t offset) {
  type_Stack(uint8_t, stack, offset);
}

int16_t *i16_Stack(Stack *stack, size_t offset) {
  type_Stack(int16_t, stack, offset);
}

uint16_t *u16_Stack(Stack *stack, size_t offset) {
  type_Stack(uint16_t, stack, offset);
}

int32_t *i32_Stack(Stack *stack, size_t offset) {
  type_Stack(int32_t, stack, offset);
}

uint32_t *u32_Stack(Stack *stack, size_t offset) {
  type_Stack(uint32_t, stack, offset);
}

int64_t *i64_Stack(Stack *stack, size_t offset) {
  type_Stack(int64_t, stack, offset);
}

uint64_t *u64_Stack(Stack *stack, size_t offset) {
  type_Stack(uint64_t, stack, offset);
}

#undef  type_Stack
