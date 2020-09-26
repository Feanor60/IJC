/*eratosthenes.c
 * @Řešení IJC-DU1, příklad a), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include <math.h>
#include "eratosthenes.h"

/* @název: void Eratosthenes(bitset_t pole)
 * @brief: funkce nastaví všechny bity, které nejsou na indexu prvočísel na 1
 * @param1: bitset_t pole: ukazatel na bitové pole
 */

void Eratosthenes(bitset_t pole){

    bitset_setbit(pole,0,1); //0 neni prvocislo
    bitset_setbit(pole,1,1); //1 neni prvocislo

	unsigned long velikost = bitset_size(pole);
    unsigned long root = sqrt(velikost);

    for(bitset_index_t i = 2; i < root; i++){
        if(bitset_getbit(pole,i) == 0){
            for(bitset_index_t j = 2; (j*i) < velikost; j++){
                bitset_setbit(pole,j*i,1);
            }
        }    
    }
}