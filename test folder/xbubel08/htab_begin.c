/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */


#include "private.h"


htab_iterator_t htab_begin(const htab_t * t){   // iterátor na první záznam

	htab_iterator_t temp;
	temp.idx = 0;
	temp.ptr = t->array[0];
	temp.t = t;

	while(temp.idx <= htab_bucket_count(t)){

		if(temp.ptr != NULL){

			return temp;
		}

		
		temp.idx++;
		temp.ptr = t->array[temp.idx];
	}

	temp = htab_end(t);

	return temp;
}