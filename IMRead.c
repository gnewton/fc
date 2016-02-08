  
#include "im_io.h"
        
byte *Imread(filename, width, height)
char    filename[];
int     *height, *width;
{
  byte    *image;
  FILE    *fptr, *fopen();
  char    bits[12];
  int     imsize;
  
  char    line[80], command[80], ch, 
  *strdup(),
  *getenv();
  
  int     done, number, nbits;  

  void FindFile();
    
  FindFile(filename,&fptr);
  if(fptr == NULL)
    return(NULL);
  else
    {
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
		    {
		      image = NULL;
		      done = -1;
		    }
		  else
		    {
		      sscanf (bits+1, "%d", &nbits);
		      if (nbits != 8) 
			{
			  image = NULL;
			  done = -1;
			}
		    }
		}
	    }
	}
      if (done != -1 && width != 0 && height != 0)
	{
	  imsize = *height * *width;
	  image = (byte *) malloc (sizeof(byte)*imsize);
	  fread (image, imsize, 1, fptr);
	  fclose (fptr);
	}
      return (image);
    }
}
