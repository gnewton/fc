/* sobelx   */

#include "stuff.h"


/*      alternate sobel edge detector - this is a simple sobel edge detecter 
	which places only those edges 
	

	updated 90/02/10 - gcc -Wall
	
	*/


int Sobel()
{
  extern IMAGE im_struct;
  
  extern int J,MinValue,MaxValue, TmThresh,TmWaterWeight;
  
  
  extern byte *image;
  
  register  ii, jj, n, mag;
  
  int width,height,
  a, b, c, d, f, g, h, i,
  d0, d1, d2, d3 ;
    
  short *edge_mag;
  byte *edge_dir, dir;
  
  height = im_struct.height;
  width = im_struct.width;
  edge_dir = im_struct.edge_dir;
  edge_mag = im_struct.edge_mag;
  
  
  /* find edge mag and direction  (avoiding the edges)    */
  for (jj = 1; jj < height - 1; ++jj ) 
    { 
      for(ii = 1; ii < width - 1; ++ii) 
	{ 
	  n = (width*jj) + ii ;  
	  a = image[ n - width - 1 ] ;
	  b = image[ n - width ] ;
	  c = image[ n - width + 1 ] ;
	  d = image[ n - 1 ] ;
	  f = image[ n + 1 ] ;
	  g = image[ n + width -1 ] ;
	  h = image[ n + width ] ;
	  i = image[ n + width + 1 ] ;
	  
	      
	  if(a<MinValue || b<MinValue || c<MinValue
	     || d<MinValue || f< MinValue || g<MinValue
	     || h<MinValue ||i<MinValue ||
	     a>MaxValue || b>MaxValue || c>MaxValue
	     || d>MaxValue || f> MaxValue || g>MaxValue
	     || h>MaxValue ||i>MaxValue)
	    {
	      mag = 0;
	      dir = 0;
	    }
	  else
	    {
	      
	      d0 = c + 2*f + i -( a + 2*d + g )  ;
/*	      d0 = c + f<<1 + i -( a + d<<1 + g )  ;*/

	      
	      
	      mag = d0 ;
	      dir = 6 ;
	      
	      d1 = b + 2*c + f -( d + 2*g + h ) ;
/*	      d1 = b + c<<1 + f -( d + g<<1 + h ) ;*/
	      
	      if ( d1 > mag )  
		{
		  mag = d1 ;
		  dir = 7 ;
		} 
	      d2 = a + 2*b + c -( g + 2*h + i ) ;
/*	      d2 = a + b<<1 + c -( g + h<<1 + i ) ;*/
	      
	      if ( d2 > mag ) 
		{
		  mag = d2 ;
		  dir = 0 ;
		}
	      
	      d3 = d + 2*a + b -( h + 2*i + f ) ;
/*	      d3 = d + a<<1 + b -( h + i<<1 + f ) ;*/
	      
	      if( d3 > mag ) 
		{
		  mag = d3 ;
		  dir = 1 ;
		}
	      
	      if( -d0 > mag ) 
		{
		  mag = -d0 ;
		  dir = 2 ;
		}
	      
	      
	      if ( -d1 > mag )  
		{
		  mag = -d1 ;
		  dir = 3 ;
		}
	      
	      
	      if ( -d2 > mag ) 
		{
		  mag = -d2 ;
		  dir = 4 ;
		}
	      
	      
	      if ( -d3 > mag ) 
		{
		  mag = -d3 ;
		  dir = 5 ;
		}
	    }
	  edge_dir[ n ] = dir ;
	      edge_mag[ n ] = mag ;
	    }
	}
}



