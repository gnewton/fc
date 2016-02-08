
#include "stuff.h"


typedef struct plist
{
  int x,y;
  struct plist *next;
}
LIST;


#define popd(list_of_points)\
  if(list_of_points != NULL)\
  list_of_points = list_of_points->next;

extern int AverageBlockSize;
 
#define On 0

byte *FcAverage()


{
  extern IMAGE im_struct;
  extern byte *image;
  
  LIST *list=NULL, *tmp=NULL;
    
  byte *imnew;  

  short *candidates;
  

  int width=im_struct.width,
  height = im_struct.height,
  n, sum, Flag,Adding,
  x,y,k,l,
  s2 = AverageBlockSize/2;
  
  candidates = im_struct.candidates;
  
  
  imnew = (byte*)malloc(sizeof(byte)*width*height);
  
  for(k=0; k<height; ++k)
    for(l=0; l<= width; ++l)
      {
	if(k<s2 || k>height-s2 || l<s2 || l>width-s2 
	   || candidates[k*width+l] <= StrongEdge)
	  imnew[k*width+l] = image[k*width+l];
	else
	  {
	    n=0;
	    sum = 0;  
	    list = NULL;
	    tmp = NULL;
	    
	    pushd(list,l,k);
	    Adding = TRUE;
	    
	    while(Adding)
	      {
		Adding = FALSE;
		++n;
		x = list->x;
		y = list->y;
		sum += image[y*width+x];
		
		if(candidates[y*width + x+1] > StrongEdge && x+1 < l+s2+1 && x+1<width)
		  {
		    tmp = list;
		    while(tmp != NULL )
		      {
			if(tmp->x == x+1 && tmp->y == y)
			  {
			    tmp = NULL;
			    Flag = FALSE;
			  }
			else
			  tmp = tmp->next;
		      }
		    if(Flag)
		      {
			++n;
			sum += image[y*width+x+1];
			tmp = (LIST*)malloc(sizeof(LIST));
			tmp->x =x+1;
			tmp->y = y;
			tmp->next = list;
			list = tmp;
		      }
		    
		  }
		if(candidates[y*width + x-1]> StrongEdge && x-1 >l-s2-1 && x-1>0)
		  {
		    ++n;
		    sum += image[y*width+x-1];
		    pushd(list,(x-1),y);
		  }
		if(candidates[(y+1)*width + x] > StrongEdge && y+1 < k+s2+1 && y+1<height)
		  {
		    ++n;
		    sum += image[(y+1)*width + x];
		    pushd(list,x,(y+1));
		  }
		if(candidates[(y-1)*width + x] > StrongEdge && y-1 > k-s2-1 && y-1>0) 
		  { 
		    ++n;
		    sum += image[(y-1)*width + x];
		    pushd(list,x,(y-1));
		  }
		
	      }
	    imnew[k*width+l] = sum/n;
	  }
      }

  return(imnew);
  
}
