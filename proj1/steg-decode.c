/*steg-decode.c
 * @Řešení IJC-DU1, příklad b), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include <stdio.h>
#include "ppm.c"
#include "bitset.h"
#include "eratosthenes.c"
#include <ctype.h>

char *chain_global; //globální promněnná pro uvolnění paměti při error_exit
bitset_t errat_global; //globální promněnná pro uvolnění paměti při error_exit
struct ppm *foo_global; //globální promněnná pro uvolnění paměti při error_exit

/* @název: char * chain_realloc(char * old_ptr, int size)
 * @brief: funkce zvětší alokované misto o size a vrátí ukazatel na nově alokovanou pamět
 * @param1: char * old_ptr: ukazatel na alokovanou pamět
 * @param2: int size: udává kolik paměti se má přidat k alokované paměti
 * @return: funkce vrací ukazatel na nově alokovanou pamět
 */
char * chain_realloc(char * old_ptr, int size);

/* @název: do_at_exit()
 * @brief: po ukončení programu funkce uvolní alokovanou pamět
 */
void do_at_exit();

/* @název: int main(int argc, char* argv[1])
 * @brief: funkce dekóduje obrázek ze vstupu a dešifruje tajnou zprávu
 * @param1: int argc: počet argumentů funkce, pokud je větší než dva funkce nebzla spuštěna správně
 * @param2: char* argv[] ukazatel na název obrázku
 */
int main(int argc, char* argv[]){

	atexit(do_at_exit);

	struct ppm *foo;

	if(argc != 2){
		error_exit("spatny pocet argumentu");
	}else{
		foo = ppm_read(argv[1]);
	}

	if(foo == NULL){
		exit(1);
	}

	foo_global = foo;

	unsigned xsize = foo->xsize;
	unsigned ysize = foo->ysize;

	
	bitset_alloc(errat, 3*xsize*ysize);
	errat_global = errat;
	Eratosthenes(errat);

	char size = 1;
	char znak = 0;
	int posun = 0;
	char mask = 1;
	int length = 0;
	char *chain =(char*) malloc(sizeof(char)*1);
	chain_global = chain;

	for(bitset_index_t i = 23; i < 3*xsize*ysize; i++){
		if(!(bitset_getbit(errat,i))){
			znak |= (foo->data[i] & mask) << posun;
			posun++;

			if(posun == 8){

				if(znak == EOF){
					error_exit("chybny formát");
				}

				size++;
				chain[length] = znak;
				chain = chain_realloc(chain, size);
				chain_global = chain;

				if(znak == '\0'){
					break;
				}
				
				length++;
				znak = 0;
				posun = 0;
			}
		}
	}

	if(chain[length]!='\0'){
		error_exit("chybny formát");
	}
	printf("%s\n", chain);

	return 0;
}

char * chain_realloc(char * old_ptr, int size){
	char *new_ptr = (char*) realloc(old_ptr, size);
	if(new_ptr == NULL){
		error_exit("realloc failed", size);
	}
	return new_ptr;
}

void do_at_exit(){
	free(chain_global);
	free(errat_global);
	free(foo_global);
}