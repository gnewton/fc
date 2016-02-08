
/* group - takes the first pixel of the contour in the list and expands, producing an ordered contour. 
   - expansion occurrs first in 4-connected, and when this fails for a particular pixel,
   continues 8-connected, just for that pixel
   
   */


#include "stuff.h"

#define AddToList(ptr,p)\
  tmp = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));\
  tmp->n = p;\
  tmp->next = ptr;\
  ptr = tmp;\
  candidates[p] = Grouped;\
  Flag = TRUE;


int group(strong_list)
SEGMENTS_LIST *strong_list;
{
  extern IMAGE im_struct;
  
  int width = im_struct.width, listid,
  n, Flag;
  
  short *candidates;  
  
  SEGMENTS_LIST  *lptr;
  
  EDGE_LIST *new_contour_ptr, *tmp;
  
  
  candidates = im_struct.candidates;
  
  lptr = strong_list;
  while(lptr != NULL)
    {
      
      if(lptr->num_end_points == 0 && lptr->num_split_points == 0)
	{
	  new_contour_ptr = NULL;
	  
	  n = lptr->contour_ptr->n;
	  
	  AddToList(new_contour_ptr, n);
	  listid = lptr->list_id;
	  
	  while(Flag)
	    {
	      Flag = FALSE;
	      
	      /* check 4-connected neighbours first */
	      if(candidates[n+1] == listid)
		{
		  AddToList(new_contour_ptr, n+1);
		  n = n+1;
		}
	      else
		if(candidates[n-1] == listid)
		  {
		    AddToList(new_contour_ptr, n-1);
		    n = n-1;
		  }
		else
		  if(candidates[n+width] == listid)
		    {
		      AddToList(new_contour_ptr, n+width);
		      n = n+width;
		    }
		  else
		    if(candidates[n-width] == listid)
		      {
			AddToList(new_contour_ptr, n-width);
			n = n-width;
		      }
		    else
		      if(candidates[n+width+1] == listid)
			{
			  AddToList(new_contour_ptr,n+width+1);
			  n = n+width+1;
			}
		      else
			if(candidates[n+width-1] == listid)
			  {
			    AddToList(new_contour_ptr,n+width-1);
			    n = n+width-1;
			  }
			else
			  if(candidates[n-width+1] == listid)
			    {
			      AddToList(new_contour_ptr,n-width+1);
			      n = n-width+1;
			    }
			  else
			    if(candidates[n-width-1] == listid)
			      {
				AddToList(new_contour_ptr,n-width-1);
				n = n-width-1;
			      }
	    }
	  lptr->contour_ptr = new_contour_ptr;
	}      
      lptr = lptr->next_contour;
      
      
    }/* end while  */
}


