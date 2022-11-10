#ifndef _PEMTYPES_H_
#define _PEMTYPES_H_

typedef unsigned long long U64;

enum {
    white,
    black,
    both
};

enum {
    rook,
    bishop
};

enum {
    wckc = 1,
    wcqc = 2,
    bckc = 4,
    bcqc = 8
};

#endif  // _PEMTYPES_H_