#include "stuff.h"
#include "search.h"
#include <suntool/sunview.h>
#include <suntool/canvas.h>

int Link2ClosestContour(head, start_ptr)
SEGMENTS_LIST **head, *start_ptr;
{
  extern IMAGE im_struct;
  extern int Debug, SunView;
  extern Pixwin *pw;
  extern Pixrect *pr;
  
  int *search_direction, start, *goal, search_depth, min_edge_strength, max_end_point_distance,
  i, status,
  debug(),
  Search2goal(),
  *correct_directions(), *FindClosestEndPoints();

  PTR_LIST *end_points_ptr, *t;
  
  
  int who = RUSAGE_SELF;
  struct rusage *rusage;
  
  
  /* malloc_debug(2) */;
  if(Debug)
    debug("link2closestcontour");
    
  end_points_ptr = start_ptr->end_points_list;
  max_end_point_distance = 4;
  search_depth = (int)((float)max_end_point_distance * 1.6);	  


  min_edge_strength = 80;

  

  /* Run through the end_points of the startng contour */  
  while(end_points_ptr!= NULL)
    {
       if(end_points_ptr->search_status == Unsearched)
	{
	  end_points_ptr->search_status = Searched;
	  search_direction = correct_directions(end_points_ptr, 1);
	  start = end_points_ptr->pointer->n;
      
	  goal = FindClosestEndPoints(head, start, start_ptr->list_id, NumGoalPoints,   max_end_point_distance );

	  if(start_ptr->list_id == -9)
	    {
	      t = start_ptr->end_points_list;
	      fprintf(stderr, "\n\n Listid=%d numeps=%d", start_ptr->list_id, start_ptr->num_end_points);

	      while(t!= NULL)
		{
		  fprintf(stderr, "\n endpoint=%d",t->pointer->n);
		  t = t->next;
		}
	    }
	  

	  for(i=0;i<NumGoalPoints; ++i)
	    {
	      if(goal[i] != NoCloseEndPoint)
		{
		  fprintf(stderr, "\nlistid = %d  i=%d  start=%d  goal=%d ",start_ptr->list_id, i, start, goal[i]);
		  
		  if((status = Search2Goal(head, start, goal[i], start_ptr, search_direction[0], 
					   search_depth, min_edge_strength)) == FoundGoal)
		    {
		      end_points_ptr = start_ptr->end_points_list;
		      break;
		    }
		}
	    }
	  if(status != FoundGoal)
	    end_points_ptr = end_points_ptr->next;
	}
      else
	end_points_ptr=end_points_ptr->next;
    }
  start_ptr->Search_status = Searched;
}

