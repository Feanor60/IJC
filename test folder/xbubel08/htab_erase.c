/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"
#include <stdlib.h>
#include <stdio.h>

//- Funkce
//      void htab_erase(htab_t *t, htab_iterator_t it);
//      ruší zadaný záznam v tabulce (dávejte pozor na zneplatnění it touto
//      operací - je to potenciální problém i v C++)

void htab_erase(htab_t * t, htab_iterator_t it){

	htab_iterator_t temp;
	struct htab_item *item_temp;
	temp = it;

	if(temp.ptr != NULL){

	item_temp = temp.ptr;

	free((void*)item_temp->key);
	free(item_temp);

	t->array[temp.idx] = NULL;
	
	it = temp;
	}
}