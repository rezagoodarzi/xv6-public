#include "types.h"
#include "user.h"
#include "stat.h"
#include "spinlock.h"

struct spinlock l1, l2;

void printPowersOfTwo(void *arg1, void *arg2) {
    lock_acquire(&l2);

    // Print powers of 2
    for (int i = 0; i < 10; ++i) {
        printf(1, "Power of 2: %d\n", 1 << i);
    }

    lock_release(&l2);
    exit();
}

void printHello(void *arg1, void *arg2) {
    lock_acquire(&l1);
    // Print "Hello"
        for (int i = 0; i < 10; ++i) {
            printf(1, "Hello\n");
    }

    lock_release(&l1);
    exit();
}

int main() {
    lock_init(&l1);
    lock_init(&l2);

    // Create thread for printing powers of 2
    thread_create(&printPowersOfTwo, (void *)0, (void *)0);
    sleep(3);
    // Create thread for printing "Hello"
    thread_create(&printHello, (void *)0, (void *)0);

    // Wait for both threads to finish
    join(1);
    join(2);

    exit();
}
