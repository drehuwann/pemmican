#ifndef _ATTACKS_H_
#define _ATTACKS_H_

#include "pemTypes.h"
#include "shared.h"
#include "bitboard.h"
#include "zobrist.h"
#include "io.h"

#include <string.h>

extern U64 pawn_attacks[][64];
extern U64 knight_attacks[];
extern U64 king_attacks[];

extern U64 bishop_masks[];
extern U64 rook_masks[];

extern U64 bishop_attacks[][512];
extern U64 rook_attacks[][4096];

void init_leapers_attacks();
U64 mask_pawn_attacks(int side, int square);
U64 mask_knight_attacks(int square);
U64 mask_king_attacks(int square);
U64 mask_bishop_attacks(int square);
U64 mask_rook_attacks(int square);
U64 bishop_attacks_on_the_fly(int square, U64 block);
U64 rook_attacks_on_the_fly(int square, U64 block);
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask);
U64 find_magic_number(int square, int relevant_bits, int bishop);
void init_magic_numbers();
void init_slider_attacks(int bishop);

static inline U64 get_bishop_attacks(int square, U64 occupancy) {
    occupancy &= bishop_masks[square];
    occupancy *= bishop_magic_numbers[square];
    occupancy >>= 64 - bishop_relevant_bits[square];
    return bishop_attacks[square][occupancy];
}

static inline U64 get_rook_attacks(int square, U64 occupancy) {
    occupancy &= rook_masks[square];
    occupancy *= rook_magic_numbers[square];
    occupancy >>= 64 - rook_relevant_bits[square];
    return rook_attacks[square][occupancy];
}

#endif  // _ATTACKS_H_