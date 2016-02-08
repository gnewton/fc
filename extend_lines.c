
#include "stuff.h"
#include "search.h"


int extend_lines(head_contour_list_ptr, strategy)
     SEGMENTS_LIST **head_contour_list_ptr;
     int strategy;
     
{
  extern int Debug;
  
  SEGMENTS_LIST *find_largest_line_contour(),
  *largest_line_contour_list_ptr;

  int debug(), Link2ClosestContour(), pass, min_start_contour_length[NumSearchPasses];
   
  if(Debug)
    debug("extend_lines");
  
  min_start_contour_length[Pass1] = 12;
  min_start_contour_length[Pass2] = 6;
  


  for(pass = Pass1; pass < NumSearchPasses; ++pass)
    {
      fprintf(stderr, "\n\n\n ================ Pass %d\n",pass);
      
      largest_line_contour_list_ptr = find_largest_line_contour(head_contour_list_ptr, pass);

      while(largest_line_contour_list_ptr != NULL)
	{ 
	  largest_line_contour_list_ptr->Search_status = pass;
      
	  Link2ClosestContour(head_contour_list_ptr,largest_line_contour_list_ptr, pass, strategy);
	  /*extend_line_contours_pass1(head_contour_list_ptr, 
	    largest_line_contour_list_ptr);*/
	  largest_line_contour_list_ptr = 
	    find_largest_line_contour(head_contour_list_ptr);
	}
    }
}

