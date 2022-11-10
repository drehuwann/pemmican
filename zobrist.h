#ifndef _ZOBRIST_H_
#define _ZOBRIST_H_

#include "pemTypes.h"

extern unsigned int state;

unsigned int get_random_U32_number();
U64 get_random_U64_number();
U64 generate_magic_number();

#endif  // _ZOBRIST_H_