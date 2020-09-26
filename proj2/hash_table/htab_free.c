/* @Vojtěch Bůbela
 * @VUT FIT
 * @příklad 2
 * @19.4.2020
 * @gcc 9.3.1
 */

#include "private.h"
#include <stdlib.h>

void htab_free(htab_t * t){     // destruktor tabulky	

	htab_clear(t);
	free(t);
	t = NULL;	
}