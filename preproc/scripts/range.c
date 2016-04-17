#include <stdio.h>

/* #@@range_begin(sample)  */
void
put_hello(char *name)
{
  printf("hello, %s!\n", name);
}
/* #@@range_end(sample) */

int main()
{
  put_hello("world");
}
