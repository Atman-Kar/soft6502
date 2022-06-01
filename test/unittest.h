#ifndef _UNITTEST_H
#define _UNITTEST_H

#include <../src/opcodes.h>
#include <../src/cpu.h>

/* Macro to check if arguments are equal */
#define ASSERT_EQUAL(x, y)                                                                  \
({                                                                                          \
    if((x) == (y)) {                                                                        \
        printf("\033[0;32m[+] Passed Test Case: %s, FILE: %s\n", __func__, __FILE__);       \
    } else {                                                                                \
        printf("\033[0;31m[x] Failed Test Case: %s, FILE: %s\n", __func__, __FILE__);       \
        printf("Expected: %x, Output: %x\n", (x), (y));                                     \
    }                                                                                       \
})

#endif // _UNITTEST_H