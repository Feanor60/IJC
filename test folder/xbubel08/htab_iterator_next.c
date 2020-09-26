/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */


#include "private.h"

//posun iterátoru na další záznam v tabulce (nebo na htab_end(t))
//Poznámka: toto dělá i C++ operátor ++ pro iterátory

htab_iterator_t htab_iterator_next(htab_iterator_t it){

	htab_iterator_t temp = it;

	if(temp.ptr != NULL){
		
		if(temp.ptr->next != NULL){

			temp.ptr = temp.ptr->next;
			return temp;
		}
	}

	temp.idx++;
	
	if(temp.idx >= htab_bucket_count(temp.t)){
		return htab_end(temp.t);
	}

		temp.ptr=temp.t->array[temp.idx];

	return temp;
}