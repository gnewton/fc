
#include "stuff.h"
#include "search.h"


int JoinLists(head, start_ptr, start, end_node)
SEGMENTS_LIST **head, *start_ptr;
int start;
TREE *end_node;

{
  extern IMAGE im_struct;
  extern int Debug;
    
  int goal, path_length, *new_start_point,
  RemoveFromEndPointsList(),
  DeleteFormContourList();
  
  /* new start point has tobe reconciled (gotten rid of?)          */
    
  EDGE_LIST *tmp, *search_list;
    
  SEGMENTS_LIST *goal_contour,*FindContourPtr();
  
  PTR_LIST *ptr;
  
  short *candidates;
  
  candidates = im_struct.candidates;
  
  goal = end_node->point;
  goal_contour = FindContourPtr(goal, start_ptr, head);
  
  if(Debug == 2)
    {
      printf("\n\n **join  start=%d goal=%d goalcontourptr=%d",start,goal,goal_contour);
      printf("\n %d ", goal_contour->list_id);
    }
  
  
  if(Debug == 5)
    {
      printf("\n\n\n Joining %d to %d",start_ptr->list_id,goal_contour->list_id);
      printf("\n   start :");
      ptr = start_ptr->end_points_list;
      while(ptr!= NULL)
	{
	  printf(" %d", ptr->pointer->n);
	  ptr = ptr->next;
	}
      
      printf("\n   goal :");
      ptr = goal_contour->end_points_list;
      while(ptr!= NULL)
	{
	  printf(" %d", ptr->pointer->n);
	  ptr = ptr->next;
	}
    }
  
  
  


  candidates[start] = start_ptr->list_id;

  /* get searched path    */
  path_length = 0;
  /* move up once in the tree, as the last node in the tree is the goal ep */
  end_node = end_node->parent;
  /*search_list = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));*/

  /* point end of search list to goal list, unless joining to the same list   */
  if(goal_contour == start_ptr)
    search_list = NULL;
  else
    search_list = goal_contour->contour_ptr;

  while(end_node->parent != NULL)
    {
      ++path_length;
      tmp = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
      tmp->n = end_node->point;
      candidates[tmp->n] = start_ptr->list_id;
      tmp->next = search_list;
      search_list = tmp;
      end_node = end_node->parent;
    }
  RemoveFromEndPointList(start, start_ptr);
  
  /* go through goal list, and set ordinary points (ie not split or end points) to start_list_id 
  tmp = goal_contour->contour_ptr;
  while(tmp != NULL)
    {
      if(candidates[tmp->n] <= ListIdStart)
	candidates[tmp->n] = start_ptr->list_id;
      tmp = tmp->next;
    }
  */

  /* go through start list until end, then attach to search/goal list */
  tmp = start_ptr->contour_ptr;
  while(tmp->next != NULL)
    tmp = tmp->next;
  tmp ->next = search_list;
  
  start_ptr->num_list_points += path_length;

  /* if joining different contours together     */
  if(start_ptr != goal_contour)
    {
      /* go through goal list, and set ordinary points (ie not split or end points) to start_list_id */
      tmp = goal_contour->contour_ptr;
      while(tmp != NULL)
	{
	  if(candidates[tmp->n] <= ListIdStart)
	    candidates[tmp->n] = start_ptr->list_id;
	  tmp = tmp->next;
	}
      
      /* attach goal end points list to start_ptr's   */
      /* note: goal list ep's are put on top of start_ptr`s....
	 this is so the search continues in the same direction
	 it may be inneretin to reverse this          */
      ptr = goal_contour->end_points_list;
      if(ptr != NULL)
	{
	  while(ptr->next != NULL)
	    ptr = ptr->next;
	  ptr->next = start_ptr->end_points_list;
	  start_ptr->end_points_list = goal_contour->end_points_list;
	}
      
      start_ptr->num_list_points += goal_contour->num_list_points;
      if(goal_contour->num_list_points != 1)
	{
	  candidates[goal] = start_ptr->list_id;
	  RemoveFromEndPointList(goal, start_ptr);
	  start_ptr->num_split_points += goal_contour->num_split_points;
	  start_ptr->num_end_points += goal_contour->num_end_points - 2;
	}	  
      DeleteFromContourList(head, goal_contour);
    }
  else
    {
      candidates[goal] = start_ptr->list_id;
      if(goal_contour->num_list_points != 1)
	{
	  RemoveFromEndPointList(goal, start_ptr);
	  start_ptr->num_end_points -= 2;
	}
      else
	start_ptr->num_end_points -= 1;
    }
  if(Debug == 5)
    {

      ptr = start_ptr->end_points_list;
      printf("\n   *start :");
      while(ptr!= NULL)
	{

	  printf(" %d", ptr->pointer->n);
	  ptr = ptr->next;
	}
    }
}

