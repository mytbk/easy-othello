#include <stdlib.h>
#define Debug

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

