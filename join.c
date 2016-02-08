
#include "stuff.h"

join(contour_list_ptr, new_contour_list_ptr, search_list)
	SEGMENTS_LIST *contour_list_ptr, *new_contour_list_ptr;
	EDGE_LIST **search_list;

{
  extern IMAGE im_struct;
  
  short *candidates;
  
  EDGE_LIST *last_search_ptr, *last_new_contour_ptr, *tmp;
  

  candidates = im_struct.candidates;
  
  last_search_ptr = *search_list;

  candidates[last_search_ptr->n] = contour_list_ptr->list_id;
  while(last_search_ptr->next != NULL)
    {

      last_search_ptr = last_search_ptr->next;
      candidates[last_search_ptr->n] = contour_list_ptr->list_id;
    }
  
  last_new_contour_ptr = new_contour_list_ptr->contour_ptr;
  while(last_new_contour_ptr->next != NULL)
    {
      if(candidates[last_new_contour_ptr->n] <= ListIdStart)
	candidates[last_new_contour_ptr->n] = contour_list_ptr->list_id;
      last_new_contour_ptr = last_new_contour_ptr->next;
    }  
  tmp = contour_list_ptr->contour_ptr;
  
  last_search_ptr->next = tmp;
  
  last_new_contour_ptr->next = *search_list;
  contour_list_ptr->contour_ptr = new_contour_list_ptr->contour_ptr;
}
