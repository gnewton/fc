#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <math.h>




#define STATUS_OK       0
#define STATUS_ERROR    1

#define BYTE            1
#define SHORT           2

typedef unsigned char byte;

/********************************/
/* Debug Values                 */
#define TRACE 7

/*******************************/

#define PI 3.14159265358979
#define VeryLargeNumber 1<<29

#define Num_Edge_Types 2
#define TRUE 1
#define FALSE 0


#define Grouped  100        /* Used when grouping contours at very end  */
#define Non_Edge 255
#define Edge 180
#define AlreadySearched 199


#define StrongEdge 20 
#define ContourEdge 19
#define OnNeighbourList 15

#define EndPoint 10
#define SplitPoint 5



#define Special_Case_Id 0
#define ListIdStart -1
#define SinglePointContour 1
#define DoublePointContour 2
/* ContourEdge and StrongEdge_Used must be equal;
   ContourEdge, EndPoint, OnNeighbourList and SplitPoint must be 
   less than StrongEdge 
   Non_Edge and Edge must be greater than StrongEdge   
   Special_Case_Id and ListIdStart must be less than the others,
   and ListIdStart must have access to numbers less than it, down to
   (ListIdStart - maximum number of edge lists)*/

#define TEST FALSE 


/* overlay decides whether the contours are placed over 
   the original image or not*/

/* the contours are set all one gray level (black)*/
#define All_one_gray_level TRUE
#define gray_level 0
#define OverLayColour 255
#define BackGroundColour 255
#define special_point_gray_level 0
#define Print_hist FALSE
#define Smooth_hist FALSE



/* the depth in which the search is made in depth_search  */
#define MaxSearchDepth 4
#define Search_edge_thresh 25
/* the minimum line size that a line is used to be extended*/

#define Front 4
#define Left 3
#define Right 2
#define LLeft 1
#define RRight 0

#define Forward 1
#define Backward -1
#define NoCloseEndPoint -1

#define StopThisSearch 2
#define StopAllSearch 4
#define StopSearch 4
#define Continue_This_Search TRUE
#define FoundNextContour 5
#define Searched -1
#define Unsearched -2

#define BadPoint -1
#define Range 1

/* for windowing*/
#define BACKGROUND 0
#define FOREGROUND 1
#define RED 2
#define GREEN 3
typedef struct edge_list_struct
             {
               int n;
               struct edge_list_struct *next;
	     } EDGE_LIST;

typedef struct ptr_list_struct
             {
	       int search_status;
	       struct edge_list_struct *pointer;
	       struct ptr_list_struct *next;
	     }PTR_LIST;
  


typedef struct list_of_lists 
               {
               int list_id;
	       int Search_status;
	       int num_list_points;
	       int num_end_points;
	       int num_split_points;
	       EDGE_LIST *contour_ptr;
	       struct ptr_list_struct *end_points_list;
	       struct list_of_lists *next_contour;
               } SEGMENTS_LIST;

typedef struct image_structure
               {
		 int width, height, imsize;
		 byte *image;
		 short *edge_mag;
		 byte  *edge_dir;
		 short *candidates;
	       }IMAGE;

/*

typedef struct options_struct
{

}
*/

		 


/* for making histograms */

#define HistSize 360


#define pushd(list_of_points, a, b)\
  tmp = list_of_points;\
  Flag = TRUE;\
  while(tmp != NULL )\
      {\
      if(tmp->x == a && tmp->y == b)\
	{\
	   tmp = NULL;\
	   Flag = FALSE;\
           }\
	else\
	  tmp = tmp->next;\
       	}\
  if(Flag)\
      {\
      Adding = TRUE;\
      tmp = (LIST*)malloc(sizeof(LIST));\
      tmp->x = a;\
      tmp->y = b;\
      tmp->next = list_of_points;\
      list_of_points = tmp; }



