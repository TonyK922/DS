/*
** A queue implemented with a static array.  The array size can
** be adjusted only by changing the #define and recompiling
** the module.        静态数组实现FIFO环形队列，
*/
#include "queue.h"
#include <stdio.h>
#include <assert.h>

//数组中有一个元素不用，方便计算满队列
#define	QUEUE_SIZE	100	/* Max # of values on the queue */
#define	ARRAY_SIZE	( QUEUE_SIZE + 1 )	/* Size of array */

/*
**	The array that holds the values on the queue, and pointers
**	to the front and rear of the queue.
*/
static	QUEUE_TYPE	queue[ ARRAY_SIZE ];
static	size_t		front = 1;
static	size_t		rear = 0;

void insert(QUEUE_TYPE value){
    assert( !is_full() );
    rear = (rear + 1) % ARRAY_SIZE;
    queue[rear] = value;
}

void delete(void){
    assert( !is_empty() );

    front = (front + 1) % ARRAY_SIZE;
}

QUEUE_TYPE first(void){
    assert( !is_empty() );
    queue[front];
}

QUEUE_TYPE last(void){
    assert( !is_empty() );
    queue[rear];
}

int is_empty(void){
    return (rear + 1) % ARRAY_SIZE == front;
}

int is_full(void){
    return (rear + 2) % ARRAY_SIZE == front;
}