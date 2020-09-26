/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"
#include <stdlib.h>

//zrušení všech položek, tabulka zůstane prázdná

void htab_clear(htab_t * t){ 

	htab_iterator_t iter;
	htab_iterator_t iter_next;
	htab_iterator_t end;

	iter = htab_begin(t);
	end = htab_end(t);

	while(iter.idx != end.idx) { //while itering through actual entries

		iter_next = htab_iterator_next(iter);

		htab_erase(t,iter);

		iter = iter_next;
	}

}