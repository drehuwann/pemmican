#include "attacks.h"
#include "bitboard.h"
#include "zobrist.h"
#include "io.h"

static void init_all() {
    init_leapers_attacks();
//    init_magic_numbers();
    init_slider_attacks(bishop);
    init_slider_attacks(rook);
}

static void parse_args(char ** argv) {
    while (*argv) {
        ++argv;
    }
}

static void show_env(char **envp) {
    while (*envp) {
//        printf("%s\n", *envp);
        ++envp;
    }
}

int main(int argc, char **argv, char **envp) {
    if (argc > 1) {
        parse_args(argv);
    }
    if (envp) show_env(envp);
    init_all();
    
    set_bit(bitboards[P], a2);
    set_bit(bitboards[P], b2);
    set_bit(bitboards[P], c2);
    set_bit(bitboards[P], d2);
    set_bit(bitboards[P], e2);
    set_bit(bitboards[P], f2);
    set_bit(bitboards[P], g2);
    set_bit(bitboards[P], h2);

    set_bit(bitboards[p], a7);
    set_bit(bitboards[p], b7);
    set_bit(bitboards[p], c7);
    set_bit(bitboards[p], d7);
    set_bit(bitboards[p], e7);
    set_bit(bitboards[p], f7);
    set_bit(bitboards[p], g7);
    set_bit(bitboards[p], h7);

    set_bit(bitboards[N], b1);
    set_bit(bitboards[N], g1);

    set_bit(bitboards[n], b8);
    set_bit(bitboards[n], g8);

    set_bit(bitboards[B], c1);
    set_bit(bitboards[B], f1);

    set_bit(bitboards[b], c8);
    set_bit(bitboards[b], f8);

    set_bit(bitboards[R], a1);
    set_bit(bitboards[R], h1);

    set_bit(bitboards[r], a8);
    set_bit(bitboards[r], h8);

    set_bit(bitboards[Q], d1);

    set_bit(bitboards[q], d8);

    set_bit(bitboards[K], e1);

    set_bit(bitboards[k], e8);

    print_board();
    return 0;
}
