#include "im_io.h"  


/* ------------------------------------------------ */


int Imsave(image_data,filename, xsize, ysize)
     char	*filename;
     byte	*image_data;
     int	xsize, ysize;
{
  FILE   *fptr, *fopen();
  int    status = 1;


  if(filename[0] == '\0')
    {
      printf ("width %d\n", xsize);
      printf ("height %d\n", ysize);
      printf ("pixel n8\n");
      printf ("*** image data starts ***\n%c", '\014');
      status = fwrite (image_data,xsize*ysize,1,stdout);
    }
  else
    {
        if (fptr = fopen (filename, "w"))
	  {
	    fprintf (fptr, "width %d\n", xsize);
	    fprintf (fptr, "height %d\n", ysize);
	    fprintf (fptr, "pixel n8\n");
	    fprintf (fptr, "*** image data starts ***\n%c", '\014');
	    status = fwrite (image_data,xsize*ysize,1,fptr);
	    fclose (fptr);
	  }
	else 
	  {
	    status = 0;
	  }
      }
  return (status);
}

