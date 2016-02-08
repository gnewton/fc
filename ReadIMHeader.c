#include "im_io.h"

int ReadImHeader(fptr,width,height)
FILE *fptr;
int *height, *width;
{
  char    bits[12],
  line[80], command[80], ch,*strdup();
  
  int done, number, nbits;

  	
  done = 0;
  while ( !done )
    {
      ch = fgetc (fptr);
      if (ch == '\000' || ch == '\014') done = 1;
      else
	{
	  ungetc (ch, fptr);
	  fgets (line, 80, fptr);
	  number = 0;
	  sscanf (line, "%s %d", command, &number);
	  if ( toupper(command[0]) == 'W' ) *width = number;
	  else if ( toupper(command[0]) == 'H' ) *height = number;
	  else if ( toupper(command[0]) == 'P' )
	    {
	      sscanf (line, "%s %s", command, bits);
	      if ( toupper(bits[0]) != 'N') 
		return(0);
	      else
		{
		  sscanf (bits+1, "%d", &nbits);
		  if (nbits != 8) 
		    return(0);
		}
	    }
	}
    }
  return(1);
  
}


 
