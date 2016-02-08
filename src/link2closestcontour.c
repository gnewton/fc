#include "stuff.h"
#include "search.h"
#include <suntool/sunview.h>
#include <suntool/canvas.h>

int Link2ClosestContour(head, start_ptr, pass, strategy)
SEGMENTS_LIST **head, *start_ptr;
{
  extern IMAGE im_struct;
  extern int Debug, SunView;
  extern Pixwin *pw;
  extern Pixrect *pr;
  
  int *search_direction, start, *goal, 
  i, status,
  search_depth,
  max_end_point_distance,
  min_edge_strength,
  min_end_point_contour_length,
  num_goal_points,
  searched,
  Search2goal(), debug(),
  *correct_directions(), *FindClosestEndPoints();
  
  PTR_LIST *end_points_ptr, *t;
  
  int who = RUSAGE_SELF;
  struct rusage *rusage;
  
  
  /* malloc_debug(2) */;
  if(Debug)
    debug("link2closestcontour");
  
  
  
  switch(pass)
    {
    case Pass1:
      /* Set up variables for the Search Passes */
      /* Pass 1 */
      max_end_point_distance = 4;
      search_depth = 4;
      min_edge_strength = 35;
      min_end_point_contour_length = 6;
      num_goal_points = 1;
      searched = pass;
      break;
      
    case Pass2:
      /* Pass 2 */
      max_end_point_distance = 15;
      search_depth = 17;
      min_edge_strength = 45;
      min_end_point_contour_length = 0;
      num_goal_points = 2;
      searched = pass;
      break;
    }
  
    end_points_ptr = start_ptr->end_points_list;
  
  /* Run through the end_points of the starting contour */  
  while(end_points_ptr!= NULL)
    {
      if(end_points_ptr->search_status != searched)
	{
	  end_points_ptr->search_status = searched;
	  search_direction = correct_directions(end_points_ptr, 1);
	  start = end_points_ptr->pointer->n;
	  
	  goal = FindClosestEndPoints(head, start, start_ptr->list_id, num_goal_points,   
				      max_end_point_distance, min_end_point_contour_length );
	  
	  for(i=0;i<num_goal_points; ++i)
	    {
	      if(goal[i] != NoCloseEndPoint)
		{
		  fprintf(stderr, "\nlistid = %d  i=%d  start=%d  goal=%d ",start_ptr->list_id, i, start, goal[i]);
		  
		  if((status = Search2Goal(head, start, goal[i], start_ptr, search_direction[0], 
					   search_depth, min_edge_strength, strategy)) == FoundGoal)
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
  start_ptr->Search_status = searched;
  
  
}










