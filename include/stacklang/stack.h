#ifndef STACKLANG_STACK_H
#define STACKLANG_LEXER_H

#include "stacklang/global.h"

typedef struct {
  size_t size;      /*!< Used bytes in data [0;size[ */
  size_t allocSize; /*!< Size of data in bytes */
  uint8_t * data;   /*!< Data */
} Stack;

/*!\return Returns new stack. NULL if allocation failed.
 */
Stack *newStack(void);

/*!\brief Free dynamic data used by stack.
 */
void freeStack(Stack *stack);

/*!\return Returns true, if allocation/reserving bytes was successfull,
 * otherwise false. Reserving means allocate new bytes if
 *
 *     stack->size + size > stack->allocSize.
 *
 * At least
 *
 *     stack->size + size - stack->allocSize
 *
 * bytes are reserved.
 */
bool reserveStackData(Stack *stack, size_t size);

/*!\return Returns int8_t at position 
 *    stack->size - sizeof(int8_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
int8_t   *i8_Stack(Stack *stack, size_t offset);

/*!\return Returns uint8_t at position 
 *    stack->size - sizeof(uint8_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
uint8_t  *u8_Stack(Stack *stack, size_t offset);

/*!\return Returns int16_t at position 
 *    stack->size - sizeof(int16_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
int16_t  *i16_Stack(Stack *stack, size_t offset);

/*!\return Returns uint16_t at position 
 *    stack->size - sizeof(uint16_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
uint16_t *u16_Stack(Stack *stack, size_t offset);

/*!\return Returns int32_t at position 
 *    stack->size - sizeof(int32_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
int32_t  *i32_Stack(Stack *stack, size_t offset);

/*!\return Returns uint32_t at position 
 *
 *    stack->size - sizeof(uint32_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
uint32_t *u32_Stack(Stack *stack, size_t offset);

/*!\return Returns int64_t at position
 *     stack->size - sizeof(int64_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
int64_t  *i64_Stack(Stack *stack, size_t offset);

/*!\return Returns uint64_t at position
 *     stack->size - sizeof(uint64_t) - offset.
 * \param offset offset (from end to start) in bytes
 */
uint64_t *u64_Stack(Stack *stack, size_t offset);

/*!\return returns x in reversed byte order.
 */
int8_t reverse_i8(int8_t x);

/*!\return returns x in reversed byte order.
 */
uint8_t reverse_u8(uint8_t x);

/*!\return returns x in reversed byte order.
 */
int16_t reverse_i16(int16_t x);

/*!\return returns x in reversed byte order.
 */
uint16_t reverse_u16(uint16_t x);

/*!\return returns x in reversed byte order.
 */
int32_t reverse_i32(int32_t x);

/*!\return returns x in reversed byte order.
 */
uint32_t reverse_u32(uint32_t x);

/*!\return returns x in reversed byte order.
 */
int64_t reverse_i64(int64_t x);

/*!\return returns x in reversed byte order.
 */
uint64_t reverse_u64(uint64_t x);

#endif /* STACKLANG_STACK_H */
