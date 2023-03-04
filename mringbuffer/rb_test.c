#include "rb.h"
#include <stdio.h>

// todo

int main(int argc, char **argv) {
    struct ringbuffer rb;
    char buffer[15];
    int len;

    rb_init(&rb, buffer, sizeof(buffer));
    rb_put(&rb, "hello", 5);
    rb_put(&rb, "hello", 4);
    rb_put(&rb, "hello", 5);
    rb_get(&rb, buffer, 10);
    rb_put(&rb, "hello", 5);
    len = rb_get(&rb, buffer, 10);
    printf("%d\n", len);

    len = rb_data_length(&rb);

    printf("%d\n", len);

    return 0;
}