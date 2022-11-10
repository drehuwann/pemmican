#include "bitboard.h"

extern int count_bits(U64 bb);
extern int get_ls1b_index(U64 bb);

U64 bitboards[12];
U64 occupancies[3];
int side = white;
int enpassant = no_sq;
int castle = 0;
