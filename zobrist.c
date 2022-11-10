#include "zobrist.h"

unsigned int state = 1804289383;

unsigned int get_random_U32_number() {
    unsigned int number = state;
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;
    state = number;
    return number;
}

U64 get_random_U64_number() {
    U64 n1, n2, n3, n4;
    n1 = (U64)(get_random_U32_number() & 0xffff);
    n2 = (U64)(get_random_U32_number() & 0xffff);
    n3 = (U64)(get_random_U32_number() & 0xffff);
    n4 = (U64)(get_random_U32_number() & 0xffff);
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

U64 generate_magic_number() {
    return get_random_U64_number() & get_random_U64_number() & 
            get_random_U64_number();
}
