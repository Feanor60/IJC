/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"

size_t htab_size(const htab_t * t){  // počet záznamů v tabulce

	return t->size;
}