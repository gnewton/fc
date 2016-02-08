#include <stdio.h>
#include "stuff.h"

#define ListPointOutFile "points.list"
  
  int show_edges(strong_list,outimage)
SEGMENTS_LIST *strong_list;
byte *outimage;

{
  
  extern IMAGE im_struct;
  extern byte *image;
  
  extern int Overlay,
  CheckContourDir,
  EndPointNum,
  OutputSingleContour,
  Debug,
  OutputListPoints,
  MinOutSize;

  FILE *fp;
  
  
  
  int width = im_struct.width,
  ii,jj,m,n, f, OutLine;
  
  short *candidates;
  
  SEGMENTS_LIST *list_list_ptr;
  
  EDGE_LIST *edge_list_ptr;
  
  candidates = im_struct.candidates;
  
  /* magic numbers */
  
  ii = 230;
  
  m = 35;
  
  jj = 20;
  
  
  
  list_list_ptr = strong_list;
  while(list_list_ptr != NULL)
    {
      if(Debug == 12)
	fprintf(stderr,"\n\n\n**List ID = %d   pts= %d  ends= %d  splits= %d \n ",
		list_list_ptr->list_id, list_list_ptr->num_list_points, list_list_ptr->num_end_points,
		list_list_ptr->num_split_points);
      
      if(OutputSingleContour==FALSE || list_list_ptr->list_id ==OutputSingleContour)
	if(list_list_ptr->num_list_points >= MinOutSize
	   && list_list_ptr->num_end_points <= EndPointNum
	   && (CheckContourDir == FALSE || CheckContourDir == TRUE &&
	       ContourDir(list_list_ptr) == TRUE))
	  {
	    edge_list_ptr = list_list_ptr->contour_ptr;
	    f = edge_list_ptr->n;
	    if(Debug == 12)
	      fprintf(stderr, "%d ",f);
	    
	    OutLine = OverLayColour;
	    
	    while(edge_list_ptr != NULL)
	      {
		
		if(Overlay == TRUE)
		  {
		    outimage[edge_list_ptr->n] = OutLine;
		    
		  }
		else
		  {
		    if(candidates[edge_list_ptr->n] == SplitPoint||
		       candidates[edge_list_ptr->n] == EndPoint)
		      {
			outimage[edge_list_ptr->n] = special_point_gray_level;
		      }
		    else
		      {
			if(All_one_gray_level == TRUE)
			  outimage[edge_list_ptr->n] = gray_level;
			else
			  {
			    outimage[edge_list_ptr->n] = ii + jj;
			    jj = -jj;
			  }
		      }
		  }
		edge_list_ptr = edge_list_ptr->next;
		if(edge_list_ptr != NULL && edge_list_ptr->n == f)
		  edge_list_ptr = NULL;
	      }
	  }
      ii = ii - m;
      if(ii < 80 )
	ii = 210; 
      list_list_ptr = list_list_ptr->next_contour;
    }  
}








