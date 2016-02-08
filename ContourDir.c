#include "stuff.h"
int ContourDir(list_list_ptr)
SEGMENTS_LIST *list_list_ptr;
 

{
  extern IMAGE im_struct;
  
  extern  int XCheck, YCheck;

  EDGE_LIST *ptr;
  
  int x,y,
  dx,dy,
  xmin = 50000, 
  xmax = -1,
  ymin = 50000, 
  ymax = -1;
  
  ptr = list_list_ptr->contour_ptr;
  while(ptr != NULL)
    {
      y = ptr->n/im_struct.width;
      x = ptr->n - y*im_struct.width;
  /*    printf("\n n=%d x=%d y=%d xs=%d ys=%d",ptr->n,x,y,im_struct.width,im_struct.height);*/
      if(y < ymin)  ymin = y;
      if(y > ymax)  ymax = y;
      if(x > xmax)  xmax = x;
      if(x < xmin) xmin = x;
      ptr = ptr->next;
    }
  dx = xmax - xmin;
/*  printf("\n ***********************  dx = %d, dy = %d",dx,ymax-ymin);*/
  
  if(dx > XCheck) return(FALSE);
  dy = ymax - ymin;
  if(dy > YCheck) return(FALSE);
  
  return(TRUE);
}


  
  

  
