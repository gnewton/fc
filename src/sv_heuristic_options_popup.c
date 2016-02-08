
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


void create_options_popup()
{

  int X = 2;
  
  
  options_frame = window_create(frame, FRAME,0);
  options_panel = window_create(options_frame, PANEL, 0);
  
  
  panel_create_item(options_panel, PANEL_MESSAGE,
		    PANEL_LABEL_STRING,  "Options for DLA",
		    0);
  
  panel_create_item(options_panel, PANEL_CYCLE,
		    PANEL_ITEM_X,ATTR_COL(X),
		    PANEL_ITEM_Y,ATTR_COL(1),
		    PANEL_NOTIFY_PROC, search_depth_proc,
		    PANEL_LABEL_STRING,"Search Depth        ",
		    PANEL_CHOICE_STRINGS, 
		    "2",
		    "4",
		    "6",
		    "8",
		    "10",
		    "12",
		    "14",
		    "16",
		    "18",
		    "20",
		    "25",
		    "30",
		    "35",
		    0,
		    0);
  
  panel_create_item(options_panel, PANEL_CYCLE,
		    PANEL_ITEM_X,ATTR_COL(X),
		    PANEL_ITEM_Y,ATTR_COL(2),
		    PANEL_NOTIFY_PROC, min_edge_strength_proc,
		    PANEL_LABEL_STRING,"Min. Edge Strength",
		    PANEL_CHOICE_STRINGS, 
		    "0"
		    "10",
		    "20",
		    "30",
		    "40",
		    "50"
		    "60",
		    "70",
		    "80",
		    "90",
		    "100",
		    "110",
		    "120",
		    "130",
		    "140",
		    "150",
		    "200",
		    "250",
		    "300",
		    "350",
		    "400",
		    0,
		    0);
  
  panel_create_item(options_panel, PANEL_CYCLE,
		    PANEL_ITEM_X,ATTR_COL(X),
		    PANEL_ITEM_Y,ATTR_COL(3),
		    PANEL_NOTIFY_PROC,min_end_point_contour_length,
		    PANEL_LABEL_STRING,"End-point Contour Length",
		    PANEL_CHOICE_STRINGS, 
		    "50",
		    "40",
		    "35",
		    "30",
		    "25",
		    "20",
		    "15",
		    "10",
		    "5",
		    "0".
		    0,
		    0);
  
  panel_create_item(options_panel, PANEL_CYCLE,
		    PANEL_ITEM_X,ATTR_COL(X),
		    PANEL_ITEM_Y,ATTR_COL(4),
		    PANEL_NOTIFY_PROC,max_end_point_distance,
		    PANEL_LABEL_STRING,"End-point Distance",
		    PANEL_CHOICE_STRINGS, 
		    "2",
		    "4",
		    "6",
		    "8",
		    "10",
		    "12",
		    "14",
		    "16",
		    "18",
		    "20",
		    "25",
		    "30",
		    "35",
		    "40",
		    "45",
		    "50",
		    "55",
		    "60",
		    "65",
		    "70",
		    0,
		    0);
  
  panel_create_item(options_panel, PANEL_CYCLE,
		    PANEL_ITEM_X,ATTR_COL(X),
		    PANEL_ITEM_Y,ATTR_COL(5),
		    PANEL_NOTIFY_PROC, end_point_type,
		    PANEL_LABEL_STRING, "End-point ",
		    PANEL_CHOICE_STRINGS,
		    "Probabilistic",
		    "Fixed",
		    0,
		    0);
  
  
  
  panel_create_item(options_panel, PANEL_BUTTON,
		    PANEL_ITEM_X,ATTR_COL(X),
		    PANEL_ITEM_Y,ATTR_COL(7),
		    PANEL_LABEL_IMAGE,    panel_button_image(panel,"Done",0,0),
		    PANEL_NOTIFY_PROC,    done_proc,
		    0);
  
  
  window_fit(options_panel);
  window_fit(options_frame);
}
