/*primes.c
 * @Řešení IJC-DU1, příklad a), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include <stdio.h>
#include "eratosthenes.c"
#include "error.c"

#ifdef USE_INLINE
extern void bitset_free(bitset_t jmeno_pole);

extern unsigned long bitset_size(bitset_t jmeno_pole);

extern void bitset_setbit(bitset_t jmeno_pole,bitset_index_t index,bitset_index_t vyraz);

int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
#endif

/* @název: in main()
 * @brief: funkce vytvoří bitové pole a předá ho funkci Eratosthenes poté vypíše posledních 10 prvočísel z pole,
 *  funkce také sleduje délku běhu programu
 */

int main()
{
    time_t start;
    start = clock();

    bitset_create(p,500000000);
    Eratosthenes(p);

    int counter = 0;
    for(bitset_index_t i = bitset_size(p) - 1; counter < 11; i--){
        if(counter < 10){
            if(!(bitset_getbit(p,i))){ 
                counter++;
            }
        }else{
			i++;
            while(counter > 0){
                if(!(bitset_getbit(p,i))){
                    printf("%ld\n", i);
                    counter--;
                }
                i++;
            }
            counter += 11;
        }         
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    return 0;
}