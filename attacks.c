#include "attacks.h"

U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];

U64 bishop_masks[64];
U64 rook_masks[64];

U64 bishop_attacks[64][512];
U64 rook_attacks[64][4096];

void init_leapers_attacks() {
    for (int square = 0; square < 64; ++ square) {
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);
        knight_attacks[square] = mask_knight_attacks(square);
        king_attacks[square] = mask_king_attacks(square);
    }
}

U64 mask_pawn_attacks(int side, int square) {
    U64 toRet = 0ULL;
    U64 bb = 0ULL;
    set_bit(bb, square);  
    if (!side) {  // white pawn
        if ((bb >> 7) & not_a_file) toRet |= bb >> 7;
        if ((bb >> 9) & not_h_file) toRet |= bb >> 9;
    } else {        // black pawn
        if ((bb << 7) & not_h_file) toRet |= bb << 7;
        if ((bb << 9) & not_a_file) toRet |= bb << 9;
    }
    return toRet;
}

U64 mask_knight_attacks(int square) {
    U64 toRet = 0ULL;
    U64 bb = 0ULL;
    set_bit(bb, square);
    if ((bb >> 6) & not_ab_file) toRet |= bb >> 6;
    if ((bb >> 10) & not_gh_file) toRet |= bb >> 10;
    if ((bb >> 15) & not_a_file) toRet |= bb >> 15;
    if ((bb >> 17) & not_h_file) toRet |= bb >> 17;
    if ((bb << 6) & not_gh_file) toRet |= bb << 6;
    if ((bb << 10) & not_ab_file) toRet |= bb << 10;
    if ((bb << 15) & not_h_file) toRet |= bb << 15;
    if ((bb << 17) & not_a_file) toRet |= bb << 17;
    return toRet;
}

U64 mask_king_attacks(int square) {
    U64 toRet = 0ULL;
    U64 bb = 0ULL;
    set_bit(bb, square);
    if ((bb >> 1) & not_h_file) toRet |= bb >> 1;
    if ((bb >> 7) & not_a_file) toRet |= bb >> 7;
    if (bb >> 8) toRet |= bb >> 8;
    if ((bb >> 9) & not_h_file) toRet |= bb >> 9;
    if ((bb << 1) & not_a_file) toRet |= bb << 1;
    if ((bb << 7) & not_h_file) toRet |= bb << 7;
    if (bb << 8) toRet |= bb << 8;
    if ((bb << 9) & not_a_file) toRet |= bb << 9;
    return toRet;
}

U64 mask_bishop_attacks(int square) {
    U64 toRet = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; ++ r, ++ f) {
        toRet |= (1ULL << (r * 8 + f));
    }
    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; -- r, ++ f) {
        toRet |= (1ULL << (r * 8 + f));
    }
    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; ++ r, -- f) {
        toRet |= (1ULL << (r * 8 + f));
    }
    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; -- r, -- f) {
        toRet |= (1ULL << (r * 8 + f));
    }
    return toRet;
}

U64 bishop_attacks_on_the_fly(int square, U64 block) {
    U64 toRet = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; ++ r, ++ f) {
        toRet |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; -- r, ++ f) {
        toRet |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; ++ r, -- f) {
        toRet |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; -- r, -- f) {
        toRet |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block) break;
    }
    return toRet;
}

U64 mask_rook_attacks(int square) {
    U64 toRet = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1; r <= 6; ++ r) {
        toRet |= (1ULL << (r * 8 + tf));
    }
    for (r = tr - 1; r >= 1; -- r) {
        toRet |= (1ULL << (r * 8 + tf));
    }
    for (f = tf + 1; f <= 6; ++ f) {
        toRet |= (1ULL << (tr * 8 + f));
    }
    for (f = tf - 1; f >= 1; -- f) {
        toRet |= (1ULL << (tr * 8 + f));
    }
    return toRet;
}

U64 rook_attacks_on_the_fly(int square, U64 block) {
    U64 toRet = 0ULL;
    int r, f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1; r <= 7; ++ r) {
        toRet |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) & block) break;
    }
    for (r = tr - 1; r >= 0; -- r) {
        toRet |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) & block) break;
    }
    for (f = tf + 1; f <= 7; ++ f) {
        toRet |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) & block) break;
    }
    for (f = tf - 1; f >= 0; -- f) {
        toRet |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) & block) break;
    }
    return toRet;
}

U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask) {
    U64 occupancy = 0ULL;
    for (int count = 0; count < bits_in_mask; ++ count) {
        int square = get_ls1b_index(attack_mask);
        pop_bit(attack_mask, square);
        if (index & 1 << count) {
            occupancy |= (1ULL << square);
        }
    }
    return occupancy;
}

U64 find_magic_number(int square, int relevant_bits, int bishop) {
    U64 occupancies[4096];
    U64 attacks[4096];
    U64 used_attacks[4096];
    U64 attack_mask = bishop ? mask_bishop_attacks(square)
                                : mask_rook_attacks(square);
    int occupancy_index = 1 << relevant_bits;
    for (int index = 0; index < occupancy_index; ++ index) {
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);
        attacks[index] = bishop ?
                        bishop_attacks_on_the_fly(square, occupancies[index])
                        : rook_attacks_on_the_fly(square, occupancies[index]);
    }
    for (int random_count = 0; random_count < 100000000; ++ random_count) {
        U64 magic_number = generate_magic_number();
        if (count_bits((attack_mask * magic_number) & 0xff00000000000000) < 6) {
            continue;
        }
        memset(used_attacks, 0ULL, sizeof(used_attacks));
        int index, fail;
        for (index = 0, fail = 0; !fail && index < occupancy_index; ++index) {
            int magic_index = (int)((occupancies[index] * magic_number) >>
                                (64 - relevant_bits));
            if (used_attacks[magic_index] == 0ULL) {
                used_attacks[magic_index] = attacks[index];
            } else if (used_attacks[magic_index] != attacks[index]) {
                fail = 1;
            }
        }
        if (! fail) return magic_number;
    }
    printf("Magic number fails !\n");
    return 0ULL;
}
/*
void init_magic_numbers() {
    for (int square = 0; square < 64; ++ square) {
        rook_magic_numbers[square] = find_magic_number(square,
                                            rook_relevant_bits[square], rook);
    }    
    for (int square = 0; square < 64; ++ square) {
        bishop_magic_numbers[square] = find_magic_number(square,
                                            bishop_relevant_bits[square],
                                            bishop);
    }    
}
*/
void init_slider_attacks(int bishop) {
    for (int square = 0; square < 64; ++ square) {
        bishop_masks[square] = mask_bishop_attacks(square);
        rook_masks[square] = mask_rook_attacks(square);
        U64 attack_mask = bishop ? bishop_masks[square] : rook_masks[square];
        int relevant_bits_count = count_bits(attack_mask);
        int occupancy_index = 1 << relevant_bits_count;
        for (int index = 0; index < occupancy_index; ++ index) {
            if (bishop) {
                U64 occupancy = set_occupancy(index, relevant_bits_count,
                                                attack_mask);
                int magic_index = (occupancy * bishop_magic_numbers[square]) >>
                    (64 - bishop_relevant_bits[square]);
                bishop_attacks[square][magic_index] =
                    bishop_attacks_on_the_fly(square, occupancy);
            } else {
                U64 occupancy = set_occupancy(index, relevant_bits_count,
                                                attack_mask);
                int magic_index = (occupancy * rook_magic_numbers[square]) >>
                    (64 - rook_relevant_bits[square]);
                rook_attacks[square][magic_index] =
                    rook_attacks_on_the_fly(square, occupancy);
            }
        }
    }
}

extern U64 get_bishop_attacks(int square, U64 occupancy);
extern U64 get_rook_attacks(int square, U64 occupancy);