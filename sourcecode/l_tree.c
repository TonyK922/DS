/*
** A binary search tree implemented by linking dynamically allocated
** structures.
*/
#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <malloc.h>

/*
**	The TreeNode structure holds the value and pointers for one
**	tree node.  链表实现二叉树
*/
typedef struct TREE_NODE {
	TREE_TYPE	value;
	struct TREE_NODE *left;
	struct TREE_NODE *right;
} TreeNode;

/*
**	The pointer to the root node in the tree.
*/
static	TreeNode	*tree;

//不传root参数，会导致tree被修改，所以使用 **link 来指向root
void insert(TREE_TYPE value){
    TreeNode *current;
    TreeNode **link;
    /*
	** Start with the root node.
	*/
	link = &tree;

    while((current = *link) != NULL){
        if(value < current->value){
            link = &current->left;
        }else{
            assert( value != current->value );
			link = &current->right;
        }
    }

    /*
	** Allocate a new node; make the proper link field point
	** to it.
	*/
    current = malloc( sizeof( TreeNode ) );
	assert( current != NULL );
	current->value = value;
	current->left = NULL;
	current->right = NULL;
	*link = current;  //重要
}

TREE_TYPE *find( TREE_TYPE value ){
    TreeNode *current = tree;

    while(current != NULL && current->value != value){
        if( value < current->value ){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    if( current != NULL ){
        return &current->value;
    }else{
        return NULL;
    }
}

static void do_pre_order_traverse( TreeNode *current,
    void (*callback)( TREE_TYPE value ) ){

	if( current != NULL ){
		callback( current->value );
		do_pre_order_traverse( current->left, callback );
		do_pre_order_traverse( current->right, callback );
	}
}

void pre_order_traverse( void (*callback)( TREE_TYPE value ) ){
    do_pre_order_traverse(tree, callback);
}