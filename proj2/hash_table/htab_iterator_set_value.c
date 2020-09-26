/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"

//přepisuje hodnotu, cíl musí existovat

htab_value_t htab_iterator_set_value(htab_iterator_t it, htab_value_t val){

	htab_iterator_t temp = it;

	temp.ptr->value = val;

	return htab_iterator_get_value(temp);
}