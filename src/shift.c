#include<stdio.h>


main()
{
  
  int i;

  for(i=1;i<100; ++i)
    printf("\n i=%d i<<1 = %d i<<5 = %d     i>>2=%d i>>5=%d",i,i<<1,i<<5,i>>2,i>>5);
}
