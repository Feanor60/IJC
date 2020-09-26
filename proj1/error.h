/*error.h
 * @Řešení IJC-DU1, příklad b), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);