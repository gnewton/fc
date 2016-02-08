#include "stuff.h"
  
int DeleteFromContourList(head_contour_ptr, contour_ptr)
SEGMENTS_LIST **head_contour_ptr,*contour_ptr;


{
  
  SEGMENTS_LIST *head_ptr,*ptr,*last_contour_ptr;
  
  head_ptr = *head_contour_ptr;
  
  /* see if the contour to be deleted id the first on the list */
  if(head_ptr->list_id == contour_ptr->list_id)
    *head_contour_ptr = head_ptr->next_contour;
  else
    {
      last_contour_ptr = head_ptr;
      ptr = head_ptr->next_contour;
      while(ptr->next_contour !=NULL)
	{
	  if(ptr->list_id == contour_ptr->list_id) 
	    {
	      last_contour_ptr->next_contour = ptr->next_contour;
	      /* free(ptr); */
	      return(TRUE);
	    }
	  else
	    {
	      last_contour_ptr = ptr;
	      ptr = ptr->next_contour;
	    }
	}
      return(FALSE);
    }
  
}
