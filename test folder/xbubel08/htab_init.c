/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"
#include <stdlib.h>



htab_t *htab_init(size_t n){ // konstruktor tabulky

	htab_t* temp; //temporary structure

	if(n > 0){
		temp = malloc(sizeof(htab_t) + n * sizeof(struct htab_item)); 
		//allocate data for structure - size of htab_t + (n * 1.3) because it is usually better to have only 70-75 %
		//of your hash table occupied


		if(temp != NULL){ //malloc was succesfull

			temp->size = 0; //begins with 0 entries
			temp->arr_size = n; //n number of buckets

			for(size_t i = 0; i < n; i++){
				temp->array[i] = NULL; // fill flexible member with n - 1 entries
			}

			return temp;
		}
	}

	return 0;
}