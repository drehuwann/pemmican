#ifndef _SHARED_H_
#define _SHARED_H_

#include "pemTypes.h"

extern const U64 not_a_file;
extern const U64 not_h_file;
extern const U64 not_ab_file;
extern const U64 not_gh_file;
extern const U64 not_1_rank;
extern const U64 not_8_rank;
extern const U64 not_12_rank;
extern const U64 not_78_rank;
extern const char *index2coord[];
extern const char ascii_pieces[];
extern const char *unicode_pieces[];

enum {
    P, N, B, R, Q, K,
    p, n, b, r, q, k
};

extern const int char_pieces[];
extern const int bishop_relevant_bits[];
extern const int rook_relevant_bits[];
extern const U64 rook_magic_numbers[];
extern const U64 bishop_magic_numbers[];

#endif  // _SHARED_H_
