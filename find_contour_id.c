#include "stuff.h"
 


SEGMENTS_LIST *FindContourPtr(goal,starting_contour_ptr, head_contour_list_ptr)
int goal;
SEGMENTS_LIST *starting_contour_ptr, **head_contour_list_ptr;


{
  int id;
  SEGMENTS_LIST *next_contour_list_ptr;
  EDGE_LIST *contour_ptr;
  
 
  id = ident(goal);
  if(id == starting_contour_ptr->list_id)
    return(starting_contour_ptr);
  else
    {
      next_contour_list_ptr = *head_contour_list_ptr;
      
      if(id <= ListIdStart)
	{
	  while(next_contour_list_ptr != NULL )
	    {
	      if(next_contour_list_ptr->list_id == id)
		return(next_contour_list_ptr);
	      next_contour_list_ptr = next_contour_list_ptr->next_contour;
	    }
	  return(NULL);
	}
      else
	/* special case - when the new contour is made up of only 1 or 2 edges */
	while(next_contour_list_ptr != NULL )
	  {
	    if(next_contour_list_ptr->num_list_points <= 2)
	      {
		contour_ptr = next_contour_list_ptr->contour_ptr;
		if(contour_ptr->n == goal ||
		   (contour_ptr->next != NULL &&
		    contour_ptr->next->n == goal))
		  {
		    return(next_contour_list_ptr);
		  }
		else
		  next_contour_list_ptr = next_contour_list_ptr->next_contour;
	      }
	    else
	      next_contour_list_ptr = next_contour_list_ptr->next_contour;
	  }
    }
  return(NULL);
}


  

					  
