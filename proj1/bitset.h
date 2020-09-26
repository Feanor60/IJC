/*bitset.h
 * @Řešení IJC-DU1, příklad a), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "error.h"

//typ bitoveho pole (pro predavani parametru funkce odkazem)
typedef unsigned long* bitset_t;

//typ indexu do bitoveho pole
typedef unsigned long bitset_index_t;



//bitset_create - definuje a _nuluje_ proměnnou jmeno_pole
#define bitset_create(jmeno_pole, velikost)\
bitset_index_t jmeno_pole[((velikost/((sizeof(bitset_index_t)*__CHAR_BIT__)))+(velikost % (sizeof(bitset_index_t)*__CHAR_BIT__) > 0 ? \
1 : 0))+1] = {velikost};\
assert(velikost < 500000002 && velikost > 64)\


//bitset_alloc - dynamicky alokuje pamět pro proměnnou jmeno_pole
#define bitset_alloc(jmeno_pole, velikost)\
assert(velikost > 64 && velikost < 500000002);\
bitset_t jmeno_pole =(bitset_t)\
calloc((velikost/(sizeof(bitset_index_t)*__CHAR_BIT__)) + \
((velikost % (sizeof(bitset_index_t)*__CHAR_BIT__)) > 0 ? 1 : 0)+1,sizeof(unsigned long));\
if(jmeno_pole == NULL){\
    error_exit("bitset_alloc: Chyba alokace paměti\n");\
}else{\
    *jmeno_pole = velikost;\
}


//bitset_free - uvolni dynamicky alokovanou pamět pro proměnnou jmeno_pole
#ifdef USE_INLINE
	inline void bitset_free(bitset_t jmeno_pole){
		free(jmeno_pole);
	}
#else
	#define bitset_free(jmeno_pole) free(jmeno_pole)
#endif

//bitset_size - vrátí první prvek proměnné jmeno_pole, na kterém je uložena jeho velikost
#ifdef USE_INLINE
    inline unsigned long bitset_size(bitset_t jmeno_pole)
    {
        return jmeno_pole[0];
    }
#else
    #define bitset_size(jmeno_pole) jmeno_pole[0]
#endif


//bitset_setbit - nastaví bit v proměnné jmeno_pole na indexu index na 0 nebo 1 podle toho jestli vyray == true
#ifdef USE_INLINE
    inline void bitset_setbit(bitset_t jmeno_pole,bitset_index_t index,bitset_index_t vyraz){
        if((bitset_index_t)index >= bitset_size(jmeno_pole)){
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
               (unsigned long)index, bitset_size(jmeno_pole));
        }if(vyraz){
            jmeno_pole[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] |= 
        (   (bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)));
        }else{\
            jmeno_pole[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] &= \
            ~((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)));
        }
    }
#else
    #define bitset_setbit(jmeno_pole,index,vyraz)\
    if((bitset_index_t)index >= bitset_size(jmeno_pole)){ \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",\
               (unsigned long)index, bitset_size(jmeno_pole)); \
    }else{\
    (vyraz ? \
        (jmeno_pole[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] |= \
        ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__))))\
    :\
        (jmeno_pole[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] &= \
        ~((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)))) );\
    }
#endif   



//bitset_getbit - vrátí 0 nebo 1 podle toho jestli v proměnné jmeno_pole na indexu index daný bit 1 nebo 0 
#ifdef USE_INLINE
    inline int bitset_getbit(bitset_t jmeno_pole,bitset_index_t index){
    if(index >= bitset_size(jmeno_pole)){
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", \
               (unsigned long)index,bitset_size(jmeno_pole));
    }
    return (bitset_index_t)((jmeno_pole[(index/(sizeof(bitset_index_t)*__CHAR_BIT__)+1)] &
    ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)))) > 0);
    }
#else
    #define bitset_getbit(jmeno_pole, index)\
    ((bitset_index_t)index >= bitset_size(jmeno_pole)) ?\
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, bitset_size(jmeno_pole)), 0\
    :\
    (bitset_index_t)((jmeno_pole[(index/(sizeof(bitset_index_t)*__CHAR_BIT__)+1)] & \
    ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)))) > 0) \
    
#endif
