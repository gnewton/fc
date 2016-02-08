/********************************************************
 *							*
 *							*
 *		CHist - go through the lists in      	*
 *		stronglist, and those larger than a	*
 *		certain size are used to build a 	*
 *		circular histogram.			*
 *							*
 *							*
 ********************************************************/

#include "stuff.h"
#define  OutputListPointsFile  "points.outfile"

CHist(strong_list)
SEGMENTS_LIST *strong_list;
{
  
  extern IMAGE im_struct;
  
  extern int MinOutSize,SmoothCircHist, RotateHist,OutputListPoints;


  extern byte *image;
  
  int ii,j, *Smooth(),
  width, height,
  mag,dir,diff,hist[HistSize], newhist[HistSize],max;
  
  short *candidates;
  
  float cdth, adiff;
  
  void FindEdge();
  FILE *fp;
  
  SEGMENTS_LIST *list_list_ptr;

  EDGE_LIST *edge_list_ptr;
  
  byte *output_image;
    
  width = im_struct.width;
  height = im_struct.height;
  candidates = im_struct.candidates;

  if(OutputListPoints)
    fp = fopen(OutputListPointsFile,"w");
    
  for(ii=0;ii<HistSize; ++ii)
    hist[ii] = 0;
  output_image = image;
  
  list_list_ptr = strong_list;
  while(list_list_ptr != NULL)
    {
      if(list_list_ptr->num_list_points >= MinOutSize)
	{
	  edge_list_ptr = list_list_ptr->contour_ptr;
	  while(edge_list_ptr != NULL)
	    {
	      FindEdge(edge_list_ptr->n,&mag,&dir);
	      if(OutputListPoints && fp)
		fprintf(fp,"\n %d\t%d\t\t%d\t%5.3f", edge_list_ptr->n%width,edge_list_ptr->n/width,dir,(double)mag/1020.0);
	      
	      dir = (abs(dir+RotateHist))%180;
	      
	      hist[dir] += mag;
	      if(hist[dir] > max)
		max = hist[dir];
	      edge_list_ptr = edge_list_ptr->next;
	    }
	}
      list_list_ptr = list_list_ptr->next_contour;
    }  
  
  if(OutputListPoints)
    fclose(fp);
      
  if(SmoothCircHist)
    {
      max = 0;
      for(ii=0;ii<HistSize/2;++ii)
	{
	  hist[ii+180] = hist[ii];
	}
      
      
      for(ii=0;ii<HistSize;++ii)
        {
	  newhist[ii] = 0;
	  for(j=0;j<HistSize; ++j)
            {
	      cdth = cos((double)(((double)(ii-j))* PI/180.0));
	      adiff = exp(120.0 * (cdth-1.0)) * (double)hist[j] ;
	      newhist[ii] += (int)adiff;
            }
	  if(newhist[ii] > max)
	    max = newhist[ii];
	}
      MakeCircHist(newhist,max);
    } 
  else
    {   
      for(ii=0;ii<HistSize/2;++ii)
	hist[ii+180] = hist[ii];
      MakeCircHist(hist,max);
    }
}


void FindEdge(n, mag, dir)
int n, *mag, *dir;
{
  extern  IMAGE im_struct;
  extern  byte *image;
  
  int dx, dy,
  a,b,c,d,f,g,h,i, 
  nx, n_x;
  
  double atan();
  
  
  
  nx = n + (im_struct.width);
  n_x = n - (im_struct.width);
  a = image[ n_x - 1 ] ;
  b = image[ n_x ] ;
  c = image[ n_x + 1 ] ;
  d = image[ n - 1 ] ;
  f = image[ n + 1 ] ;
  g = image[ nx -1 ] ;
  h = image[ nx ] ;
  i = image[ nx + 1 ] ;
  
  dx = c + f + f + i - a - d - d - g;
  dy = a + b + b + c - g - h - h - i;
  
  if(dx == 0)
    {
      *dir = 90;
      *mag = abs(dy);
    }
  else 
    if(dy == 0)
      {
	*dir = 0;
	*mag = abs(dx);
      }
    else 
      {
	*mag = sqrt((float)(dx*dx +  dy*dy));
	*dir = 90 + (atan((double)dy/(double)dx))*57.2;
	if(*mag > 10000 || *mag < -10000)
	  {
	    printf("\n %d %d %d %d",dx,dy,mag,dir);
	  }
      }
}











int *Smooth(hist,max)
int hist[], *max;

{
  int ii,j,newhist[HistSize];
  double exp(),cos(), cdth,temp,adiff;
  
  
  *max = 0;
  for(ii=0;ii<HistSize/2-1;++ii)
    {
      newhist[ii] = 0;
      for(j=0;j<HistSize/2-1; ++j)
	{
	  cdth = cos((double)(((double)(ii-j))* PI/180.0));
	  adiff = exp(120.0 * (cdth-1.0)) * (double)hist[j] ;
	  newhist[ii] += (int)adiff;
	}
      if(newhist[ii] > *max)
	{
	  *max = newhist[ii];
	}
    }
  
  return(newhist);
} 

