#include "io.h"

void printBitboard(const U64 bb) {
    printf("\n");
    for (int rank = 0; rank < 8; ++ rank) {
        printf("%d  ", 8 - rank);
        for (int file = 0; file < 8; ++ file) {
            int square = 8 * rank + file;
            printf(" %d ", get_bit(bb, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n    a  b  c  d  e  f  g  h\n\n");
    printf("ULL bb = %llu \n", bb);
}

void print_board() {
    printf("\n");
    for (int rank = 0; rank < 8; ++ rank) {
        for (int file = 0; file < 8; ++ file) {
            int square = rank * 8 + file;
            if (! file) printf("%d  ", 8 - rank);
            int piece = -1;
            for (int bb_piece = P; bb_piece <= k; ++ bb_piece) {
                if (get_bit(bitboards[bb_piece], square)) {
                    piece = bb_piece;
                }
            }
        #ifdef WIN64
            printf(" %c ", (piece == -1) ? '.' : ascii_pieces[piece]);
        #else  // WIN64
            printf(" %s", (piece == -1) ? ". " : unicode_pieces[piece]);
        #endif  // WIN64
        }
        printf("\n");
    }
    printf("\n    a  b  c  d  e  f  g  h\n");
    printf(" Side to play : %s.\n", ! side ? "white" : "black");
    printf(" En passant : %s.\n", (enpassant != no_sq) ?
                                    index2coord[enpassant] : "no");
    printf(" Castling : %c%c%c%c\n\n", (castle & wckc) ? 'K' : '-',
                                        (castle & wcqc) ? 'Q' : '-',
                                        (castle & bckc) ? 'k' : '-',
                                        (castle & bcqc) ? 'q' : '-');
}