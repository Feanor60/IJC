/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */


#include "private.h"

#ifndef __USE_INLINE__
#define __USE_INLINE__

extern inline bool htab_iterator_valid(htab_iterator_t it);

#endif

// - Funkce pro čtení/zápis přes iterátor:
//        cstr = htab_iterator_get_key(iterator);
//          vrací klíč, cíl musí existovat

htab_key_t htab_iterator_get_key(htab_iterator_t it){

	htab_iterator_t temp = it;

	return temp.ptr->key;
}