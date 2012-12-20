#include <stdlib.h>

void clrscr() 
{
#ifdef linux
	system ("clear");
#else
	system ("cls");
#endif
}

