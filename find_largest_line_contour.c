  
#include "stuff.h"
#include "search.h"


SEGMENTS_LIST *find_largest_line_contour(head_contour_list_ptr, pass, min_contour_length)
SEGMENTS_LIST **head_contour_list_ptr;
int pass, min_contour_length;


{
  SEGMENTS_LIST *list_ptr, *max_ptr;
  
  int max;
  
  max = 0;
  max_ptr = NULL;
  list_ptr = *head_contour_list_ptr;
  while(list_ptr != NULL)
    {
      switch(pass)
	{
	case Pass1:
	  if(list_ptr->num_end_points == 2 &&
	     list_ptr->Search_status != pass &&
	     list_ptr->num_split_points == 0)
	    {
	      if(list_ptr->num_list_points > min_contour_length &&
		 list_ptr->num_list_points > max)
		{
		  max = list_ptr->num_list_points;
		  max_ptr = list_ptr;
		}
	    }
	  break;
	  
	case Pass2:
	  if(list_ptr->num_end_points > 0 &&
	     list_ptr->Search_status != pass)
	    {
	      if(list_ptr->num_list_points > min_contour_length &&
		 list_ptr->num_list_points > max)
		{
		  max = list_ptr->num_list_points;
		  max_ptr = list_ptr;
		}
	    }
	  break;
	}
      list_ptr = list_ptr->next_contour;
    }
  return(max_ptr);
}
