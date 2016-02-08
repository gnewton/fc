
#include "stuff.h"

int *find_n_end_points(num_end_points, contour_ptr)
short num_end_points;
EDGE_LIST *contour_ptr;
     
{
  extern IMAGE im_struct;
  
  short *candidates;
  
  int *end_points, index;
  EDGE_LIST *ptr;
  
  candidates = im_struct.candidates;
   
  end_points = (int*)malloc(sizeof(int) * num_end_points);
  ptr = contour_ptr;
  index = 0;
  while(index < num_end_points && ptr != NULL)
    {
      if(candidates[ptr->n] == EndPoint)
	{
	  end_points[index] = ptr->n;
	  ++index;
	}
      ptr = ptr->next;
    }
  if(index == 0)
    return(NULL);
  else
    return(end_points);
}
