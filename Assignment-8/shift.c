#include <stdio.h>

int main( int argc, char **argv )
{
  int x = 1 * 256 +
          0 * 128 +
	  1 * 64 +
	  1 * 32 +
	  1 * 16 +
	  0 * 8 +
	  1 * 4 +
	  0 * 2 +
	  1 * 1;

  int shift=0;

  printf( "x=%d, shift=%d, x>>shift=%d\n", x, shift, x>>shift );

  return 0;
}
