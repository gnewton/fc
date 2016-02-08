#define Space 7

#include "stuff.h"


test(head_list_ptr)
	SEGMENTS_LIST *head_list_ptr;


{
  extern IMAGE im_struct;
  

  short *candidates;
  
  SEGMENTS_LIST *ptr;
  EDGE_LIST *contour_ptr;
  int i;
  

  candidates = im_struct.candidates;
  
  ptr = head_list_ptr;
  while(ptr != NULL)
    {
      print_head_ptr(ptr);
      contour_ptr = ptr->contour_ptr;
      i = 0;
      
      while(contour_ptr != NULL)
	{
	  if((i%Space) == 0)
	    printf("\n");
	  printf("[%d %d]",contour_ptr->n,candidates[contour_ptr->n]);
	  ++i;
	  contour_ptr = contour_ptr->next;
	}
      ptr = ptr->next_contour;
    }
}
