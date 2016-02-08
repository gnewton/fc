#include "im_io.h"

#define NameSize 30
int ImHeader(width,height,info)
int width,height;
char *info;

{
  printf("* %s\n",info);
  printf ("width %d\n", width);
  printf ("height %d\n", height);
  printf ("pixel n8\n");
  printf ("*** image data starts ***\n%c", '\014');
  
}

