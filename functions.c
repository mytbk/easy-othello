#include <stdlib.h>
#include "debug.h"

void clrscr() 
{
#ifndef debug
#ifdef linux
	system ("clear");
#else
	system ("cls");
#endif
#endif
}

