/* EdgeListBuild */

#include "stuff.h"

/* EdgeListBuild - sent the edge mag and the edge direction, returns an array
   containing three different classes of edges: Superior, Inferior
   and Other.
   
   
   copyright glen newton 87/12/01
   u of waterloo
   
   */


int EdgeListBuild(edges, strong_edges)
EDGE_LIST **edges, **strong_edges;

{
  extern IMAGE im_struct;
  extern  int Edge_Thresh, K;
    
  EDGE_LIST *tmp, *ptr;
  
  int ii, jj, width, height,
  n, 
  na, nb, nc, nd, nf, ng, nh, ni,
  no, np, nq, nr, ns, nt, nu, nv,
  sum,
  total, total_squared ;
  
  short *edge_mag, *candidates,
  average_Edge_value,
  edge_flag,
  directions,
  a, b, c, d, e, f, g, h, i,
  width2, o, p, q, r, s, u, v;
  
  byte *edge_dir;
  
  
  width = im_struct.width;
  height = im_struct.height;

  edge_mag = im_struct.edge_mag;
  edge_dir = im_struct.edge_dir;
  candidates = im_struct.candidates;
  
  
  
  sum = 0 ;
  total = 0 ;
  total_squared = 0;
  
  /* look at the mags  parallel to the direction of the present pixel:
     if either is greater, the present pixel is not a candidate */
  ii = im_struct.imsize;
    
  for ( n = 0 ; n < ii ; ++n ) 
    {
      candidates[ n ] = Non_Edge ;
	  
      if ( edge_mag[ n ] > Edge_Thresh ) 
	{ 
	  e = edge_mag[ n ] ;
	  directions = edge_dir[ n ] % 4 ; 
	  
	  edge_flag = FALSE;
	  na = n-width-1;
	  nb = n-width;
	  nc = n-width+1;
	  nd = n-1;
	  nf = n+1;
	  ng = n+width-1;
	  nh = n+width;
	  ni = n+width+1;
	  width2 = width+width;
	  
	  switch( directions ) 
	    {     
	    case 0 : 
	      np = n - width2;
	      nu = n + width2;
	      p = edge_mag[np];
	      u = edge_mag[nu];
	      
	      b = edge_mag[ nb ] ;
	      h = edge_mag[ nh ] ;
	      if( e > b && e > h )
		{
		  if(edge_dir[n] == edge_dir[nc] ||
		     edge_dir[n] == edge_dir[nf] ||
		     edge_dir[n] == edge_dir[ni] &&
		     edge_dir[n] == edge_dir[na] ||
		     edge_dir[n] == edge_dir[nd] ||
		     edge_dir[n] == edge_dir[ng])
		    edge_flag = TRUE;
		}
	      break;
	      
	    case 1 : 
	      no = n - width2 - 2;
	      nv = n + width + 2;
	      o = edge_mag[no];
	      v = edge_mag[nv];
	      
	      i = edge_mag[ ni ] ;   
	      a = edge_mag[ na ] ;
	      if ( e > i && e > a ) 
		{
		  if(edge_dir[n] == edge_dir[nb] ||
		     edge_dir[n] == edge_dir[nc] ||
		     edge_dir[n] == edge_dir[nf] &&
		     edge_dir[n] == edge_dir[nd] ||
		     edge_dir[n] == edge_dir[ng] ||
		     edge_dir[n] == edge_dir[nh])
		    edge_flag = TRUE;
		}
	      break;
	      
	    case 2 :
	      nr = n - 2;
	      ns = n + 2;
	      r = edge_mag[nr];
	      s = edge_mag[ns];
	      
	      d = edge_mag[ nd ] ;
	      f = edge_mag[ nf ] ;
	      if( e > d && e > f) 
		{
		  if(edge_dir[n] == edge_dir[na] ||
		     edge_dir[n] == edge_dir[nb] ||
		     edge_dir[n] == edge_dir[nc] &&
		     edge_dir[n] == edge_dir[ng] ||
		     edge_dir[n] == edge_dir[nh] ||
		     edge_dir[n] == edge_dir[ni] )
		    edge_flag = TRUE;
		}
	      break;
	      
	    case 3 :
	      nq = n - width2 + 2;
	      nr = n + width2 - 2;
	      q = edge_mag[nq];
	      r = edge_mag[r];
	      
	      g = edge_mag[ ng ] ;
	      c = edge_mag[ nc ] ;
	      if (e > g && e > c )
		{
		  if(edge_dir[n] == edge_dir[nd] ||
		     edge_dir[n] == edge_dir[na] ||
		     edge_dir[n] == edge_dir[nb] &&
		     edge_dir[n] == edge_dir[nf] || 
		     edge_dir[n] == edge_dir[nh] ||
		     edge_dir[n] == edge_dir[ni])
		    edge_flag = TRUE;
		}
	      break;
	    }
	  if (edge_flag) 
	    {
	      edge_flag = FALSE;
	      candidates[n] = Edge;
	      tmp = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	      tmp->n = n;
	      tmp->next = *edges;
	      *edges = tmp;
	      if(edge_mag[n] > Edge_Thresh)
		{
		  ++sum;
		  total += edge_mag[n];
		  /* the edges are put in the list before this
		     if only for output purposes ... they should
		     not be put in the list, and below (where
		     candidates which don't make it are set to
		     non_edge), they should not be changed at
		     all, and left EDGE. this is so when searching
		     is done later, the EDGEs in candidates will
		     be accessible      */
		}
	    }
	  
	} /*  end if  */
	
    } /*  end n loop  */
  
  average_Edge_value = total/sum ;
  
  /*   this is a test */ 
  
  average_Edge_value = K * (float)average_Edge_value ;
  
  
  
  /*   end test       */
  
  
  
  
  /* figure out if the pixel is a candidate, and if it is, see if it
     is a Superior, Inferior, or Other edge.                      */
  
  tmp = *edges;
  n=0;
  while( tmp != NULL )
    {
      if ( edge_mag[tmp->n] > (average_Edge_value )
	  && edge_mag[tmp->n] > Edge_Thresh)
	{
	  ++n;
	  candidates[tmp->n] = StrongEdge;
	  ptr = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  ptr->n = tmp->n;
	  ptr->next = *strong_edges;
	  *strong_edges= ptr;
	} 
      
      else
	candidates[tmp->n] = Edge;
      
      tmp = tmp->next;
    }
}


