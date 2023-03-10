/*
** A stack implemented with a linked list.  This stack has no size
** limit.   链表实现堆栈，没有长度限制,栈顶位于链表头部
*/
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#define	FALSE 0

/*
**	Define a structure to hold one value.  The link field will
**	point to the next value on the stack.
*/
typedef	struct	STACK_NODE {
	STACK_TYPE	value;
	struct STACK_NODE *next;
} StackNode;

/*
**	A pointer to the topmost node on the stack.
*/
static	StackNode	*stack = NULL;

void create_stack( size_t size ){

}

void destroy_stack( void ){
	while( !is_empty() )
		pop();
}

void push(STACK_TYPE value){
    StackNode *new_node;
    new_node = malloc(sizeof(StackNode));

    assert(new_node != NULL);
    new_node->value = value;
    new_node->next = stack;
    stack = new_node;
}

void pop( void ){
    StackNode *first_node;

    assert(!is_empty());
    first_node = stack;
    stack = first_node->next;
    free(first_node);
}

STACK_TYPE top(void){
    assert( !is_empty() );
    return stack->value;
}

int is_empty( void ){
	return stack == NULL;
}

//无长度限制
int is_full(void){
    return FALSE;
}