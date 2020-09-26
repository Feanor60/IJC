/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */


#include "private.h"
#include <stdlib.h>


//htab_iterator_t htab_lookup_add(htab_t *t, htab_key_t key);
//      V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
//        - pokud jej nalezne, vrátí iterátor na záznam
//        - pokud nenalezne, automaticky přidá záznam a vrátí iterátor
//      Poznámka: Dobře promyslete chování této funkce k parametru key.
//      Poznámka: podobně se chová C++ operátor [] pro std::unordered_map

htab_iterator_t htab_lookup_add(htab_t * t, htab_key_t key){

	size_t hash = htab_hash_fun(key) % t->arr_size;
	int item_value; //for increasing value when the key is found

	htab_iterator_t dummy; //return this when something goes wrong
	dummy.ptr = NULL;
	dummy.t = NULL;
	dummy.idx = -1;

	htab_iterator_t iterator;
	htab_iterator_t iterator_old;
	iterator_old.ptr = NULL;
	htab_iterator_t iterator_new;

	iterator.idx = hash;
	iterator.t = t;
	iterator.ptr = t->array[hash]; 

	while(iterator.ptr != NULL){ //iterate through bucket till end or found


		if(!strcmp(htab_iterator_get_key(iterator),key) ){
			
			item_value = htab_iterator_get_value(iterator);
			item_value++;
			htab_iterator_set_value(iterator,item_value);
			return iterator;
		}

		iterator_old = iterator;
		iterator.ptr = iterator.ptr->next;
	}

	
	iterator_new.ptr = malloc(sizeof(struct htab_item));

	if(iterator_new.ptr == NULL){

		return dummy;
	}

	char *temp_key = malloc((strlen(key) + 1) * sizeof(char));


	// iterator_new.ptr->key 

	if(temp_key == NULL){

		free(iterator_new.ptr);
		return dummy;
	}

	strcpy(temp_key,key);

	// (void) strcpy(word, key);
	iterator_new.ptr->key = temp_key;
	iterator_new.ptr->next = NULL;
	htab_iterator_set_value(iterator_new,1);
	

	if(iterator_old.ptr == NULL){
		t->array[hash] = iterator_new.ptr;
	}else{
		iterator_old.ptr->next = iterator_new.ptr;
	}
	t->size++;


	return iterator_new;
}