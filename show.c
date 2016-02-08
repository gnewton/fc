#include "stuff.h"

int show(head,Flag)
SEGMENTS_LIST *head;
int Flag;

{
  SEGMENTS_LIST *ptr;
  EDGE_LIST *eptr;
  PTR_LIST *pptr;
  
  ptr = head;
  
  printf("\n id=%d num=%d ep=%d sp=%d \n", ptr->list_id, ptr->num_list_points, ptr->num_end_points,
	 ptr->num_split_points);
  

  switch(Flag)
    {
      case(0):
	{
	  eptr = ptr->contour_ptr;
	  while(eptr != NULL)
	    {
	      printf("[%d] ",eptr->n);
	      eptr = eptr->next;
	    }
	}
      case(1):
	{
	  pptr = ptr->end_points_list;
	  while(pptr != NULL)
	    {
	      printf("(%d)",pptr->pointer->n);
	      pptr = pptr->next;
	    }
	}
      break;
    }
}

  
