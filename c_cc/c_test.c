#include<stdio.h>

void print(const char* msg) {
    printf("%s\n", msg);
}

// gcc -o run_tests c_test.c

int main () {

    char* msg = "this is text\n";

    print(msg);

}