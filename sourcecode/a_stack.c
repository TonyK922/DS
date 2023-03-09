/*
** A stack implemented with a static array.  The array size can
** be adjusted only by changing the #define and recompiling
** the module.           静态数组实现堆栈
*/
#include "stack.h"
#include <assert.h>

#define	STACK_SIZE	100	/* Max # of values on the stack */

/*
**	The array that holds the values on the stack, and a pointer
**	to the topmost value on the stack.
*/
static	STACK_TYPE	stack[ STACK_SIZE ];
static	int		top_element = -1;

void push(STACK_TYPE value){
    assert( !is_full() );
    
    top_element += 1;
    stack[top_element] = value;
}

void pop(void){
    assert( !is_empty() );
    top_element -= 1;
}

STACK_TYPE top(void){
    assert( !is_empty() );
    return stack[top_element];
}

int is_empty( void ){
	return top_element == -1;
}

int is_full(void){
    return top_element == STACK_SIZE - 1;
}
