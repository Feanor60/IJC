/*ppm.h
 * @Řešení IJC-DU1, příklad b), 19.3.2020
 * @Autor: Vojtěch Bůbela
 * @Fakulta: VUT FIT
 * @přeloženo gcc 9.2.1
 */

#include <stdio.h>

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);