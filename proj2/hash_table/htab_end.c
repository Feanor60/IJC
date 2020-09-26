/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"
#include "stdlib.h"


htab_iterator_t htab_end(const htab_t * t){     // iterátor _za_ poslední záznam

	htab_iterator_t temp;

	size_t i;
	int last_valid_it;

	for(i = 0; i < htab_bucket_count(t); i++){

		if(t->array[i] != NULL)
			last_valid_it = i; 
		
	}

	temp.idx = last_valid_it + 1; //points to next entry after last valid entry


	return temp;
}