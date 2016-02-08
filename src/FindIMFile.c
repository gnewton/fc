#include "im_io.h"

void FindFile(filename, fptr)
char    filename[];
FILE **fptr;
{
  char    line[80], 
  buffer[80], 
  ch,
  *impath, *path,
  *filename_im,
  bits[12],
  *strdup(),
  *getenv();
  
  
  int     done, number, nbits;

  filename_im = NULL;
  impath = NULL;
  
  if(!strcmp(filename,"stdin"))
    *fptr = stdin;
  else
    {
      *fptr = fopen (filename,"r");
      if (*fptr == NULL)
	{
	  sprintf(buffer,"%s%s",filename,".im");
	  *fptr = fopen (buffer,"r");
	  if (*fptr == NULL)
	    {
	      if(path=getenv("IMPATH"))
		{
		  sprintf(buffer,"%s%s%s",path,"/",filename);
		  *fptr = fopen (buffer,"r");
		  if (*fptr == NULL)
		    {
		      sprintf(buffer,"%s%s%s%s",path,"/",filename,".im");
		      *fptr = fopen (buffer,"r");
		    }
		}
	    }
	}
    }
}
