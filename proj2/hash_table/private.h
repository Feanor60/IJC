/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#ifndef __PRIVATE_H__
#define __PRIVATE_H__

#include "htab.h"

struct htab_item{
	htab_key_t key;
	htab_value_t value;
	struct htab_item *next;
};

struct htab{
	size_t size;
	size_t arr_size;
	struct htab_item *array[];
};

#endif
