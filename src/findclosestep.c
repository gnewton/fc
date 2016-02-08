#include "stuff.h"
#include "search.h"

int *FindClosestEndPoints(head,start, start_id, number, max_ep_distance, min_ep_contour_length)
SEGMENTS_LIST **head, *start_id;
int start, number,max_ep_distance, min_ep_contour_length;

{
  extern IMAGE im_struct;
  extern int Debug;
  
  SEGMENTS_LIST *headptr;
  
  int width = im_struct.width,
  i, distance, goal, j,
  *endpoints, *epdistance,
  Xa,Ya,Xb,Yb;
  
  /* ep_list (start_ptr->end_points_olist) points to a list of pointers which 
     points to the members of the contour_ptr list which are endpoints        */
  PTR_LIST *ep_list;
  
  
  max_ep_distance *= max_ep_distance;
  
  /* ep - contains the found endpoints and their distance in an array, in the order */
  /*      distance,point,distance,point.......                                      */
  endpoints = (int*)malloc(sizeof(int)*number);
  epdistance = (int*)malloc(sizeof(int)*number);
  
  for(i=0;i<number; ++i) 
    {
      endpoints[i] = NoCloseEndPoint;
      epdistance[i] = VeryLargeNumber;
    }
  
  
  Ya = start/width;
  Xa = start - Ya*width;
  
  headptr = *head;
  
  /* go through the contour lists */
  while(headptr != NULL)
    {
      if(headptr->num_list_points > min_ep_contour_length)
	{

	  ep_list = headptr->end_points_list;
	  while(ep_list != NULL)
	    {  
	      goal = ep_list->pointer->n;
	      if(goal != start)
		{
		  Yb = goal/width;
		  Xb = goal - Yb*width;
		  /*printf("\n Xa=%d Ya=%d Xb=%d Yb=%d",Xa,Ya,Xb,Yb);	  */
		  Xb = Xa-Xb;
		  Yb = Ya-Yb;
		  distance = Xb*Xb + Yb*Yb;
		  
		  if(headptr->list_id == start_id && distance < 20)
		    distance = 0;
		  
		  if(distance<max_ep_distance)
		    {
		      /*max_ep_distance = distance;*/
		      for(i=0; i<number; ++i)
			{
			  if(distance < epdistance[i])
			    {
			      j = goal;
			      goal = endpoints[i];
			      endpoints[i] = j;
			      j = distance;
			      distance = epdistance[i];
			      epdistance[i] = j;
			    } /* end if */

			} /* end for */

		    } /* end if */

		} /* end if */

	      ep_list = ep_list->next;
	    } /* end while */
	}  /* end if */

      headptr = headptr->next_contour;
    } /* end while */
  /* if there is no point within the minumal distance   */
  
  if(Debug == 9)
    printf("\n start=%d  goal=%d",start,endpoints[0]);
  
  return(endpoints);
}



