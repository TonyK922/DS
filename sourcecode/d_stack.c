/*
** A stack implemented with a dynamically allocated array.
** The array size is given when create is called, which must
** happen before any other stack operations are attempted.  动态分配数组实现栈
*/ 
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

/*
**	The array that holds the values on the stack, and a pointer
**	to the topmost value on the stack.
*/
static	STACK_TYPE	*stack = NULL;
static	size_t	stack_size = 0;
static	int	top_element = -1;

void creat_stack(size_t size){
    assert(stack_size == 0);
    stack_size = size;
    stack = malloc(stack_size * (sizeof(STACK_TYPE)));
    assert(stack != NULL);
}

void destroy_stack(void){
    assert( stack_size > 0 );
	stack_size = 0;
	free( stack );
	stack = NULL;
}

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

//top_element 代表栈顶指针，会变化，stack_size表示整个栈的大小，一旦创建不会改变
int is_empty( void ){
    assert( stack_size > 0 );
	return top_element == -1;
}

int is_full(void){
    assert( stack_size > 0 );
    return top_element == STACK_SIZE - 1;
}
