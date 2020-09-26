/*ppm.c
 * @Řešení IJC-DU1, příklad b), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @Přeloženo: gcc 9.2.1
 */

#include "ppm.h"
#include <stdio.h>
#include "error.c"

/* @název: struct ppm
 * @brief: struktura sloužící k uložení obrázku
 * @param1: unsigned xsize: proměnná typu unsigned int sloužící k uložení šířky obrázku
 * @param2: unsigned ysize: proměnná typu unsigned int sloužící k uložení výšky obrázku
 * @param3: char data[]: slouží k uložení bajtů pixelů obrázku
 */

struct ppm {
        unsigned xsize; 
        unsigned ysize;
        char data[];    // RGB bajty, celkem 3*xsize*ysize
     };

/*@název: struct ppm * ppm_read(const char * filename)
 *@brief: funkce přijme ukazatel na název obrázku, otevře obrázek, načte jeho obsah do struktury ppm a vrátí ji
 *@param1: const char * filename: ukazatel na první znak názvu obrázku
 */

struct ppm * ppm_read(const char * filename){

    FILE *fp = fopen(filename, "r");
    	if(fp == NULL){ 
		error_exit("nepodarilo se otevrit soubor", filename);
    	}
	char c[20];

	fscanf(fp,"%s", &c[0]);
	if(c[0]!='P'){
		warning_msg("chybný formát");
		return NULL;
	}
	if(c[1]!='6'){
		warning_msg("chybný formát");
		return NULL;
	}

	unsigned xsize;
	unsigned ysize;
	int color;
	fscanf(fp,"%*c %u", &xsize);
	fscanf(fp,"%*c %u", &ysize);
	fscanf(fp,"%*c %d", &color);

	if(color < 1 || color >= 65536){
		fclose(fp);
		warning_msg("chybný formát");
		return NULL;
	}

	unsigned max_size = 8000*8000*3;
	unsigned actual_size = xsize*ysize*3;

	if(actual_size >= max_size){
		fclose(fp);
		warning_msg("byla překročna maximální povolená velikost obrázku");
		return NULL;
	}

	if(actual_size < 3){
		fclose(fp);
		warning_msg("obrázek je příliš malý");
		return NULL;
	}
	
	struct ppm *foo = malloc(sizeof(struct ppm)+sizeof(char)*3*xsize*ysize);
	if(foo == NULL){
		fclose(fp);
		warning_msg("nepodarilo se alokovat pamet");
		return NULL;
	}

	foo->xsize = xsize;
	foo->ysize = ysize;

	unsigned size;

	c[0] = fgetc(fp); //přečtu jeden prázdný znak, který následuje po definici maximálního roysahu barvy

	size = fread(foo->data, sizeof(char), actual_size, fp);
	if(foo->data == NULL){
		fclose(fp);
		warning_msg("nepodarilo se nahrat data");
		return NULL;
	}
	if(size != actual_size){
		ppm_free(foo);
		fclose(fp);
		warning_msg("chybný formát");
		return NULL;
	}
	c[0] = fgetc(fp);
	if(c[0] != EOF){
		error_exit("chybný formát");
	}
	

	fclose(fp);
	return foo;
}

void ppm_free(struct ppm *p){
	free(p);
}