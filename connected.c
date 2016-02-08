 
#include "stuff.h"

SEGMENTS_LIST *connected(strong_edges)
EDGE_LIST **strong_edges;
{
  extern  IMAGE im_struct;
    
  SEGMENTS_LIST *strong_list, *new_list;

  PTR_LIST *end_points_list, *ep;  /* a list of pointers to the end points in the contour_list  */
  
  EDGE_LIST *list_ptr,
  *tmp, 
  *next_pix,
  *neigh_list, 
  *ptr, 
  *list, 
  *find_neighbours();
  
  int number_of_points, 
  number_of_neighbours, 
  num_end_points, 
  num_split_points,
  list_id,
  width,
  Id_Flag;

  short *candidates, *edge_mag ;
  byte *edge_dir;
  
  
  candidates = im_struct.candidates;
  edge_mag = im_struct.edge_mag;
  edge_dir = im_struct.edge_dir;
  width = im_struct.width;
  
  
  list_id = ListIdStart;
  
  strong_list = NULL;
  tmp = *strong_edges;
  while(tmp != NULL)
    {
      switch(edge_dir[tmp->n])
	{
	  case(0):
	  case(8):
	    {
	      edge_mag[tmp->n - width] = (int) (0.75 * edge_mag[tmp->n - width]);
	      edge_mag[tmp->n + width] =  (int) (0.75 * edge_mag[tmp->n + width]);
	    }
	  case(1):
          case(7):
	    {
	      edge_mag[tmp->n - width -1] = (int) (0.75 * edge_mag[tmp->n - width -1]);
	      edge_mag[tmp->n + width + 1] =  (int) (0.75 * edge_mag[tmp->n + width + 1]);
	    }
	  case(2):
          case(6):
	    {
	      edge_mag[tmp->n  -1] = (int) (0.75 * edge_mag[tmp->n  -1]);
	      edge_mag[tmp->n  + 1] =  (int) (0.75 * edge_mag[tmp->n  + 1]);
	    }
	  case(3):
          case(5):
	    {
	      edge_mag[tmp->n - width +1] = (int) (0.75 * edge_mag[tmp->n - width +1]);
	      edge_mag[tmp->n + width - 1] =  (int) (0.75 * edge_mag[tmp->n + width - 1]);
	    }
	}
      
	  Id_Flag = FALSE;
      neigh_list = NULL;
      ptr = NULL;
      list_ptr = NULL;
      end_points_list = NULL;

      next_pix = tmp->next;
      if(candidates[tmp->n] == StrongEdge)
	{
	  /*
	  ptr = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
	  ptr->n = tmp->n;
	  */
	  ptr = tmp;
	  ptr->next = list_ptr;
	  number_of_points = 1;
	  num_end_points = 0;
	  num_split_points = 0;
	  
	  list_ptr = ptr;
	  candidates[ptr->n] = list_id;
	  
	  neigh_list = find_neighbours( neigh_list,&number_of_neighbours,
				       ptr->n);
	  
	  if(candidates[ptr->n] == EndPoint)
	    {
	      ep = (PTR_LIST*)malloc(sizeof(PTR_LIST));
	      ep->pointer = list_ptr;
	      ep->next = end_points_list;
	      ep->search_status = Unsearched;
	      end_points_list = ep;
	      ++num_end_points;
	    }
	  
	  else
	    if(candidates[ptr->n] == SplitPoint)
	      ++num_split_points;
	    else
	      Id_Flag = TRUE;
	      
	  
	  while(neigh_list != NULL)
	    {
	      ++number_of_points;
	      ptr = neigh_list;
	      neigh_list = neigh_list->next;
	      ptr->next = list_ptr;
	      list_ptr = ptr;
	      candidates[ptr->n] = list_id;
	      neigh_list = find_neighbours(neigh_list,&number_of_neighbours,
					   list_ptr->n);
	      
	      if(candidates[list_ptr->n] == EndPoint)
		{
		  ep = (PTR_LIST*)malloc(sizeof(PTR_LIST));
		  ep->pointer = list_ptr;
		  ep->next = end_points_list;
		  ep->search_status = Unsearched;
		  end_points_list = ep;
		  ++num_end_points;
		}
	      
	      
	      if(candidates[list_ptr->n] == SplitPoint)
		++num_split_points;
	      else
		  Id_Flag = TRUE;
	    }
	  
	  new_list = (SEGMENTS_LIST*)malloc(sizeof(SEGMENTS_LIST));
	  
	  new_list->contour_ptr = list_ptr;
	  
	  new_list->num_list_points = number_of_points;
	  new_list->num_end_points = num_end_points;
	  new_list->end_points_list = end_points_list;
	  new_list->num_split_points = num_split_points;
	  
	  if(Id_Flag == TRUE)
	    {
	      
	      new_list->list_id = list_id;
	      --list_id;
	    }
	  else
	    new_list->list_id = Special_Case_Id;
	  
	  new_list->Search_status = Unsearched;
	  
	  new_list->next_contour = strong_list;
	  
	  strong_list = new_list;
	  list = NULL;
	}
      tmp = next_pix;
    }
  return(strong_list);
  
}

