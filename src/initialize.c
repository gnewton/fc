 
#include "stuff.h"


int initialize()
{
  extern IMAGE im_struct;
  extern byte *Trace;
  extern int TraceFlag;
  
  int ii, width, height;
  short *edge_mag;
  byte *edge_dir;
  

  width = im_struct.width;
  height = im_struct.height;
  im_struct.imsize = width*height;
  
  edge_mag = (short *) malloc( sizeof (short) *  width * height ) ;		
  edge_dir = (byte * ) malloc( sizeof (byte) * width * height ) ;
  
  im_struct.candidates = (short *) malloc( sizeof (short) * width * height ) ;
  
  
  /* make sure there are no edge effects by setting perimeter 
     pixel values of the edge detector mag and direction
     so they won't cause any trouble                   */
  
  for( ii = 0; ii <width; ++ii)
    {
      edge_dir[width + ii ] = -1;
      edge_mag[ width ] = 0 ;
    }
  for( ii = 0; ii < width * height; ii = ii + width  )
    {
      edge_dir[ ii ] = -1 ;
      edge_mag[ ii ] = 0 ;
    }
  for (ii = 0; ii <width; ++ii)
    {
      edge_dir[ width * (height - 1) + ii ] = -1 ;  
      edge_mag[ width * (height - 1) + ii ] = 0 ;
    }   
  im_struct.edge_mag = edge_mag;
  im_struct.edge_dir = edge_dir;

  if(TraceFlag)
    {
      Trace = (byte*)malloc(sizeof(byte)*width*height);
      for(ii=0;ii<width*height;++ii)
	Trace[ii] = 255;
    }
  
}




