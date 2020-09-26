/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#ifndef __IO_H__
#define __IO_H__

#define MAX_WORD_LEN 127 //implementation limit for lenght of word

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int get_word(char *s, int max, FILE *f);

#endif