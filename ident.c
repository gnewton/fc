
#include "stuff.h"

/* - ident returns the identity number of the list of the end point
   which was just found.

   - this is done by examining the neighbours of the end point and finding one
   which has a value that is less than or equal than the ListIdStart, as
   nothing else in the candidates array has values in this range...

   - there are 2 special cases : 1 - when the end point is the member of a
   list made up of only 2 end points, the new end point and another end point,
   in which case there is no list id assigned to the list, and 
   DoublePointContour is returned; 2 - if the end point is the only point in 
   the list, it too is assigned no list id, and returns  SinglePointContour.
*/


int ident(new_contour_end_point)
     int new_contour_end_point;

{
  extern IMAGE im_struct;
  
  short *candidates;
    
  int width = im_struct.width,
  height = im_struct.height,
  ii,jj,n;


  candidates = im_struct.candidates;
   
  n = new_contour_end_point;
  

  /* if a neighbour in candidates is found which has a valid list id, then
     the new end point is a member of this list  
  */
  for(ii=-1; ii<=1; ++ii)
    for(jj=-width; jj <=width; jj+=width)
      if(candidates[n+ii+jj] <= ListIdStart)
	return(candidates[n+ii+jj]);
  

  /* if the neighbour is a split point, one cannot tell if the end point is a
     member of an list with an id, so the id of the split pooint neighbour is 
     found
     */
  for(ii=-1; ii<=1; ++ii)
    for(jj=-width; jj <= width; jj+=width)
      if(candidates[n+ii+jj] == SplitPoint)
	return(ident((n+ii+jj)));



  /* If a neighbour in candidates is found which is an end point, the new
     end point is  the member of a list which is a two point line - that
     is, it is made up of only two linked end points 
  */
  for(ii=-1; ii<=1; ++ii)
    for(jj=-width; jj<=width; jj+=width)
      if(candidates[n+width+height] == EndPoint)
	return(DoublePointContour);
  
  return(SinglePointContour);
}

