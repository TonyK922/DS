#include <stdio.h>
#include <stdint.h>
int main(){
	int32_t a = -1062730404;
	printf("ip = %d.%d.%d.%d\n",(uint8_t)(((char*)(&a))[3]),
				    (uint8_t)(((char*)(&a))[2]),
				    (uint8_t)(((char*)(&a))[1]),
                                    (uint8_t)(((char*)(&a))[0]));
	return 0;
}
