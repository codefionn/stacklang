# stacklang

Programming language which operates on two stacks.

## Examples

Hello world:

```
#str#"Hello World" #str.print
```

Add to numbers:

```
#str#"Type two numbers: "
#f32.read #f32.read
#f32.add #f32.write #ch#'\n' #ch.print
```

## Expressions

Spaces/horizontal tabulators between expressions are NOT included.
Line-feed, vertical tabular and carriage-return characters are ignored.

```
program ::=
  stmt
| stmt program

stmt ::=
  expr
| operation

operation ::=
  'def' id ':' expr 'enddef'

id ::=
  "[a-zA-Z_][a-zA-Z0-9_]*"

expr ::=
  manipulator
| manipulator expr

manipulator ::=
  '('
| ')'
| '<'
| '>'
| literal
| buildin
| id

literal ::=
  bool
| integer
| float
| char
| string

bool ::=
  '#b#true'
| '#b#false'

integer ::=
  "#(u|i)(8|16|32|64)#(0|[1-9][0-9]*|0x[0-9A-F)*)"

float ::=
  "#f(32|64)#[0-9]*\.[0-9]+"

char ::=
  "#u8#('\\.|'[^']')"

string ::=
  "#str#\"(\\.|[^\"]*)\""

buildin ::=
  "#(u|i)(8|16|32|64)\.(add|sub|mul|div|rsh|lsh|inv|eq|write|read)"
| "#ch\.(write|read)"
| "#str\.(cc|eq|write|read)"
| "\.(eat)"
```

## Semantics

Note: The final program also implements bound checks.

Some C code for basic functionalities:

```C
typedef struct {
  size_t size;
  size_t allocSize;
  uint8_t * data;
} Stack;

Stack *newStack(void) {
  Stack *result = (Stack*) malloc(sizeof(Stack));
  result->size = 0;
  result->allocSize = 1024;
  result->data = (uint8_t*) malloc(result->allocSize);

  return result;
}

void freeStack(Stack *stack) {
  free(stack->data);
  free(stack);
}

void reserveStackData(Stack *stack, size_t size) {
  if (stack->size + size > stack->allocSize) {
    stack->allocSize = stack->size + size + 1024; // 1024 is additional
    stack->data = (uint8_t*) realloc(stack->data, stack->allocSize);
  }
}

Stack *parent = NULL;
Stack *current = newStack();
```

Transformations:

```
'(' ->
  freeStack(parent);
  parent = current;
  current = newStack();
 
')' ->
  freeStack(current);
  current = parent;
  parent = NULL;

'>' ->
  reserveStackData(current, 1);
  current->data[current->size++] = parent->data[--parent->size];
 
'<' ->
  reserveStackData(parent, 1);
  parent->data[parent->size++] = current->data[--current->size];

"#i8#(0|[1-9][0-9]*|0x[0-9A-F)*)" ->
  reserveStackData(current, 1);
  current->data[current->size++] = /* integer */

"#u8#(0|[1-9][0-9]*|0x[0-9A-F)*)" ->
  reserveStackData(current, 1);
  current->data[current->size++] = /* integer */

"#i16#(0|[1-9][0-9]*|0x[0-9A-F)*)" ->
  reserveStackData(current, sizeof(int16_t));
  // push integer bytes in reverse
  // (so that top of stack will be the first integer of the number)
  current->data[current->size++] = /* integer[1] */
  current->data[current->size++] = /* integer[0] */

and so on ...

#i8.add ->
  current->data[current->size - 2] = current->data[current->size - 1] + current->data[current->size - 2];
  current->size -= 1;

#i16.add ->
  int16_t result;
  int16_t x = 0, y = 0;
  ((uint8_t*) &x)[1] = current->data[current->size - 2]
  ((uint8_t*) &x)[0] = current->data[current->size - 1]
  ((uint8_t*) &y)[1] = current->data[current->size - 4]
  ((uint8_t*) &y)[0] = current->data[current->size - 3]
  result = x + y
  current->data[current->size - 4] = ((uint8_t*) &result)[1];
  current->data[current->size - 3] = ((uint8_t*) &result)[0];
  current->size -= 2;

and so on ...

#u8.add ->
  current->data[current->size - 2] = current->data[current->size - 1] + current->data[current->size - 2];
  current->size -= 1;

#str#"str" ->
  // Puts str in reverse on stack (0st element in str will be on top of stack)
  // str is the string in the expression (null terminated)
  size_t len = strlen(str);
  reserveStackData(stack, len + 1);
  stack->data[stack->size++] = '\0';
  for (size_t i = len; i > 0; ++i) {
	  stack->data[stack->size++] = str[i - 1];
  }

.eat ->
  current->size -= 1;
```
