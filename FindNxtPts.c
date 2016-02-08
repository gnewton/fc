
#include "stuff.h"
#include "search.h"

#define TurnConstant 0.7

int FindNextPoints(next_point, start_point, search_direction, min_edge_strength)
     NEXTPOINT *next_point;
     int start_point, search_direction, min_edge_strength;
{
  extern IMAGE im_struct;
  
  int width = im_struct.width,
  start_point_direction, dir,tmp,dif;
  
  short *candidates, *edge_mag;
  byte *edge_dir;
  
  edge_mag = im_struct.edge_mag;
  edge_dir = im_struct.edge_dir;
  candidates = im_struct.candidates;
  
  start_point_direction = edge_dir[start_point];
  
  
  /* remember Front = 0, Left = 1, Right = 2  */
  
  
  if(search_direction == Backward)   
    start_point_direction = (start_point_direction + 4)%8;
  
  switch(start_point_direction)
    {
      case(0):
	{
	  next_point[Front].point = start_point + 1;
	  next_point[Left].point = start_point + 1 + width;
	  next_point[Right].point = start_point + 1 - width;
	  
	  if(candidates[start_point + width] > SplitPoint)
	    next_point[LLeft].point = start_point + width;
	  else
	    next_point[LLeft].point = BadPoint;

	  
	  if(candidates[start_point - width] > SplitPoint)
	    next_point[RRight].point = start_point + width;
	  else
	    next_point[RRight].point = BadPoint;

	  break;
	}
      
      case(1):
	{
	  next_point[Front].point = start_point + 1 - width;
	  next_point[Left].point = start_point - width;
	  next_point[Right].point = start_point + 1;
	  if(candidates[start_point + width +1] > SplitPoint)
	    next_point[LLeft].point = start_point + width +1;
	  else
	    next_point[LLeft].point = BadPoint;

	  
	  if(candidates[start_point-width -1] > SplitPoint)
	    next_point[RRight].point = start_point-width-1;
	  else
	    next_point[RRight].point = BadPoint;

	  break;
	}
      case(2):
	{
	  next_point[Front].point = start_point - width;
	  next_point[Left].point = start_point - width -1;
	  next_point[Right].point = start_point - width + 1;
	  if(candidates[start_point + 1] > SplitPoint)
	    next_point[LLeft].point = start_point+1;
	  else
	    next_point[LLeft].point = BadPoint;

	  if(candidates[start_point-1] > SplitPoint)
	    next_point[RRight].point = start_point -1;
	  else
	    next_point[RRight].point = BadPoint;

	  break;
	}
      case(3):
	{
	  next_point[Front].point = start_point - width -1;
	  next_point[Left].point = start_point -1;
	  next_point[Right].point = start_point - width;
	  if(candidates[start_point + 1 -width] > SplitPoint)
	    next_point[LLeft].point = start_point + 1 - width;
	  else
	    next_point[LLeft].point = BadPoint;

	  
	  if(candidates[start_point -1 +width] > SplitPoint)
	    next_point[RRight].point = start_point -1 + width;
	  else
	    next_point[RRight].point = start_point -1 + width;

	}
      case(4):
	{
	  next_point[Front].point = start_point - 1;
	  next_point[Left].point = start_point - 1 + width;
	  next_point[Right].point = start_point - 1 - width;
	  if(candidates[start_point - width] > SplitPoint)
	    next_point[LLeft].point = start_point - width;
	  else
	    next_point[LLeft].point = BadPoint;

	  
	  if(candidates[start_point + width] > SplitPoint)
	    next_point[RRight].point = start_point + width;
	  else
	    next_point[RRight].point = BadPoint;
	  break;
	}
      case(5):
	{
	  next_point[Front].point = start_point - 1 + width;
	  next_point[Left].point = start_point + width;
	  next_point[Right].point = start_point -1;
	  if(candidates[start_point -1 -width] > SplitPoint)
	    next_point[LLeft].point = start_point -1 -width;
	  else
	    next_point[LLeft].point = BadPoint;

	  if(candidates[start_point + 1 + width] > SplitPoint)
	    next_point[RRight].point = start_point +1 +width;
	  else
	    next_point[RRight].point = BadPoint;

	  break;
	}
      case(6):
	{
	  next_point[Front].point = start_point + width;
	  next_point[Left].point = start_point + width + 1;
	  next_point[Right].point = start_point + width -1;
	  if(candidates[start_point + 1] > SplitPoint)
	    next_point[LLeft].point = start_point + 1;
	  else
	    next_point[LLeft].point = BadPoint;

	  
	  if(candidates[start_point - 1] > SplitPoint)
	    next_point[RRight].point = start_point - 1;
	  else
	    next_point[RRight].point = BadPoint;

	  break;
	}
      case(7):
	{
	  next_point[Front].point = start_point + width + 1;
	  next_point[Left].point = start_point + 1;
	  next_point[Right].point = start_point + width;
	  if(candidates[start_point + 1 - width] > SplitPoint)
	    next_point[LLeft].point = start_point + 1 - width;
	  else
	    next_point[LLeft].point = BadPoint;

	  if(candidates[start_point -1 + width] > SplitPoint)
	    next_point[RRight].point = start_point -1 + width;
	  else
	    next_point[RRight].point = BadPoint;

	  break;
	}
    }
  
  next_point[Front].distance = 2;
  next_point[Right].distance = 3;
  next_point[Left].distance = 3;
  next_point[RRight].distance = 2;
  next_point[LLeft].distance = 2;

  /* remember Front = 0, Left = 1, Right = 2  */
  for(dir = 0;dir<=Front; ++dir)
    {
      if(edge_mag[next_point[dir].point] < min_edge_strength ||
	 candidates[next_point[dir].point] <= SplitPoint)
	next_point[dir].point = BadPoint;
/*      else
	{
	  dif = (edge_dir[next_point[dir].point] - edge_dir[start_point])%8;
	  fprintf(stderr,"\n*******************\n");
	  
	  switch(dir)
	    {
	    case Front:
	      if(abs(dif) >2)
		next_point[dir].point = BadPoint;
	      break;

	    case Left:
	    case Right:
	      if(abs(dif) >1)
		next_point[dir].point = BadPoint;
	      break;
	      
	    case LLeft:
	      if(dif >0 || dif < -1)
		next_point[dir].point = BadPoint;
	      break;
	      
	    case RRight:
	      if(dif < 0 || dif > 1)
		next_point[dir].point = BadPoint;
	      break;
	    }
	}*/
    }
}


/*
	 (abs(edge_dir[next_point[dir].point] - edge_dir[start_point])%8) != 0)
*/
