/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"

//        i = htab_iterator_get_value(iterator);
//          vrací hodnotu, cíl musí existovat

htab_value_t htab_iterator_get_value(htab_iterator_t it){

	htab_iterator_t temp = it;


	return temp.ptr->value;
}