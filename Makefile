THIS_FILE := $(lastword $(MAKEFILE_LIST))
CC := gcc -Wall -Wextra -Werror -oFast $(DEBUG)
RM := rm -f

all:
	${CC} -c shared.c -I./ -o build/shared.o
	${CC} -c bitboard.c -I./ -o build/bitboard.o
	${CC} -c zobrist.c -I./ -o build/zobrist.o
	${CC} -c attacks.c -I./ -o build/attacks.o
	${CC} -c io.c -I./ -o build/io.o
	${CC} -c pemmican.c -I./ -o build/pemmican.o

	${CC} build/shared.o build/bitboard.o build/zobrist.o build/attacks.o \
	build/pemmican.o build/io.o -o build/pemmican

debug:
	$(MAKE) clean
	$(MAKE) $(THIS_FILE) DEBUG="-g -D_DEBUG" all
	objdump -M "intel" -D build/shared.o -l > build/shared.S
	objdump -M "intel" -D build/bitboard.o -l > build/bitboard.S
	objdump -M "intel" -D build/zobrist.o -l > build/zobrist.S
	objdump -M "intel" -D build/attacks.o -l > build/attacks.S
	objdump -M "intel" -D build/io.o -l > build/io.S
	objdump -M "intel" -D build/pemmican.o -l > build/pemmican.S

clean:
	$(RM) build/*.o build/pemmican

re:
	$(MAKE) clean
	$(MAKE) all
