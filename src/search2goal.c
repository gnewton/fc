
/* Search2goal from start point to goal NOT recursively,
   but by building a tree of the search path and keeping a list of
   the leaves points                                              */




#include "stuff.h"
#include "search.h"
#include <math.h>
#include <suntool/sunview.h>
#include <suntool/canvas.h>
#include <suntool/panel.h>

#define Search TRUE

extern NumberOfSearchNodes;



int Search2Goal(head, start, goal, start_ptr, search_direction, search_depth, min_edge_strength, strategy)
SEGMENTS_LIST **head, *start_ptr;
int start, goal, search_direction, search_depth, min_edge_strength, strategy;
{
  extern IMAGE im_struct;
  extern int Debug, TraceFlag, TraceColour, SunView, LeftButtonDown;
  extern byte *Trace;
  extern Pixwin *pw;
  extern Pixrect *pr;
  extern Panel_item imvalue_item;

  
  
  TREE *node, *leaves_list, *last, *ptr, *leavesptr,*searched_points_list, *newnode, *lastp, *lastf, *parent;
  

  Event *event;
  
  NEXTPOINT next_points[NumSearchPoints];
  

  

  int  search_status=Search, min_depth,
  cost, i,j, path_depth, width, min_goal_distance,
  xa,ya,xb,yb,
  AlreadyOnLeaves,
  FindNextPoints(),
  JoinLists();

  char *str[12];  
  
  short *edge_mag,
  *candidates;
  
  int who = RUSAGE_SELF;
  struct rusage *rusage;

  

  if(SunView)
    sv_show(start_ptr);
  
      
  if(Debug)
    debug("Search2goal");
  
  edge_mag = im_struct.edge_mag;
  candidates = im_struct.candidates;
  width = im_struct.width;


  
  node = NULL;
  
  node = (TREE*)malloc(sizeof(TREE));
  node->point = start;
  node->parent = NULL;
  for(j=0; j< NumSearchPoints; ++j)
    node->next[j] = NULL;
  
  node->leaves = NULL;
  node->path_length = 0;
  node->path_arc_cost = 0;
  node->direction = 0;
  node->depth = 0;
  
  SQDIST(goal,node->point,node->goal_distance);
  
  path_depth = 0;
  
  leaves_list = node;
  searched_points_list = NULL;
  
  while(search_status == Search)
    {
      if(leaves_list == NULL)
	search_status = StopSearch;
      else
	{
	  /*REMOVE_FROM_FRINGE;*/
	  
	  /* show the nodes searched in output */
	  if(TraceFlag)
	    Trace[node->point] = 255;/*TraceColour-4;*/
	  
	  
	  /* remove node from leaves list */
	  RemoveFromLeavesList(leaves_list, node);
	  if(node->parent != NULL)
	    AddToSearchedList(searched_points_list,node);
	  
	  
	  if(node->path_length < search_depth)
	    
	    {
	      
	      /* find next points, and add to tree list and leaves_list list */
	      FindNextPoints(next_points, node->point, search_direction, min_edge_strength);
	      
	      if(Debug == 12)
		printf("\n node = %d   | ",node->point);
	      
	      for(i=NumSearchPoints-1; i>=0; --i)
		{
		  if(next_points[i].point != BadPoint)
 		    {
		      /* Check if point already on leaves list */
		      AlreadyOnLeaves = FALSE;
		      leavesptr = leaves_list;
		      while(leavesptr != NULL)
			{
			  if(next_points[i].point == leavesptr->point)
			    {
			      AlreadyOnLeaves = TRUE;
			      break;
			    }
			  leavesptr = leavesptr->leaves;
			}

		      /* */
		      if(!AlreadyOnLeaves /* && (candidates[next_points[i].point] != AlreadySearched)*/)
			{
			  if(Debug == 12)
			    printf("%d ",next_points[i].point);

			  if(SunView)
			    {
			      sprintf(str,"%d",NumberOfSearchNodes);
			      panel_set(imvalue_item, PANEL_LABEL_STRING, str,0);
			    }
			  
			  newnode = (TREE*)malloc(sizeof(TREE));		      
			  newnode->point = next_points[i].point;
			  newnode->parent = node;
			  newnode->depth = node->depth + 1;
			  
			  newnode->path_length = node->path_length + next_points[i].distance;
			  newnode->path_arc_cost = node->path_arc_cost + 1024 - edge_mag[next_points[i].point];
			  newnode->direction = i; /* the direction Front, Left, Right LLeft, RRight */

			  switch(i)
			    {
			    case Front:
			    case RRight:
			    case LLeft:
			      newnode->node_distance = 2;
			      break;
			    case Left:
			    case Right:
			      newnode->node_distance = 3;
			    }
			  for(j=0; j< NumSearchPoints; ++j)
			    newnode->next[j] = NULL;
			  
			  /*SQDIST(goal,newnode->point,newnode->goal_distance);*/
			  ya = goal/width;
			  xa = goal - ya*width;
			  yb = newnode->point/width;
			  xb = newnode->point - yb*width;
			  if(SunView)
			    {
			      pw_put(pw, xb, yb, GREEN);
			      ++NumberOfSearchNodes;
			    }
			  
			  xb = xa-xb;
			  yb = ya-yb;
			  newnode->goal_distance =(int)sqrt((float)(xb*xb + yb*yb));
			  newnode->leaves = leaves_list;
			  node->next[i] = newnode;
			  leaves_list = newnode;

			  
			}
		      
		    }
		}
	    }	      
	  /* find "best" next point (branch-and-bound)              */
	  /* - the very best is the goal point, but otherwise       */
	  /*   take the point with lowest cost                      */
	  /* - because' edge strengths are being used, the lowest    */
	  /*   cost is actually the highest cost.                   */
	  
	  leavesptr = leaves_list;
	  
	  min_goal_distance = cost = VeryLargeNumber;
	  min_depth = 99999;
	  
	  while(leavesptr != NULL && search_status != FoundGoal)
	    {
	      if(leavesptr->point == goal /*|| candidates[leavesptr->point] == EndPoint*/)
		{
		  search_status = FoundGoal;
		  JoinLists(head, start_ptr, start, leavesptr);
		  if(SunView)
		    {
		      /*getchar();*/
		      sv_show(start_ptr);
		    }
		  break;
		}
	      else
		{
		  switch(strategy)
		    {
		    case DepthFirst:
		      /* Take node from top of the leaves stack         */
		      /*      NO HEURISTIC - takes next node from the   */
		      /*      top of the leaves_list                   */
		      fprintf(stderr,"\n Depth \n");
		      node = leavesptr;
		      leavesptr = NULL;
		      break;
		      
		    case BreadthFirst:
		      /* Take node with */
		      fprintf(stderr,"\n depth = %d *************",min_depth);
		      if(leavesptr->depth < min_depth)
			{
			  fprintf(stderr, "\n depth = %d ",min_depth);
			  
			  node = leavesptr;
			  min_depth = leavesptr->depth;
			}
		      leavesptr = leavesptr->leaves;
		      break;
		      
		      
		      
		    case BranchAndBound:
		      /* Find best global point (search ALL of leaves)  */
		      /*     using ARC COST, g(n), as heuristic         */
		      /*     depth-first                                */

		      if(leavesptr == leavesptr->leaves)
			{
			  leavesptr = NULL;
			  break;
			}
		      if(leavesptr->path_arc_cost < cost)
			{
			  cost = leavesptr->path_arc_cost;
			  node = leavesptr;
			}
		      leavesptr = leavesptr->leaves;
		      break;
		      
		    case AveragePathCost:
		      if(leavesptr->path_arc_cost*leavesptr->path_length <cost)
			{
			  cost = leavesptr->path_arc_cost*leavesptr->path_length;
			  node = leavesptr;
			}
		      leavesptr = leavesptr->leaves;
		      break;


		    case BestFirst:
		      /* Find best GLOBAL point (search ALL of leaves)  */
		      /*      using GOAL DISTANCE,  h(n), as heuristic  */

		      if(leavesptr->goal_distance < min_goal_distance)
			{
			  min_goal_distance = leavesptr->goal_distance;
			  node = leavesptr;
			}
		      leavesptr = leavesptr->leaves;
		      break;


		    case AStar:
		      /* Find best GLOBAL point (search ALL of leaves)  */
		      /*      using both ARC_COST, g(n), and GOAL_DISTANCE, h(n), as heuristic.   */

		      if(leavesptr->path_arc_cost + leavesptr->goal_distance*(1024-edge_mag[leavesptr->point]) < cost)
			{
			  cost = leavesptr->path_arc_cost + leavesptr->goal_distance*(1024-edge_mag[leavesptr->point]);
			  node = leavesptr;
			}
		      leavesptr = leavesptr->leaves;
		      break;
		    }
		}
	    }
	}
    }
  




  while(searched_points_list != NULL)
    {
      candidates[searched_points_list->point] = Non_Edge;
      searched_points_list = searched_points_list->leaves;
    }
  
  
  /* Free up pointers                */

  while(leaves_list != NULL)
    {
      lastf = leaves_list;
      parent = leaves_list->parent;
      while(parent != NULL)
	{
	  lastp = parent;
	  parent = parent->parent;
	  free(lastp);
	}
      leaves_list = leaves_list->leaves;
      free(lastf);
    }
  
  return(search_status);
  
}
