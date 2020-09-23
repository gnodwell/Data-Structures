#include <stdio.h>
#include "bandb.h"

int main( int argc, char **argv )
{
  char *str1 = "abcdefghi";
  unsigned char dest[9] = "01234567";

  printf( "\"%s\"\n", dest );

  getbytes( dest, 8, str1, 0 );
  dest[8] = '\0';

  printf( "\"%s\"\n", dest );

  getbytes( dest, 8, str1, 1 );
  dest[8] = '\0';

  printf( "\"%s\"\n", dest );

  return 0;
}
