#Makefile
# @Řešení IJC-DU1, příklad a) b), 19.3.2020
# @Autor: Vojtěch Bůbela
# @Fakulta: VUT FIT

CFLAGS =-g -O2 -std=c11 -pedantic -Wall -Wextra -lm

cc = gcc

all: primes primes-i steg-decode

primes: primes.c eratosthenes.c error.c bitset.h eratosthenes.h error.h
	$(cc) $(CFLAGS) primes.c -o primes

primes-i: primes.c eratosthenes.c error.c bitset.h eratosthenes.h error.h
	$(cc) $(CFLAGS) primes.c -o primes-i -DUSE_INLINE

steg-decode: steg-decode.c error.c error.h ppm.c ppm.h bitset.h eratosthenes.h eratosthenes.c
	$(cc) $(CFLAGS) steg-decode.c -o steg-decode

run: primes primes-i
	./primes && ./primes-i
	
.PHONY : clean clean_o
clean:
	rm primes primes-i steg-decode