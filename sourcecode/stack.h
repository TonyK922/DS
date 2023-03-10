/*
** Interface for a stack module
*/

#define	STACK_TYPE	int	/* Type of value on the stack 可以根据需要修改*/

/*
** push
**	Pushes a new value on the stack.  The argument is the value
**	to be pushed.
*/
void	push( STACK_TYPE value );

/*
** pop
**	Pops a value off of the stack, discarding it.
*/
void	pop( void );

/*
** top
**	Returns the topmost value on the stack without changing the
**	stack.
*/
STACK_TYPE top( void );

/*
** is_empty
**	Returns TRUE if the stack is empty, else FALSE.
*/
int	is_empty( void );

/*
** is_full
**	Returns TRUE if the stack is full, else FALSE.
*/
int	is_full( void );

//适用于动态数组实现的栈
void creat_stack(size_t size);

void destroy_stack(void);