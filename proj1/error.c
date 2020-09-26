/*error.c
 * @Řešení IJC-DU1, příklad b), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* @název: void warning_msg(const char *fmt, ...)
 * @brief: funkce vypíše na stderr "CHYBA: " a dále string fmt + další argumenty předané funkci
 * @param1: const char *fmt: ukazatel na string, který má funkce vypsat
 * @param2: ...: nespecifikovaný počet argumentů, které funkce také vypíše
 */

void warning_msg(const char *fmt, ...){

    va_list ap;

    fprintf(stderr,"CHYBA: ");

    va_start(ap, fmt);

    vfprintf(stderr, fmt, ap);

    va_end(ap);

    fprintf(stderr,"\n");
}

/* @název: void error_exit(const char *fmt, ...)
 * @brief: funkce vypíše na stderr "CHYBA: " a dále string fmt a poté ukončí program pomocí exit(1)
 * @param1: const char *fmt: ukazatel na string, který má funkce vypsat
 * @param2: ...: nespecifikovaný počet argumentů, které funkce potřebuje kvůli řetězci fmt
 */

void error_exit(const char *fmt, ...){

    va_list ap;

    fprintf(stderr,"CHYBA: ");

    va_start(ap, fmt);

    vfprintf(stderr, fmt, ap);

    va_end(ap);

    fprintf(stderr,"\n");
    
    exit(1);
}