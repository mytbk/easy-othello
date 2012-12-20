#include <stdlib.h>
#include <cstring>
#include "common.h"

void clrscr()
{
#ifdef linux
	system ("clear");
#else
	system ("cls");
#endif
}

