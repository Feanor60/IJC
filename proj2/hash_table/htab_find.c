/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

//htab_iterator_t htab_find(htab_t *t, htab_key_t key);
//      V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
//        - pokud jej nalezne, vrátí iterátor na záznam
//        - pokud nenalezne, vrátí iterátor htab_end(t)

#include "private.h"

htab_iterator_t htab_find(htab_t * t, htab_key_t key){

	size_t hash = htab_hash_fun(key) % t->arr_size;

	htab_iterator_t temp;
	temp.t = t;
	temp.idx = hash;
	temp.ptr = t->array[hash];

	while(temp.ptr->next != NULL && htab_iterator_valid(temp) ){ //iterate while in t

		if(temp.ptr->key == key){
			return temp;
		}

		temp = htab_iterator_next(temp); //iter to the next item
	}

	return temp;	
}