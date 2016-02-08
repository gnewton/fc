
#include "stuff.h"

EDGE_LIST *find_neighbours(neigh_list,num_nabors,n)

int n, *num_nabors;
EDGE_LIST *neigh_list;


{
  extern IMAGE im_struct;
  
  short *candidates;
  
  EDGE_LIST *new_nb;
  int width = im_struct.width,
  i, a[4], num_ones;
  
  candidates = im_struct.candidates;
  
  *num_nabors = 0;
  
  if(candidates[n-width] <= StrongEdge)
    {
      ++*num_nabors;
      if(candidates[n-width] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n-width;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n-width] = OnNeighbourList;
	}
    }
  if(n+width > width*im_struct.height|| n+width+1> width*im_struct.height||n-width-1<0)
    printf("\n\n\n find_neighbours   *************\n\n");
  
  if(candidates[n+width] <= StrongEdge)
    {
      ++*num_nabors; 
      if(candidates[n+width] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n + width;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n+width] = OnNeighbourList;
	}
    }
  
  if(candidates[n+1] <= StrongEdge)
    {
      ++*num_nabors;
      if(candidates[n+1] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n + 1 ;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n+1] = OnNeighbourList;
	}
    }
  
  if(candidates[n-1] <= StrongEdge)
    {
      ++*num_nabors;
      if(candidates[n-1] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n-1;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n-1] = OnNeighbourList;
	}
    }
  
  if(candidates[n+width+1] <= StrongEdge) 
    {
      ++*num_nabors;
      if(candidates[n+width+1] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n+width+1;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n+width+1] = OnNeighbourList;
	}
    }
  
  if(candidates[n+width-1] <= StrongEdge)
    {
      ++*num_nabors;
      if(candidates[n+width-1] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n+width-1;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n+width-1] = OnNeighbourList;
	}
    }
  
  if(candidates[n-width+1] <= StrongEdge)
    {
      ++*num_nabors;
      if(candidates[n-width+1] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n - width +1;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n-width+1] = OnNeighbourList;
	}
    }
  
  if(candidates[n-width-1] <= StrongEdge)
    {
      ++*num_nabors;
      if(candidates[n-width-1] == StrongEdge)
	{
	  new_nb = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  new_nb->n = n - width - 1;
	  new_nb->next = neigh_list;
	  neigh_list = new_nb;
	  candidates[n-width-1] = OnNeighbourList;
	}
    }
  
  if(*num_nabors <= 1)
    candidates[n] = EndPoint;
  else
    
    {
      i = 0;
      
      /* all following ifs assume that StrongEdge < ContourEdge, and that
	 there isn't anything else < ContourEdge    */
      
      if(candidates[n+width+1] <= StrongEdge)
	{
	  a[i] = 7;
	  ++i;
	}
      if(candidates[n+width] <= StrongEdge)
	{
	  a[i] = 6;
	  ++i;
	}
      if(candidates[n+width-1] <= StrongEdge)
	{
	  a[i] = 5;
	  ++i;
	}
      if(candidates[n-1] <= StrongEdge)
	{
	  a[i] = 4;
	  ++i;
	}
      if(candidates[n-width-1] <= StrongEdge)
	{       
	  a[i] = 3;
	  ++i;
	}
      if(candidates[n-width] <= StrongEdge)
	{
	  a[i] = 2;
	  ++i;
	}
      if(candidates[n-width+1] <= StrongEdge)
	{
	  a[i] = 1;
	  ++i;
	}
      if(candidates[n+1] <= StrongEdge)
	{
	  a[i] =0 ;
	  ++i;
	}
      
      if(*num_nabors == 2)
	{
	  if((8 + a[1] - a[0]) == 1 || a[0] - a[1] == 1)
	    candidates[n] = EndPoint;  
	}
      else
	{
	  num_ones = 0;
	  if((a[0] - a[1]) == 1)
	    ++num_ones;
	  if((a[1] - a[2]) == 1)
	    ++num_ones;
	  
	  if(*num_nabors == 4)
	    {
	      if((a[2] - a[3]) == 1)
		++num_ones;
	      if(( 8 + a[3] - a[0]) == 1 ) 
		++num_ones;
	      if(num_ones <= 1)
		candidates[n] = SplitPoint;
	    }
	  else
	    {
	      if(*num_nabors == 3)
		if(( 8 + a[2] - a[0]) == 1)
		  ++num_ones;
	      if(num_ones == 0)
		candidates[n] = SplitPoint;
	      else
		if(num_ones == 2)
		  candidates[n] = EndPoint;
	    }
	}
    }
  
  return(neigh_list);
}




 
