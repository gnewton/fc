

#include "stuff.h"

int RemoveFromEndPointList(goal, goal_contour)
int goal;
SEGMENTS_LIST *goal_contour;
{
  PTR_LIST *ptr;

  
  ptr = goal_contour->end_points_list;
  if(ptr->pointer->n == goal)
    goal_contour->end_points_list = goal_contour->end_points_list->next;
  else
    {
      while(ptr != NULL && ptr->next != NULL)
	{
	  if(ptr->next->pointer->n != goal)
	    ptr = ptr->next;
	  else
	    {
	      ptr->next = ptr->next->next;
	      break;
	    }
	}
    }
  
}

