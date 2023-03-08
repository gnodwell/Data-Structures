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

  int y = 1 * 256 +
          0 * 128 +
	  1 * 64 +
	  1 * 32 +
	  1 * 16 +
	  0 * 8 +
	  1 * 4 +
	  0 * 2 +
	  1 * 1;

  printf( "x=%d, y=%d, x&y=%d\n", x, y, x&y );

  return 0;
}
