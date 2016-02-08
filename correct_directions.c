/*******************************************************************************************************/
/*                                                                                                     */
/*                  correct_directions                                                                 */
/*                                                                                                     */
/* finds the search direction of an end point. ie. if the end point direction points away from the     */
/*   contour, then the direction is Forwad. If the end point edge direction points to the contour, then*/
/*   the search direction is backward.                                                                 */
/*******************************************************************************************************/

#include "stuff.h"

int *correct_directions(end_points_ptr, num_end_points)
PTR_LIST *end_points_ptr;
int num_end_points;

{
  extern IMAGE im_struct;
  
  PTR_LIST *tmp;
  
  short  *candidates;
  byte *edge_dir;
  
  int width = im_struct.width,
  *search_direction, endpoint,i;
  
  
  edge_dir = im_struct.edge_dir;
  candidates = im_struct.candidates;
  
  tmp = end_points_ptr;
  search_direction = (int*)malloc(sizeof(int)*num_end_points);
  i = 0;
  
  while(i<num_end_points && tmp != NULL)
    {
      
      endpoint = tmp->pointer->n;
      
      switch(edge_dir[endpoint])
	{
	  case(0):
	    {
	      if(candidates[endpoint - 1] > StrongEdge &&
		 candidates[endpoint -1 -width] > StrongEdge &&
		 candidates[endpoint -1 + width] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(1):
	    {
	      if(candidates[endpoint + width - 1] > StrongEdge &&
		 candidates[endpoint + width] > StrongEdge &&
		 candidates[endpoint -1] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(2):
	    {
	      if(candidates[endpoint + width -1] > StrongEdge &&
		 candidates[endpoint + width] > StrongEdge &&
		 candidates[endpoint + width + 1] > StrongEdge)
		search_direction[i]= Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(3):
	    {
	      if(candidates[endpoint + width + 1] > StrongEdge &&
		 candidates[endpoint + width] > StrongEdge &&
		 candidates[endpoint + 1] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(4):
	    {
	      if(candidates[endpoint + 1] > StrongEdge &&
		 candidates[endpoint + 1 - width] > StrongEdge &&
		 candidates[endpoint + 1 + width] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(5):
	    {
	      if(candidates[endpoint - width + 1] > StrongEdge &&
		 candidates[endpoint + 1] > StrongEdge &&
		 candidates[endpoint - width] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(6):
	    {
	      if(candidates[endpoint - width] > StrongEdge &&
		 candidates[endpoint - width - 1] > StrongEdge &&
		 candidates[endpoint - width + 1] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	  case(7):
	    {
	      if(candidates[endpoint - width - 1] > StrongEdge &&
		 candidates[endpoint -1 -width] > StrongEdge &&
		 candidates[endpoint -1 + width] > StrongEdge)
		search_direction[i] = Backward;
	      else 
		search_direction[i] = Forward;
	      break;
	    }
	}
      tmp = tmp->next;
      ++i;
    }  
  return(search_direction);
}
