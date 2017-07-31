#include <stdlib.h>

int func1(void){
    return random();
}

int main(int c, const char **argv) {
    long int x = func1();
    printf("%d\n", x);
    return 0;
}
