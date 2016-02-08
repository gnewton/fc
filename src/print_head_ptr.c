
#include "stuff.h"


int print_head_ptr(ptr)
	SEGMENTS_LIST *ptr;


{
  extern IMAGE im_struct;
  

     
  EDGE_LIST *contour_ptr;
  
 
  
  contour_ptr = ptr->contour_ptr;
  printf(" \n\n list_id = %d  listpoints = %d  end = %d  split = %d ", 
	 ptr->list_id, ptr->num_list_points, ptr->num_end_points, 
	 ptr->num_split_points);
  
  
}
