/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */


//Napište funkci
//
//        int get_word(char *s, int max, FILE *f);
//
//      která čte jedno slovo ze souboru f do zadaného pole znaků
//      a vrátí délku slova (z delších slov načte prvních max-1 znaků,
//      a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
//      Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
//      Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.
//
//    Omezení: řešení v C bude tisknout jinak uspořádaný výstup
//      a je povoleno použít implementační limit na maximální
//      délku slova (např. 127 znaků), delší slova se ZKRÁTÍ a program
//      při prvním delším slovu vytiskne varování na stderr (max 1 varování).
//
//    Poznámka: Vhodný soubor pro testování je například seznam slov
//              v souboru /usr/share/dict/words
//              nebo texty z http://www.gutenberg.org/
//              případně výsledek příkazu:  "seq 1000000 2000000|shuf"

#include "io.h"
 
static int warning_printed = 0;

int get_word(char *s, int max, FILE *f){

	if(f == NULL){
		fprintf(stderr,"Error: invalid file pointer\n");
	}

	char c;

	while((c = fgetc(f)) != EOF && isspace(c));

	if(c == EOF){
		return EOF;
	}

	int string_counter = 1;
	s[0] = c;

	
	while(!isspace(c = fgetc(f))){

		if(c == EOF){
			s[string_counter] = '\0';
			return EOF;
		}

		s[string_counter] = c;
		string_counter++;	

		if(string_counter >= MAX_WORD_LEN && string_counter >= max){

			if(!warning_printed && string_counter > MAX_WORD_LEN){
			
				warning_printed = 1;
				fprintf(stderr,"Error: tried to load word longer than implementation limit\n");
			}
		
			s[string_counter] = '\0';

			while(!isspace(fgetc(f))){
				string_counter++;
			}

			return string_counter;			
		}

	}

	s[string_counter] = '\0';


	return string_counter;
}