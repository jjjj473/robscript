#include "hello_block.h"
#include "math_block.h"
#include <stdio.h>

int main(void) {
    block_hello();
    printf("2 + 3 = %d\n", block_add(2, 3));
    return 0;
}
