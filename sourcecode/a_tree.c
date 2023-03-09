/*
** A binary search tree implemented with a static array.  The
** array size can be adjusted only by changing the #define and
** recompiling the module.   静态数组实现二叉树
*/
#include "tree.h"
#include <assert.h>
#include <stdio.h>

#define	TREE_SIZE	100	/* Max # of values in the tree */
#define	ARRAY_SIZE	( TREE_SIZE + 1 )

/*
**	The array that holds the values in the tree.
*/
static	TREE_TYPE	tree[ ARRAY_SIZE ] = {0};


static int left_child(int current){
    return current * 2;
}

static int right_child(int current){
    return current * 2 + 1;
}


void insert(TREE_TYPE value){
    assert(value!= 0);
    /*
	** Start with the root node.
	*/
    int current = 1;

    while(tree[current] ! = 0){
        if(value < tree[current]){
            current = left_child(current);
        }else{
            //And make sure we don't have a duplicate value!
            assert(value != tree[current]);
            current = right_child(current);
        }
        assert( current < ARRAY_SIZE );
    }
    tree[ current ] = value;
}


TREE_TYPE *find(TREE_TYPE value){
    int current = 1;
    
    while( current < ARRAY_SIZE && tree[current] != value){
        if(value < tree[current]){
            current = left_child(current);
        }else{
            current = right_child(current);
        }
    }

    if(current < ARRAY_SIZE){
        //返回指向目标值的指针
        return tree + current;
    }else{
        //未找到
        return 0;
    }
}


static void do_pre_order_traverse(int current, void(*callback)(TREE_TYPE value)){
    if( current < ARRAY_SIZE && tree[ current ] != 0 ){
		callback( tree[ current ] );
		do_pre_order_traverse( left_child( current ),
		    callback );
		do_pre_order_traverse( right_child( current ),
		    callback );
	}
}

//从根节点1开始前序遍历
void pre_oder_traverse(void(*callback)(TREE_TYPE value)){
    do_pre_order_traverse(1, callback);
}