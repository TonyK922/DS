#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int *array;
    int *origin;
    int size;
} Solution;

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

int randInt(int min, int max){
    int ret = rand()%(max - min + 1) + min;
    return ret;
}

Solution* solutionCreate(int* nums, int numsSize) {
    Solution *obj = malloc(sizeof(Solution));
    obj->size = numsSize;
    obj->array = malloc(sizeof(int)*numsSize);
    obj->origin = malloc(sizeof(int)*numsSize);
    memcpy(obj->array, nums, sizeof(int)*numsSize);
    memcpy(obj->origin, nums, sizeof(int)*numsSize);
    return obj;
}

int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->size;
    memcpy(obj->array, obj->origin, sizeof(int)*obj->size);
    return obj->array;
}

int* solutionShuffle(Solution* obj, int* retSize) {
    *retSize = obj->size;
    for(int i = 0; i < obj->size; i++){
        int idx = randInt(i, obj->size - 1);
        swap(&(obj->array[i]), &(obj->array[idx]));
    }
    return obj->array;
}

void solutionFree(Solution* obj) {
    free(obj->array);
    free(obj->origin);
    free(obj);
    return;
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(nums, numsSize);
 * int* param_1 = solutionReset(obj, retSize);
 
 * int* param_2 = solutionShuffle(obj, retSize);
 
 * solutionFree(obj);
*/

int main(){
    int array[3] = {1,2,3};
    int* a = solutionCreate(array, 3);
    int b_size;
    int* b = solutionShuffle(a, &b_size);
    for(int i = 0; i < b_size; i++){
        printf("%d\t",b[i]);
    }
    printf("\n");
    return 0;
}