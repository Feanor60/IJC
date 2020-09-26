/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "htab.h"
#include "io.h"
#include <stdlib.h>

#define max_size 500000 	//500000 because i tested my table on the /usr/share/dict/words
							//and it has around 500000 words

#define MAX_WORD_LEN 127 //implementation limit for lenght of word


int main(int argc, char **argv){

	if(argc < 2){
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}

	

	int max = MAX_WORD_LEN;
	char string[MAX_WORD_LEN + 1];
	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL){
		fprintf(stderr,"Error: cannot open file\n");
		return -1;
	}

	htab_t *t = htab_init(max_size);

	while(get_word(string, max, fp) != EOF){

		if(htab_lookup_add(t,string).ptr == NULL){
			fprintf(stderr,"Error: cannoc allocate item in table\n");
			htab_free(t);
			fclose(fp);
			return -1;
		}

	}

	

	htab_iterator_t iterator = htab_begin(t);
	htab_iterator_t invalid = htab_end(t);

	while(iterator.idx != invalid.idx){

		if(iterator.ptr != NULL){

			printf("%s\t", htab_iterator_get_key(iterator));//htab_iterator_get_key(iterator));
			printf("%d\n",htab_iterator_get_value(iterator));

		}
	
		iterator = htab_iterator_next(iterator);
	}
	
	htab_free(t);

	fclose(fp);

	return 0;	
}
