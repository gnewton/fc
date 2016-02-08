
#include "stuff.h"
#include "search.h"
#include <strings.h>
#include <stdio.h>
#include <suntool/sunview.h>
#include <suntool/canvas.h>
#include <suntool/panel.h>
#include <suntool/textsw.h>
#include <suntool/alert.h>

#define CMAP_SIZE 256
#define IM_MAP_SIZE 4
#define FRAME_WIDTH 1024
#define FRAME_HEIGHT 768
#define CMS_SIZE 4
#define CMS_START 0

#define MIN_WINDOW_WIDTH 300
#define FRAME_LABEL_HEIGHT 22
#define PANEL_HEIGHT 52
#define BUTTONFONT "/usr/lib/fonts/fixedwidthfonts/sail.r.6.i386"

Frame frame, panel, histogram_frame, histogram_panel, save_frame, save_panel;

Canvas canvas;
Cursor cursor;


Panel_item imvalue_item, x_item, y_item,
  imvalue_label_item,x_label_item,y_label_item,
  fname_item;
Pixwin *pw;
Pixfont *bf;

Pixrect *pr;
char *frame_label="fcView";

static void continue_extend_proc(),extend_proc(), set_search_strategy(),
  mag_proc(),
  crop_proc(),
  save_popup_proc(),
  save_proc();

void canvas_event_proc();
int Crop = FALSE,
  LeftButtonDown = FALSE,
  cx0,cy0,cx1,cy1;

int NumberOfSearchNodes = 0;


SEGMENTS_LIST **Head;

int strat = DepthFirst;



int View_extend_lines(head_contour_list_ptr, strategy)
SEGMENTS_LIST **head_contour_list_ptr;
int strategy;

{
  extern IMAGE im_struct;
  
  SEGMENTS_LIST *head;
  EDGE_LIST *contour_ptr;
  
  Rect *r;
  u_char red[CMS_SIZE],
  green[CMS_SIZE],
  blue[CMS_SIZE];
   
  int x,y,p,i,
  width,height,
  win_width, win_height,
  image_width,image_height;


  
  Head = head_contour_list_ptr;
  
  bf = pf_open(BUTTONFONT);
  width = im_struct.width;
  height = im_struct.height;
  
  if(width<MIN_WINDOW_WIDTH)
    win_width  = MIN_WINDOW_WIDTH;
  
  
  win_width = (width<MIN_WINDOW_WIDTH) ? MIN_WINDOW_WIDTH : width;
  
  
  
  win_height=(height > FRAME_HEIGHT) ? FRAME_HEIGHT : height ;
  
  win_width = (win_width > FRAME_WIDTH) ? FRAME_WIDTH : win_width ;
  
  
  if(win_width<MIN_WINDOW_WIDTH)
    win_width  = MIN_WINDOW_WIDTH;
  
  
  /* create canvas and frame*/
  
  cx0 = cy0 = 0;
  cx1 = width;
  cy1 = height;
  
  frame = window_create(NULL, FRAME,
			FRAME_LABEL, frame_label,
			FRAME_NO_CONFIRM, TRUE,
			WIN_HEIGHT, win_height + FRAME_LABEL_HEIGHT +
			PANEL_HEIGHT ,
			WIN_WIDTH, win_width + 9,
			0);
  
  panel = window_create(frame, PANEL,0);
  create_panel_items();
  
  if(win_height == height && 
     (win_width == width || win_width==MIN_WINDOW_WIDTH))
    canvas = window_create(frame, CANVAS,
			   CANVAS_AUTO_SHRINK,  TRUE,
			   CANVAS_AUTO_EXPAND, TRUE,
			   CANVAS_FIXED_IMAGE,  FALSE,
			   WIN_CONSUME_PICK_EVENT, LOC_DRAG,
			   CANVAS_WIDTH, width,
			   CANVAS_HEIGHT, height,
			   WIN_EVENT_PROC,canvas_event_proc,
			   0);
  else 
    canvas = window_create(frame, CANVAS,
                           CANVAS_AUTO_SHRINK,TRUE,
                           CANVAS_AUTO_EXPAND, TRUE,
		           CANVAS_FIXED_IMAGE,	FALSE,
			   CANVAS_WIDTH, width,
			   CANVAS_HEIGHT, height,
			   WIN_VERTICAL_SCROLLBAR, scrollbar_create(0),
                           WIN_HORIZONTAL_SCROLLBAR, scrollbar_create(0),	
			   0);
  
  /*    window_fit(frame);*/
  
  pw = canvas_pixwin(canvas);
  
  for(i=CMS_START; i < IM_MAP_SIZE; i++)
    {
      red[i]=blue[i]=green[i]=(i-CMS_START)*(CMAP_SIZE/IM_MAP_SIZE);
    }
  
  red[BACKGROUND] = 255;
  blue[BACKGROUND] = 255;
  green[BACKGROUND] = 255;
    
  red[FOREGROUND] = 0;
  blue[FOREGROUND] = 0;
  green[FOREGROUND] = 0;
  
  red[RED] = 255;
  blue[RED] = 10;
  green[RED] = 0;
  
  red[GREEN] = 5;
  blue[GREEN] = 25;
  green[GREEN] =222;
  

  pw_setcmsname(pw, "fc");
  pw_putcolormap(pw, CMS_START, CMS_START + CMS_SIZE , red, green, blue);
  
  cursor = window_get(canvas,WIN_CURSOR);
  cursor_set(cursor, 
	     CURSOR_OP, PIX_DST^PIX_SRC,0);
  window_set(canvas,WIN_CURSOR, cursor, 0);
  
  
  
  pr = mem_create(width,height,8);
  
  
  head = *head_contour_list_ptr;
  while(head != NULL)
    {
      contour_ptr = head->contour_ptr;
      while(contour_ptr != NULL)
	{	   
	  y = contour_ptr->n/width;
	  x = contour_ptr->n - y*width;
	  pw_put(pw, x, y, FOREGROUND); 
	  contour_ptr = contour_ptr->next;
	}
      head = head->next_contour;
    }
  
  window_main_loop(frame);
  exit(0);
}



create_panel_items()
{
  panel_create_item(panel,PANEL_MESSAGE,
		    PANEL_LABEL_X, ATTR_COL(0),
		    PANEL_LABEL_Y, ATTR_COL(0),
		    PANEL_LABEL_STRING, "n",
		    0);
  
  x_item = panel_create_item(panel, PANEL_MESSAGE,
			     PANEL_LABEL_X, ATTR_COL(2),
			     PANEL_LABEL_Y,ATTR_COL(0),
			     0);
  
  panel_create_item(panel,PANEL_MESSAGE,
		    PANEL_LABEL_X, ATTR_COL(6),
		    PANEL_LABEL_Y, ATTR_COL(0),
		    PANEL_LABEL_STRING, "y",
		    0);
  
  y_item = panel_create_item(panel, PANEL_MESSAGE,
			     PANEL_LABEL_X, ATTR_COL(8),
			     PANEL_LABEL_Y, ATTR_COL(0),
			     0);
  
  panel_create_item(panel,PANEL_MESSAGE,
		    PANEL_LABEL_X, ATTR_COL(0),
		    PANEL_LABEL_Y, ATTR_COL(1),
		    PANEL_LABEL_STRING,"SNodes",
		    0);
  
  
  imvalue_item = panel_create_item(panel, PANEL_MESSAGE,
				   PANEL_LABEL_X, ATTR_COL(7),
				   PANEL_LABEL_Y, ATTR_COL(1),
				   0);

  panel_create_item(panel, PANEL_BUTTON,
		     PANEL_LABEL_X, ATTR_COL(15),
		    PANEL_LABEL_Y, ATTR_COL(1),
		    PANEL_LABEL_IMAGE, panel_button_image(panel, "Save",5,0),
		    PANEL_NOTIFY_PROC, save_proc,
		    0);
  
  
  panel_create_item(panel, PANEL_CYCLE,
		    PANEL_LABEL_STRING,    "Strategy",
		    PANEL_LABEL_X, ATTR_COL(12),
		    PANEL_LABEL_Y, ATTR_COL(0),
		    PANEL_NOTIFY_PROC, set_search_strategy,
		    PANEL_CHOICE_STRINGS,
		          "Breadth First",
		          "Depth First",
		          "Branch-and-Bound",
		          "Average Path Cost",
                          "Best First",
		          "A*",
		          0,
		    0);
  /*
  panel_create_item(panel, PANEL_BUTTON,
		    PANEL_LABEL_X, ATTR_COL(20),
		    PANEL_LABEL_Y, ATTR_COL(0),
		    PANEL_LABEL_IMAGE, panel_button_image(panel,"Clear",5,0),
		    PANEL_NOTIFY_PROC, extend_proc,
		    0);
  
  
  panel_create_item(panel, PANEL_BUTTON,
		    PANEL_LABEL_X, ATTR_COL(12),
		    PANEL_LABEL_Y, ATTR_COL(1),
		    PANEL_LABEL_IMAGE, panel_button_image(panel,"Save",5,0),
		    PANEL_NOTIFY_PROC, save_popup_proc,
		    0);
  
  */
  window_fit_height(panel);
}

static void set_search_strategy(item, value, event)
Panel_item item;
int        value;
Event      *event;
{
  switch(value)
    {
    case 0:
      strat = BreadthFirst;
      break;
      
    case 1:
      strat = DepthFirst;
      break;
    case 2:
      strat = BranchAndBound;
      break;
    case 3:
      strat = AveragePathCost;
      break;
    case 4:
      strat = BestFirst;
      break;
    case 5:
      strat = AStar;
      break;
    }
  
} 

 
static void crop_proc()
{
  
}



static void extend_proc()
{
  
  
}


static void histogram_done_proc()
{

}

static void save_popup_proc()
{
}

static void save_popup_done_proc()
{

}


extern int panel_pw_text();

void canvas_event_proc(window,event,arg)
Window window;
Event *event;
caddr_t arg;

{
  int e,x,y,im;
  
  
  char *str[12];
  
  e = event_action(event);
  

  switch(e)
    {
    case MS_LEFT:
      fprintf(stderr,"\n down buttoning*** ");
      
      if(!LeftButtonDown)
	{
	  fprintf(stderr,"\n down buttoning %d %d",strat, DepthFirst);
	  
	  LeftButtonDown = TRUE;
	  extend_lines(Head,strat);
	}
      else
	LeftButtonDown = FALSE;
      
    }
}



static void save_proc()
{
  int a,x,y,width,height;
  
  byte *outimage;
  
  height = im_struct.height;
  width = im_struct.width;
  
  outimage = (byte*)malloc(sizeof(byte)*width*height);

  for(y=0; y<height; ++y)
    for(x=0; x<width; ++x)
      {

	if((a = pw_get(pw,x,y)) == RED)
	  outimage[y*width + x] = 255;
	else
	  outimage[y*width + x] = 0;
      }
  Imsave(outimage, "",  im_struct.width, im_struct.height) ;
  
}

