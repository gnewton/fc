#include "stuff.h"
#include "search.h"
#include <suntool/sunview.h>
#include <suntool/canvas.h>
#include <suntool/panel.h>

sv_show(start_ptr)
SEGMENTS_LIST *start_ptr;
{
  extern  Pixwin *pw;
  extern Pixrect *pr;
  extern IMAGE im_struct;
  extern Panel_item imvalue_item;
  
  extern int NumberOfSearchNodes;
  
  EDGE_LIST *ptr;
  int x,y,width,height;
  char *str[12];
  
  width = im_struct.width;
  height = im_struct.height;
  
  sprintf(str,"%d",NumberOfSearchNodes);
  panel_set(imvalue_item, PANEL_LABEL_STRING, str,0);
  

  ptr = start_ptr->contour_ptr;
  
  while(ptr != NULL)
    {
      y = ptr->n/width;
      x = ptr->n - y*width;
      pw_put(pw, x, y, RED);
      pr_put(pr,x,y,RED);
      
      ptr = ptr->next;
    }
}      
