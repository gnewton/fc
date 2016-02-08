#include "stuff.h"
 
 
int AddToSearchList(point, search_list)
int point;
EDGE_LIST **search_list;
{
  EDGE_LIST *tmp;
  

  tmp = (EDGE_LIST*)malloc(sizeof(EDGE_LIST));
  tmp->n = point;
  tmp->next = *search_list;
  *search_list = tmp;
/*  free(tmp);*/
}
