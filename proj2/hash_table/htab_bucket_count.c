/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"

size_t htab_bucket_count(const htab_t * t){     // velikost pole

	return t->arr_size;
}